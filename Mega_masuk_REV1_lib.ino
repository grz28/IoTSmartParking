

/*            INI PAKE HC-SR04 DAN BUTTON UNTUK BUKA GERBANG
 *                   
 *                   KONFIGURASI PIN MEGA NODE MASUK
###########################################################################

HCSR =5v , GND          LEDB1 = 22   
TRIG1 4                 LEDK1 = 23
ECHO1 5                 LEDB2 = 24
TRIG2 6                 LEDK2 = 25
ECHO2 7                 LEDB3 = 26
TRIG3 8                 LEDK3 = 27   
ECHO3 9                 LEDB4 = 28   
TRIG4 10                LEDK4 = 29   
ECHO4 11                LEDB5 = 30
TRIG5 38                LEDK5 = 31
ECHO5 39                LEDB6 = 32
TRIG6 40                LEDK6 = 33
ECHO6 41                LEDB7 = 34
TRIG7 42                LEDK7 = 35
ECHO7 43                LEDB8 = 36
TRIG8 44                LEDK8 = 37
ECHO8 45

###########################################################################
*/

#include <NewPing.h>

#define TRIGGER_PIN1 4
#define ECHO_PIN1 5
#define TRIGGER_PIN2 6
#define ECHO_PIN2 7
#define TRIGGER_PIN3 8
#define ECHO_PIN3 9
#define TRIGGER_PIN4 10
#define ECHO_PIN4 11
#define TRIGGER_PIN5 38
#define ECHO_PIN5 39
#define TRIGGER_PIN6 40
#define ECHO_PIN6 41
#define TRIGGER_PIN7 42
#define ECHO_PIN7 43
#define TRIGGER_PIN8 44
#define ECHO_PIN8 45
#define MAX_DISTANCE 200 
#define LEDM1 22   
#define LEDH1 23
#define LEDM2 24
#define LEDH2 25
#define LEDM3 26
#define LEDH3 27   
#define LEDM4 28   
#define LEDH4 29   
#define LEDM5 48
#define LEDH5 49
#define LEDM6 32
#define LEDH6 33
#define LEDM7 34
#define LEDH7 35
#define LEDM8 46
#define LEDH8 47

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE);
NewPing sonar5(TRIGGER_PIN5, ECHO_PIN5, MAX_DISTANCE);
NewPing sonar6(TRIGGER_PIN6, ECHO_PIN6, MAX_DISTANCE);
NewPing sonar7(TRIGGER_PIN7, ECHO_PIN7, MAX_DISTANCE);
NewPing sonar8(TRIGGER_PIN8, ECHO_PIN8, MAX_DISTANCE);


String kirim, slot1, slot2, slot3, slot4, slot5, slot6, slot7, slot8;
int jarak1, jarak2, jarak3, jarak4, jarak5, jarak6, jarak7, jarak8;

void setup() {
  Serial.begin (9600);
  Serial1.begin(115200); // komunikasi serial dengan nodeMCU
 pinMode(LEDM1, OUTPUT);
 pinMode(LEDH1, OUTPUT);
 pinMode(LEDM2, OUTPUT);
 pinMode(LEDH2, OUTPUT);
 pinMode(LEDM3, OUTPUT);
 pinMode(LEDH3, OUTPUT);
 pinMode(LEDM4, OUTPUT);
 pinMode(LEDH4, OUTPUT);
 pinMode(LEDM5, OUTPUT);
 pinMode(LEDH5, OUTPUT);
 pinMode(LEDM6, OUTPUT);
 pinMode(LEDH6, OUTPUT);
 pinMode(LEDM7, OUTPUT); 
 pinMode(LEDH7, OUTPUT);
 pinMode(LEDM8, OUTPUT); 
 pinMode(LEDH8, OUTPUT);
}


