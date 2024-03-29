#include <Arduino.h>
#define DEBUG_ON 1

#define localDomain "pogoda"
#define _setSyncInterval 15


#include "BluetoothSerial.h"
#include <esp_now.h>
#include <WiFi.h>

// #include <WifiClient.h>
#include <WifiAP.h>
#include <WebServer.h>

#include <Wire.h>
#include <RtcDS3231.h>
#include "Adafruit_Thermal.h"
#include "EEPROM.h"
#include "home.h"

int nilaiA, nilaiB = 0;
int bbb = 0,aaa = 0;
RtcDS3231<TwoWire> Rtc(Wire);
uint8_t Jam, Menit, Detik;
BluetoothSerial SerialBT;
Adafruit_Thermal printer(&SerialBT);
bool state;
byte statewifi = 0;
int stwf = 0;
byte count_bt = 0;
//set jam manual
int setjam;
int setmenit;
int setdetik;
String jam, menit, detik;
char nama_hari[7][12] = {"sabtu", "minggu", "senen", "selasa", "rabu", "kamis", "jumat"};



const char *ssid = "kampret";
const char *password = "123456789";
WebServer server(80);

uint8_t broadcastAddress[] = { 0xC0, 0x49, 0xEF, 0xE7, 0xC7, 0x8C };
typedef struct struct_message {

  int butonA;
  int butonB;
  //  uint8_t jam;
  //  uint8_t menit;
  //  uint8_t detik;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


#define PRINT(s, v) \
  { \
    Serial.print(F(s)); \
    Serial.print(v); \
  }
char szTxt[20];
#define pinbtnA 35
#define pinbtnB 32
#define pinbtnChangeWifi 5

uint8_t address[] = { 0x66, 0x32, 0xB0, 0xC6, 0x1D, 0xBF };
String name = "RPP02N";
bool connected;
void (*ku_reset)(void) = 0;
void handlehome() {
  server.send(200, "text/html", home);
}

void setting_wifi() {
  String ssidName = server.arg("ssid");
  String passwordName = server.arg("pswd");

  writeString(3, ssidName);
  Serial.print("SSID : ");
  Serial.println(ssidName);
  delay(500);
  writeString(14, passwordName);
  Serial.print("Password : ");
  Serial.println(passwordName);

  Serial.println(ssidName);
  Serial.println(passwordName);
  server.send(200, "text/html", home);
  delay(1000);
  ku_reset();
}

void handlewaktu() {
  jam = server.arg("jam");
  menit = server.arg("menit");
  detik = server.arg("detik");


  String click = server.arg("klik");

  // int jam = jam.toInt();
  setjam = jam.toInt();
  setmenit = menit.toInt();
  setdetik = detik.toInt();

  Serial.print(click);
  Serial.print("menit : ");
  Serial.println(setmenit);
  Serial.print("jam : ");
  Serial.println(setjam);
  Serial.print("detik : ");
  Serial.println(setdetik);


  //set waktu manual
  char userTime[8];
  userTime[0] = setjam / 10 + '0';
  userTime[1] = setjam % 10 + '0';
  userTime[2] = ':';
  userTime[3] = setmenit / 10 + '0';
  userTime[4] = setmenit % 10 + '0';
  userTime[5] = ':';
  userTime[6] = setdetik / 10 + '0';
  userTime[7] = setdetik % 10 + '0';
  RtcDateTime manual = RtcDateTime(__DATE__, userTime);
  Rtc.SetDateTime(manual);
  Serial.println(manual);
  //
  //    EEPROM.write(alamatjam,setjam);
  //    EEPROM.write(alamatmenit,setmenit);
  //    EEPROM.commit();

  // server.send(200, "application/json", "sukses");
  server.send(200, "text/html", home);
}

void setting_bt() {

  String NameBt = server.arg("btt");
  writeString(25, NameBt);
  delay(500);
  server.send(200, "text/html", home);
  delay(1000);
  ku_reset();
}
void writeString(char add, String data) {
  int _size = data.length();
  int i;
  for (i = 0; i < _size; i++) {
    EEPROM.writeChar(add + i, data[i]);
  }
  EEPROM.writeChar(add + _size, '\0');
  EEPROM.commit();
}


String read_String(char add) {
  int i;
  char data[256];  //Max 100 Bytes
  int len = 0;
  char k;
  k = (char)EEPROM.readChar(add);
  while (len < 10) {
    k = (char)EEPROM.readChar(add + len);
    data[len] = k;
    len++;
  }
  data[len] = '\0';
  return String(data);
}

void setup() {
  Serial.begin(115200);
  if (!EEPROM.begin(1000)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }

  SerialBT.setPin("0000");
  SerialBT.begin("Sihab", true);
  // WiFi.softAPConfig(ip, gateway, subnet);
  //  WiFi.mode(WIFI_AP);
  statewifi = (byte)EEPROM.readByte(stwf);
  // Serial.print(statewifi);
  String ssidString = read_String(3);
  String passString = read_String(14);
  const char *ssid = ssidString.c_str();
  const char *password = passString.c_str();
  Serial.println(ssidString);
  Serial.println(passString);

  name = read_String(25);
  Serial.println(name);
  // Serial.print((char)EEPROM.readChar(3));
  // Serial.print((char)EEPROM.readChar(4));
  // Serial.println((char)EEPROM.readChar(5));
  count_bt = 0;
  if (!WiFi.softAP(ssid, password) && statewifi == 1) {

    log_e("Soft AP creation failed.");
    while (1)
      ;
  }

  else if (statewifi == 0 && !connected) {
    Serial.println("Masuk Ke mode normal/STA");

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
      Serial.println("Error initializing ESP-NOW");
      return;
    }

    esp_now_register_send_cb(OnDataSent);
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("Failed to add peer");
      return;
    }
  }

  if (statewifi == 1) {
    IPAddress myIP = WiFi.softAPIP();

    server.on("/", handlehome);
    server.on("/setwifi", setting_wifi);
    server.on("/setbt", setting_bt);
    server.on("/setjam", handlewaktu);
    server.begin();
    Serial.println(myIP);
  }

  Rtc.Begin(21, 22);
  // RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  // Rtc.SetDateTime(compiled);
  // WiFi.mode(WIFI_STA);
  pinMode(pinbtnA, INPUT_PULLUP);
  pinMode(pinbtnB, INPUT_PULLUP);
  pinMode(pinbtnChangeWifi, INPUT_PULLUP);
}

