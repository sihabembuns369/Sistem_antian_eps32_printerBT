
#include <esp_now.h>
#include <WiFi.h>
#include <DMD32.h>
#include "fonts/Arial_Black_16_ISO_8859_1.h"
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
DFRobotDFPlayerMini mp3;
void printDetail(uint8_t type, int value);
#define belas 12
#define puluh 13
#define seratus 14

const char *nmr_a = "A00";
const char *nmr_b = "B00";
String nomer_aa, nomer_bb;
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
int pinA, panggilulangA;
int pinB, panggilulangB;

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
const int defaultBrightness = (15 * 255) / 100;
//Timer setup
//create a hardware timer  of ESP32
hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

int nilaiA, nilaiB;
int nilaiAwal_a = 0 , nilaiAwal_b = 0;
int resetloket = 0;
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id;
  int butonA;
  int butonB;
  int resetl;
} struct_message;


// Create a struct_message called myData
struct_message myData;

struct_message board1;
struct_message board2;

struct_message boardsStruct[3] = {board1, board2};

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  //   Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  //  Serial.println(macStr);
  //   Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  memcpy(&myData, incomingData, sizeof(myData));

  boardsStruct[myData.id - 1].butonA = myData.butonA;
  boardsStruct[myData.id - 1].butonB = myData.butonB;
  boardsStruct[myData.id - 1].resetl = myData.resetl;
  //  Serial.printf("x value: %d \n", boardsStruct[myData.id-1].butonA);
  //  Serial.printf("y value: %d \n", boardsStruct[myData.id-1].butonB);
  //  Serial.println();

}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial2.begin(9600);
  mp3.begin(Serial2);
  mp3.setTimeOut(500); //Set serial communictaion time out 500ms
  mp3.volume(20);  //Set volume value (0~30).
  mp3.volumeUp(); //Volume Up
  mp3.volumeDown(); //Volume Down
  mp3.EQ(DFPLAYER_EQ_NORMAL);
  mp3.outputDevice(DFPLAYER_DEVICE_SD);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  uint8_t cpuClock = ESP.getCpuFreqMHz();
  timer = timerBegin(0, cpuClock, true);
  timerAttachInterrupt(timer, &triggerScan, true);
  timerAlarmWrite(timer, 300, true);
  timerAlarmEnable(timer);

  // pinMode(pinbusy,INPUT);

  //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  //Bluetooth device name
  dmd.setBrightness(100); //1-255
  dmd.selectFont(Arial_Black_16_ISO_8859_1);

    dmd.selectFont(Arial_Black_16_ISO_8859_1);

    //menmpilkan pertma kali
     dmd.drawString( 4,  1, nmr_a, 3, GRAPHICS_NORMAL    );
  dmd.drawString( 36,  1, nmr_b, 3, GRAPHICS_NORMAL    );
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

  //dari bluettoh
  nilaiA = boardsStruct[0].butonA;
  nilaiB = boardsStruct[0].butonB;
  resetloket = boardsStruct[0].resetl;
  //panggilA
  pinA = boardsStruct[1].butonA;
  panggilulangA = boardsStruct[1].butonB;




  Serial.print("Nilai buton A ");
  Serial.print(pinA);
  Serial.print("  ");
  Serial.print("  Pangggil Ulang ");
  Serial.print(panggilulangA);
  Serial.print("  loketA ");
  Serial.print(nilaiA);
  Serial.print("  LoketB ");
  Serial.print(nilaiB);
  Serial.print("  counter A =");
  Serial.print(nilaiAwal_a);
  Serial.print("  loket di reset =");
  Serial.println(resetloket);
