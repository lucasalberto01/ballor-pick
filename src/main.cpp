#include <Arduino.h>
#include <PS4Controller.h>
#include <L298NX2.h>

#define IN1_A 34
#define IN2_A 35

#define IN1_B 32
#define IN2_B 33
L298NX2 motors(IN1_A, IN2_A, IN1_B, IN2_B);
void setup()
{
  Serial.begin(115200);
  PS4.begin("1a:2b:3c:01:01:01");
  Serial.println("Ready.");
}

void loop()
{
  // Below has all accessible outputs from the controller
  if (PS4.isConnected())
  {

    int lStick = PS4.LStickY(); // -127 to 127
    int rStick = PS4.RStickY(); // -127 to 127

    if (lStick < -50)
    {
      motors.backward();
    }
    else if (lStick > 50)
    {
      motors.forward();
    }
    else if (rStick < -50)
    {
      motors.forwardA();
      motors.backwardB();
    }
    else if (rStick > 50)
    {
      motors.backwardA();
      motors.forwardB();
    }
    else
    {
      motors.stop();
    }

    if (PS4.Charging()){
      Serial.println("The controller is charging");
    }
    if (PS4.Audio()){
        Serial.println("The controller has headphones attached");
    }
    if (PS4.Mic()){
      Serial.println("The controller has a mic attached");
    }

    Serial.printf("Battery Level : %d\n", PS4.Battery());
    // Remove it when you're not trying to see the output
    delay(10);
  }
}