void loop() {

  server.handleClient();
  RtcDateTime now = Rtc.GetDateTime();
  state = digitalRead(pinbtnChangeWifi);
  // Serial.print(state);
  // Serial.print(" ");
  statewifi = (byte)EEPROM.readByte(stwf);
  // Serial.print(statewifi);
  if (statewifi == 1) {
    // Serial.println(" mode AP");
    count_bt = 0;
  } else if ((statewifi == 0 || statewifi == 255) && !connected) {
    // Serial.println(" mode STA");
    // esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (count_bt <= 5) {
      while (!SerialBT.connected(1000)) {
        connected = SerialBT.connect(name);
        SerialBT.connect(name);
        count_bt++;
        Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
      }
    }
  }
  nilaiA = (byte)EEPROM.readByte(37);
  nilaiB = (byte)EEPROM.readByte(38);
  // Serial.println(count_bt);
  // Serial.print(nilaiA);
  // Serial.print(" ");
  // Serial.print(nilaiB);
  // Serial.print(" ");
  // Serial.print(" ");
  // Serial.print(" ");
  // Serial.println(bbb);



  if (state == 1 && (statewifi == 0 || statewifi == 255)) {
    Serial.println("button di tekan ke mode AP");
    EEPROM.writeByte(stwf, 1);
    EEPROM.commit();
    ku_reset();
  } else if (statewifi == 1 && state == 1) {
    Serial.println("button di tekan ke mode STA");
    EEPROM.writeByte(stwf, 0);
    EEPROM.commit();
    ku_reset();
  }

  // mengambil nilai RTC
  Jam = now.Hour();
  Menit = now.Minute();
  Detik = now.Second();
  nama_hari[now.DayOfWeek()];
  // Serial.print(digitalRead(pinbtnA));
  // if (digitalRead(pinbtnA) == 1) {
  //   cetak_karcis("A",szTxt);
  // }
  if (connected) {
    buttonAA();
    buttonBB();
  }

  //Menampilkanke serial monitor
  sprintf(szTxt, "%02d/%02d/%02d Jam %02d:%02d:%02d",now.Day(),now.Month(),now.Year(), Jam, Menit, Detik);
  PRINT("\nWaku Sekarang ", szTxt);
}


void buttonAA() {
  String NomerAA = "A00";
  String nomer_aa;
  if (digitalRead(pinbtnA) == 1) {
    // aaa++;
    nilaiA++;
    delay(10);
    EEPROM.writeByte(37, nilaiA);
    EEPROM.commit();
    //    nomer = String(nilaiA);
    if (nilaiA < 10) {
      NomerAA = +"A0";
    } else if (nilaiA >= 10 && nilaiA < 31) {
      NomerAA = +"A";
    }

    nomer_aa = NomerAA + String(nilaiA);

    cetak_karcis(nomer_aa, szTxt);  //mencetak ke printer tehermal
    delay(300);
  }

  if (nilaiA > 30) {
    nilaiA = 0;
  }
}

void buttonBB() {
  String NomerBB = "B00";
  String nomer_bb;

  if (digitalRead(pinbtnB) == 1) {
    nilaiB++;
    // bbb++;
    delay(10);
    EEPROM.writeByte(38,nilaiB);
    EEPROM.commit();
    if (nilaiB < 10) {
      NomerBB = +"B0";
    } else if (nilaiB >= 10 && nilaiB < 31) {
      NomerBB = +"B";
    }
    

    nomer_bb = NomerBB + String(nilaiB);

    cetak_karcis(nomer_bb, szTxt);
    delay(300);
  }

  if (nilaiB > 30) {  //apabila nilai dari tombol b lebih dari angka 99, maka akan kembali ke 0
    nilaiB = 0;
  }
}

void cetak_karcis(String karcis, char szTxt2[20]) {

  Serial.println("mencetak karcis");
  printer.wake();        // MUST wake() before printing again, even if reset
  printer.setDefault();  // Restore printer to defaults
  printer.feed(1);
  printer.setSize('M');
  printer.justify('C');
  printer.println(F("Karcis Nomor Antrian:"));
  printer.feed(1);

  printer.boldOn();
  printer.justify('C');
  printer.setSize('L');
  printer.println(karcis);
  printer.boldOff();

  printer.feed(1);
  printer.justify('C');
  printer.setSize('S');
  printer.println(F(szTxt2));
  printer.justify('C');
  printer.setSize('S');
  printer.println(F("Created by EMBUN'S 369"));
  printer.feed(3);

  printer.sleep();  // Tell printer to sleep
  delay(500L);      // Sleep for 3 seconds

  Serial.println("MUST wake() before printing again, even if reset");

  Serial.println("Restore printer to defaults mode");
}
