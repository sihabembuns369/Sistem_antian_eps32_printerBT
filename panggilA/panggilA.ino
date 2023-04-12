//test pin ep8266 master antrian
#include <ESP8266WiFi.h>
#include <espnow.h>
#define BOARD_ID 2
#define pinA D5
#define pinPanggil D7
uint8_t broadcastAddress[] = { 0xC0, 0x49, 0xEF, 0xE7, 0xC7, 0x8C };
#define BOARD_ID 2
typedef struct struct_message {
    int id;
    int pinA;
    int pinPanggil;
} struct_message;

struct_message myData;
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nLast Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void setup() {
  Serial.begin(115200);
pinMode(pinA,INPUT);
pinMode(pinPanggil,INPUT);
WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } 
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);


}

void loop() {
  Serial.println(digitalRead(pinA));
  myData.id = BOARD_ID;
  myData.pinA = digitalRead(pinA);
  myData.pinPanggil = digitalRead(pinPanggil);
  esp_now_send(0, (uint8_t *) &myData, sizeof(myData));

}