void ping1(){
jarak1 = sonar1.ping_cm();  
Serial.print(sonar1.ping_cm());
Serial.print("cm :");
  if (jarak1 >= 200 || jarak1 <= 0){
    digitalWrite(LEDM1,LOW); //ketika slot terpakai
    digitalWrite(LEDH1,LOW);
    Serial.println("s1 tidak terjangkau");
    slot1=("tidak terjangkau");
  }
else if (jarak1 <= 4) {  // This is where the LED On/Off happens
    digitalWrite(LEDM1,HIGH); //ketika slot terpakai
    digitalWrite(LEDH1,LOW);
    slot1=("terpakai");
    Serial.println("s1 terpakai");
  }
  else if (jarak1 > 4){
    digitalWrite(LEDM1,LOW);
    digitalWrite(LEDH1,HIGH);
    slot1=("kosong");
    Serial.println("s1 kosong");
  }
  }


void ping2(){
  jarak2 = sonar2.ping_cm(); 
Serial.print(sonar2.ping_cm());
Serial.print("cm :");
   if (jarak2 >= 200 || jarak2 <= 0){
    Serial.println("s2 tidak terjangkau");
    digitalWrite(LEDM2,LOW); //ketika slot terpakai
    digitalWrite(LEDH2,LOW);
    slot2=("tidak terjangkau");
   }
 else if (jarak2 <= 4) {  // This is where the LED On/Off happens
    digitalWrite(LEDM2,HIGH); //ketika slot terpakai
    digitalWrite(LEDH2,LOW);
    slot2=("terpakai");
    Serial.println("s2 terpakai");
  }
  else if (jarak2 > 4){
    digitalWrite(LEDM2,LOW);
    digitalWrite(LEDH2,HIGH);
    slot2=("kosong");
    Serial.println("s2 kosong");
  }
   
}

void ping3(){
jarak3 = sonar3.ping_cm();   
Serial.print(sonar3.ping_cm());
Serial.print("cm :");
 if (jarak3 >= 200 || jarak3 <= 0){
    Serial.println("s3 tidak terjangkau");
    digitalWrite(LEDM3,LOW); //ketika slot terpakai
    digitalWrite(LEDH3,LOW);
    slot3=("tidak terjangkau");
 }
 else if (jarak3 <= 4) {  // This is where the LED On/Off happens
    digitalWrite(LEDM3,HIGH); //ketika slot terpakai
    digitalWrite(LEDH3,LOW);
    slot3=("terpakai");
    Serial.println("s3 terpakai");
  }
  else if (jarak3 > 4){
    digitalWrite(LEDM3,LOW);
    digitalWrite(LEDH3,HIGH);
    slot3=("kosong");
    Serial.println("s3 kosong");
  }
 
}

void ping4(){
jarak4 = sonar4.ping_cm();   
Serial.print(sonar4.ping_cm());
Serial.print("cm :");
  if (jarak4 >= 200 || jarak4 <= 0){
    Serial.println("s4 tidak terjangkau");
    digitalWrite(LEDM4,LOW); //ketika slot terpakai
    digitalWrite(LEDH4,LOW);
    slot4=("tidak terjangkau");
  }
 else if (jarak4 <= 4) {  // This is where the LED On/Off happens
    digitalWrite(LEDM4,HIGH); //ketika slot terpakai
    digitalWrite(LEDH4,LOW);
    slot4=("terpakai");
    Serial.println("s4 terpakai");
  }
  else if (jarak4 > 4){
    digitalWrite(LEDM4,LOW);
    digitalWrite(LEDH4,HIGH);
    slot4=("kosong");
    Serial.println("s4 kosong");
  }
  
}

