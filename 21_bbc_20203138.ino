#include <Servo.h>
#define PIN_SERVO 10

Servo myservo;

// Arduino pin assignment
#define PIN_IR A0

//Framework setting
#define _DIST_MIN 100
#define _DIST_MAX 410

//Servo range
#define _DUTY_MIN 950
#define _DUTY_NEU 1480
#define _DUTY_MAX 1500

//#define _DIST_ALPHA 0.0

//#define _SERVO_ANGLE 30.0
//#define _SERVO_SPEED 30.0


int a, b; // unit: mm

void setup() {
// initialize GPIO pins
  myservo.attach(PIN_SERVO);
  
// initialize serial port
  Serial.begin(57600);

  a = 70;
  b = 280;
  myservo.writeMicroseconds(1500);
}

  float ir_distance(void){ // return value unit: mm
    float val;
    float volt = float(analogRead(PIN_IR));
    val = ((6762.0/(volt-9.0))-4.0) * 10.0;
    return val;
  }

void loop() {
  float raw_dist = ir_distance();
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);
  Serial.print("min:100,max:450,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
  
  if(dist_cali > 255) {
    myservo.writeMicroseconds(_DUTY_MIN);
  }
  else {
    myservo.writeMicroseconds(_DUTY_MAX);
  }
  delay(20);
}