//  loketA();
//  loketB();

  String NomerAA = "A00";
  String NomerBB = "B00";

  if (pinA == 1  && nilaiAwal_a < nilaiA) {
    nilaiAwal_a ++;
    if (nilaiAwal_a < 10) {
      NomerAA = + "A0";
    } else if (nilaiAwal_a >= 10 && nilaiAwal_a < 31) {
      NomerAA = + "A";
    }
    nomer_aa = NomerAA + String(nilaiAwal_a);
    nmr_a = nomer_aa.c_str();
    dmd.selectFont(Arial_Black_16_ISO_8859_1);
  dmd.drawString( 4,  1, nmr_a, 3, GRAPHICS_NORMAL    );
    terbilang(15, 17, nilaiAwal_a);
  }

  //loket B
  else if (pinB == 1 && nilaiAwal_b < nilaiB) {
    nilaiAwal_b++;
    if (pinB < 10) {
      NomerBB = + "B0";
    } else if (nilaiAwal_b >= 10 && nilaiAwal_b < 31) {
      NomerBB = + "B";
    }
    nomer_bb = NomerBB + String(nilaiAwal_b);
    nmr_b = nomer_bb.c_str();
      dmd.selectFont(Arial_Black_16_ISO_8859_1);
  dmd.drawString( 36,  1, nmr_b, 3, GRAPHICS_NORMAL    );
    terbilang(16, 18, nilaiAwal_b);
  }

  if (panggilulangA == 1 && nilaiAwal_a> 0) {
    terbilang(15, 17, nilaiAwal_a);
  }
  else if (panggilulangB == 1 && nilaiAwal_b >0) {
    terbilang(16, 18, nilaiAwal_b);
  }

   if (nilaiAwal_a > 30) {
        nilaiAwal_a = 0;
      }
       if (nilaiAwal_b > 30) {
        nilaiAwal_b = 0;
      }

      if(resetloket = 1){
        nilaiAwal_a = 0;
        nilaiAwal_b = 0;
        }

  //terbilang(16, 18, nilaiB);


}

void loketA() {
  dmd.selectFont(Arial_Black_16_ISO_8859_1);
  dmd.drawString( 4,  1, nmr_a, 3, GRAPHICS_NORMAL    );
}

void loketB() {
  dmd.selectFont(Arial_Black_16_ISO_8859_1);
  dmd.drawString( 36,  1, nmr_b, 3, GRAPHICS_NORMAL    );
}


void terbilang(int antriannya , int keloket, int nilaipanggil) {

  if (nilaipanggil < 10) {
    mp3.play(antriannya);
    delay(1700);
    mp3.play(nilaipanggil);
    delay(1500);
    mp3.play(keloket);
    delay(3500);
  } else if (nilaipanggil == 10) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(10);
    delay(2700);
    mp3.play(keloket);
    delay(3500);
  } else if (nilaipanggil == 11) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(11);
    delay(2700);
    mp3.play(keloket);
    delay(3500);
  } else if (nilaipanggil > 11 and nilaipanggil < 20) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(nilaipanggil - 10);
    delay(1400);
    mp3.play(belas);
    delay(1350);
    mp3.play(keloket);
    delay(3500);
  } else  if (nilaipanggil == 20) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(2);
    delay(1600);
    mp3.play(puluh);
    delay(1000);
    mp3.play(keloket);
    delay(3500);
  } else if (nilaipanggil > 20 and nilaipanggil < 30) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play((nilaipanggil - (nilaipanggil % 10)) / 10);
    delay(1500);
    mp3.play(puluh);
    delay(1000);
    mp3.play(nilaipanggil % 10);
    delay(1600);
    mp3.play(keloket);
    delay(3500);
  } else if (nilaipanggil == 30) {
    mp3.play(antriannya);
    delay(2700);
    mp3.play(3);
    delay(1000);
    mp3.play(puluh);
    delay(1000);
    mp3.play(keloket);
    delay(3500);
  }
  //
  //  Serial.print("Nilai Awal = ");
  //  Serial.println(nilaiAwal_a);
  //  if ( nilaiAwal_a > 30 or nilaiAwal_b > 30) {
  //
  //    nilaiAwal_a = 0;
  //    nilaiAwal_b = 0;
}
//    panelA = false;
//  panelB = false;

//}
