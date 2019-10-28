#include <M5Stack.h>
#include <esp_now.h>
#include <WiFi.h>
#define CHANNEL 1

#define RIGHT_ARM_PIN 22
#define LEFT_ARM_PIN 21

static bool is_pushued_stick_c = false;

void initESPNow()
{
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
}

void configDeviceAP()
{
  char* SSID = "slave_1";
  bool result = WiFi.softAP(SSID, "slave_1_Password", CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
  }
}

void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  char macStr[18];
  //snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
  //         mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  //Serial.print("Last Packet Recv from: "); Serial.println(macStr);
  Serial.print("Recv Data: ");
  for(uint32_t i = 0; i < data_len; i++){
    Serial.print(""); Serial.print(data[i]);
  }
  Serial.println("");

  if(data[0] == 1){
    is_pushued_stick_c = true;
  }else{
    is_pushued_stick_c = false;
  }
}

void setupESPNow()
{
  Serial.println("ESPNow/Basic/Slave");

  WiFi.mode(WIFI_AP);  //Set device in AP mode to begin with
  configDeviceAP();  // configure device AP mode
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());  // This is the mac address of the Slave in AP Mode
  initESPNow();  // Init ESPNow with a fallback logic
  esp_now_register_recv_cb(onDataRecv);  // Once ESPNow is successfully Init, we will register for recv CB to get recv packer info.
}

void setupVibrationMotor()
{
  pinMode(RIGHT_ARM_PIN, OUTPUT);
  digitalWrite(RIGHT_ARM_PIN, 0);

  pinMode(LEFT_ARM_PIN, OUTPUT);
  digitalWrite(LEFT_ARM_PIN, 0);
}

void setup()
{
  Serial.begin(115200);
  // Power ON Stabilizing...
  delay(500);
  M5.begin();
  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);

  setupVibrationMotor();

  setupESPNow();
}

void loop() {
  
  if(is_pushued_stick_c){
    digitalWrite(LEFT_ARM_PIN, 1);
    digitalWrite(RIGHT_ARM_PIN, 1);
  }else{
    digitalWrite(RIGHT_ARM_PIN, 0);
    digitalWrite(LEFT_ARM_PIN, 0);
  }
  
  delay(100);
  M5.update();
}