void ping5(){
jarak5 = sonar5.ping_cm();   
Serial.print(sonar5.ping_cm());
Serial.print("cm :");
 if (jarak5 >= 200 || jarak5 <= 0){
    Serial.println("s5 tidak terjangkau");
    digitalWrite(LEDM5,LOW); //ketika slot terpakai
    digitalWrite(LEDH5,LOW);
    slot5=("tidak terjangkau");
  }
 else if (jarak5 <= 4) {  // This is where the LED On/Off happens
    digitalWrite(LEDM5,HIGH); //ketika slot terpakai
    digitalWrite(LEDH5,LOW);
    slot5=("terpakai");
    Serial.println("s5 terpakai");
  }
  else if (jarak5 > 4){
    digitalWrite(LEDM5,LOW);
    digitalWrite(LEDH5,HIGH);
    slot5=("kosong");
    Serial.println("s5 kosong");
  }

}

void ping6(){
jarak6 = sonar6.ping_cm();   
Serial.print(sonar6.ping_cm());
Serial.print("cm :");
  if (jarak6 >= 200 || jarak6 <= 0){
    Serial.println("s6 tidak terjangkau");
    digitalWrite(LEDM6,LOW); //ketika slot terpakai
    digitalWrite(LEDH6,LOW);
    slot6=("tidak terjangkau");
  }
 else if (jarak6 <= 4) {  // This is where the LED On/Off happens
    digitalWrite(LEDM6,HIGH); //ketika slot terpakai
    digitalWrite(LEDH6,LOW);
    slot6=("terpakai");
    Serial.println("s6 terpakai");
  }
  else if (jarak6 > 4){
    digitalWrite(LEDM6,LOW);
    digitalWrite(LEDH6,HIGH);
    slot6=("kosong");
    Serial.println("s6 kosong");
  }

}

void ping7(){
jarak7 = sonar7.ping_cm();   
Serial.print(sonar7.ping_cm());
Serial.print("cm :");
  if (jarak7 >= 200 || jarak7 <= 0){
    Serial.println("s7 tidak terjangkau");
    digitalWrite(LEDM7,LOW); //ketika slot terpakai
    digitalWrite(LEDH7,LOW);
    slot7=("tidak terjangkau");
  } 
 else if (jarak7 <= 4) {  // This is where the LED On/Off happens
    digitalWrite(LEDM7,HIGH); //ketika slot terpakai
    digitalWrite(LEDH7,LOW);
    slot7=("terpakai");
    Serial.println("s7 terpakai");
  }
  else if (jarak7 > 4){
    digitalWrite(LEDM7,LOW);
    digitalWrite(LEDH7,HIGH);
    slot7=("kosong");
    Serial.println("s7 kosong");
  }

}

void ping8(){
jarak8 = sonar8.ping_cm();   
Serial.print(sonar8.ping_cm());
Serial.print("cm :");
if (jarak8 >= 200 || jarak8 <= 0){
    Serial.println("s8 tidak terjangkau");
    digitalWrite(LEDM8,LOW); //ketika slot terpakai
    digitalWrite(LEDH8,LOW);
    slot8=("tidak terjangkau");
}
 else if (jarak8 <= 4) {  // This is where the LED On/Off happens
    digitalWrite(LEDM8,HIGH); //ketika slot terpakai
    digitalWrite(LEDH8,LOW);
    slot8=("terpakai");
    Serial.println("s8 terpakai");
  }
  else if (jarak8 > 4){
    digitalWrite(LEDM8,LOW);
    digitalWrite(LEDH8,HIGH);
    slot8=("kosong");
    Serial.println("s8 kosong");
  }

}

void loop() {
ping1();
ping2();
ping3();
ping4();
ping5();
ping6();
ping7();
ping8();
Serial.println("-----------");
kirim = String("Slot1:")+String(slot1 + ",")+String("Slot2:")+String(slot2+ ",")+String("Slot3:")+String(slot3+ ",")+String("Slot4:")+String(slot4+ ",")+String("Slot5:")+String(slot5+ ",")+String("Slot6:")+String(slot6+ ",")+String("Slot7:")+String(slot7+ ",")+String("Slot8:")+String(slot8+ ",");
Serial.println(kirim);
Serial1.println(kirim);
delay (2500); 
}
