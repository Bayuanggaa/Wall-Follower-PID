#include <NewPing.h>
#define BATAS_MAKSIMAL 200
#define TRIGGER_PIN 14
#define ECHO_PIN 12
#define setpoint 23

//Anggota kelompok 4 :
//1. Bayu Angga Rahadi
//2. Arta Deka Anindita
//3. Helmi Aprianto
//4. Fakur Yosi Alisandro


NewPing Left(TRIGGER_PIN,ECHO_PIN,BATAS_MAKSIMAL);

double jarakKiri,jarak,error,integral,errorTerakhir,derivative,jarakDepan,jarak1;

// NILAIN PID 
float kp = 6.5;
float ki = 0.5;
float kd = 0.6;

int totalkiri,totalkanan;

int nilai_pid, motor_speed;
//kecepatan motor
int rightspeed = 124;
int leftspeed = 124;

//left motor
const int ENA = 15;
const int IN1 = 2;
const int IN2 = 4;

//right motor
const int ENB = 19;
const int IN3 = 5;
const int IN4 = 18;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  jarakKiri = baca_jarak_kiri();
  error = jarakKiri - setpoint;
  
  Serial.print("Sensor : ");
  Serial.print(jarakKiri);
  Serial.print(" // ");
  Serial.print("Kiri : ");
  Serial.print(totalkiri);
  Serial.print(" // ");
  Serial.print("Kanan : ");
  Serial.print(totalkanan);
  Serial.print(" // ");
  Serial.print("PID : ");
  Serial.print(nilai_pid);
  Serial.print(" // ");  
  Serial.print("Error :");
  Serial.print(error);
  Serial.print(" // ");
  Serial.print("Integral : ");
  Serial.print(integral);
  Serial.print(" // ");
  Serial.print("Derivative : ");
  Serial.print(derivative);
  Serial.println(" // ");

  integral = error + integral;
   
  derivative = (error - errorTerakhir);

  nilai_pid = (kp * error + kd * derivative + ki * integral);
  
  errorTerakhir = error;

   if (nilai_pid >=80){
     nilai_pid = 80;    
   }
   if (nilai_pid <=-80){
     nilai_pid =-80;    
   }
  //motor_speed = constrain(nilai_pid, -80, 80);  
   totalkiri = leftspeed - (nilai_pid);
   totalkanan = rightspeed + nilai_pid;
   forward(totalkiri, totalkanan);


    
}
//-------FUNGSI---------------
void forward(int speed1, int speed2) {
  // Menentukan nilaikecepatan maju; max =  nilai min = 0
  if ( speed1 < 0 ) {
    speed1 = 0;   
  }
  if ( speed1 > 250 ) {  
    speed1 = 250;
  }
  if (speed2 < 0) {
    speed2 = 0;  
  }
  if (speed2 > 250) {
    speed2 = 250;
  }
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed1);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed2);
}
//-------JARAK---------------------

float baca_jarak_kiri() {
  int Pengulangan = 1;
  float durasi;
  durasi = Left.ping_median(Pengulangan);
  jarak = (durasi / 2) * 0.0343;
  return jarak;
}