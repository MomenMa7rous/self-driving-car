#include <Arduino.h>
#include <stdlib.h>

class MX1580_motor
{
  uint8_t pin_a;
  uint8_t pin_b;
  
  public:
  MX1580_motor(uint8_t p_a,uint8_t p_b):pin_a(p_a),pin_b(p_b) {}

  void begin()
  {
    pinMode(pin_a,OUTPUT);
    pinMode(pin_b,OUTPUT);
    coast();
  }

  void move(int speed)
  {
    speed = constrain(speed,-255,255);

    if (speed > 0)
    {
      analogWrite(pin_a,(uint8_t)speed);
      analogWrite(pin_b,0);
      
    }
    else if(speed < 0)
    {
      analogWrite(pin_a,0);
      analogWrite(pin_b,(uint8_t) abs(speed));
    }
    else
    {
      coast();
    }
  }

  void coast()
  {
    analogWrite(pin_a,0);
    analogWrite(pin_b,0); 
  }

  void brake()
  {
    analogWrite(pin_a,255);
    analogWrite(pin_b,255);
  }
};

MX1580_motor left_motor(18, 19);
MX1580_motor right_motor(23, 32);


void setup() {
  Serial.begin(115200);
  left_motor.begin();
  right_motor.begin();

}

void loop() {
  left_motor.move(160);
  right_motor.move(160);
  delay(1200);

  left_motor.coast();
  right_motor.coast();
  delay(500);

  left_motor.move(-160);
  right_motor.move(-160);
  delay(1200);

  left_motor.brake();
  right_motor.brake();
  delay(1000);
}
