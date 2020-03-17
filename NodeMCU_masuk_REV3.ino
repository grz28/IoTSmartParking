////////////////////////// SETUP PIN NODEMCU MASUK //////////////////////////////


// Pinout RFID                         Pinout Servo                Pinout LCD
// RST RFID ke D3 NodeMCU              VCC ke 5V                   VCC ke 5V
// 3.3V RFID ke 3.3V NodeMCU           Gnd ke GND                  Gnd ke Gnd
// SDA ke Pin D4    /SD3               Data servo 1 ke Pin D8      SDA ke Pin D2
// MOSI ke Pin D7   /SD0               Data servo 2 ke pin D3      SCL ke Pin D1
// SCK ke Pin D5    /SCLK
// MISO ke Pin D6   /SD1

// Pinout komunikasi serial :
// TX - RX1 MEGA
// RX - TX1 MEGA

/////////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

WiFiClient client;
Servo servo1;
//Servo servo2;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SS_PIN 2 // D4 awal pake GPIO2
#define RST_PIN 10 //D3 =0

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
String kirim;
String request_string;
const char* host = "192.168.43.120"; //IP Komputer
HTTPClient http;
String strID, rfidUid, data, dataLDR;
//unsigned long timenow = 0;
int index1, index2;
String dat1="";
//String dat2="";

void setup() {
  Serial.begin(115200);
//  Serial1.begin(115200);
  lcd.clear();
  lcd.init();
  lcd.backlight();
  servo1.attach(15);  //D8 awalnya, coba D4 (GPIO2)
 // servo2.attach(16); //D0 awalnya D3
  SPI.begin();
  rfid.PCD_Init();
  konek();
}
 
void konek() {
  WiFi.disconnect();
  WiFi.begin("syntheticsax","lolrektbeetch"); //ssid + pw
    while ((!(WiFi.status() == WL_CONNECTED))){ //digunakan untuk reconnect
    delay(300);
   }
}

void autentikasi(){
        
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  } 
  strID.toUpperCase();
  Serial.println(strID); //RFID dari NodeMCU 
       
baca_database(strID);
aktuator();
}

void baca_database(String id)
{
  if (!client.connect(host, 80)) {
    Serial.println("Gagal Baca DB");
    return;
  }

  request_string = "/esp82661/rfidread1.php?idcard=";
  request_string += id;

  Serial.print("requesting URL: ");
  Serial.print(request_string);
  client.print(String("GET ") + request_string + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
 }

void aktuator(){ 
// butuh penjelasan kinerja function ini//
  while (client.available()>0){
    delay(10);
    char c = client.read();
    data+=c;
  }
   if (data.length() > 0) {
    Serial.println(data);
    index1 = data.indexOf("%"); //ini ngambil dari DB rfidread.php?
    index2 = data.indexOf("%", index1 + 1);
    dat1 = data.substring(index1 + 1, index2);
    Serial.print("dat1:");
    Serial.println(dat1);
    data = "";
    lcd.setCursor(0, 1);
    lcd.print(dat1); //     disini bisa ditambahkan LDR sebagai trigger servo nutup, baca lewat mega.
    if (dat1.indexOf("Silahkan Masuk") >=0) {
      servo1.write(90);
      delay(5000);
    }
    else if (dat1.indexOf("Parkir") >=0) {
      servo1.write(0);
      delay(3000);  
    }
    else if (dat1.indexOf("Belum") >=0) {
      servo1.write(0);
      delay(3000);  
    }
    else if (dat1.indexOf("ID") >=0) {
      servo1.write(0);
      delay(3000);  
    }
    else {
       servo1.write(0);
//       servo2.write(0);
    }
  }
}

void lokasi(String data1)
{ 
  
  if (!client.connect(host, 80)) {
    Serial.println("Gagal Update Lokasi");
    return;
  }

  request_string = "/esp82661/terima.php?data=";
  request_string += data1;

  Serial.print("requesting URL: ");
  Serial.print(request_string);
  client.print(String("GET ") + request_string + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
 }

 void baca_sensor (){
  //kode iki ditokno
    while (Serial.available()>0) {
       dataLDR = Serial.readString();
       //Serial.println(dataLDR);
    }
    if (dataLDR.length() <= 0) {
       Serial.println("Tidak ada komunikasi serial");
       delay(2000);
    }
    else if (dataLDR.length() > 0) {
       lokasi(dataLDR);
       delay(2000);
    }
 }

void parkir_penuh (){
  cek_parkir("cek");
  while (client.available()>0){
    delay(10);
    char c = client.read();
    data+=c;
  }
   if (data.length() > 0) {
    Serial.println(data);
    index1 = data.indexOf("%"); //ini ngambil dari DB rfidread.php?
    index2 = data.indexOf("%", index1 + 1);
    dat1 = data.substring(index1 + 1, index2);
    Serial.print("dat1:");
    Serial.println(dat1);
    data = "";
    lcd.setCursor(0,0);
    lcd.print(dat1); //     disini bisa ditambahkan LDR sebagai trigger servo nutup, baca lewat mega.
    if (dat1.indexOf("Parkir") >=0) {
      servo1.write(0);
      delay(2000);  
    }
    else {
       servo1.write(0);
//     servo2.write(0);
    }
  }
}
 
void cek_parkir (String datap){
if (!client.connect(host, 80)) {
    Serial.println("Gagal Baca Jumlah parkir");
    return;
  }

  request_string = "/esp82661/penuh.php?cek=";
  request_string += datap;

  Serial.print("requesting URL: ");
  Serial.print(request_string);
  client.print(String("GET ") + request_string + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  lcd.clear();
  //lcd.print("Tap Kartu Anda:");
 if ((!(WiFi.status() == WL_CONNECTED))) {
    Serial.println("Gagal Konek ke WiFi");
    lcd.setCursor(0, 0);
    lcd.print("No WiFi"); 
    lcd.setCursor(0,1); 
    lcd.print("Hub. Operator");
    delay(3000);
    return;
  }
else {        
  parkir_penuh();
  autentikasi();
  servo1.write(0);
 // servo2.write(0);
  baca_sensor();
 }
}




