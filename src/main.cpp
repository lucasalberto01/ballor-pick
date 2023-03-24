#include "main.h"

#include <Arduino.h>

#include "motor.h"

#define MODE \
    MODE_BT  // Change this to MODE_PS4 if you want to use the PS4 controller

#if MODE == MODE_PS4  // PS4 controller

#include <PS4Controller.h>
PS4Controller PS4;

#endif

#if MODE == MODE_BT  // Bluetooth controller

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#endif

VespaMotors motors;

void setup() {
    Serial.begin(115200);

#if MODE == MODE_PS4
    PS4.begin("1a:2b:3c:01:01:01");
    Serial.println("Ready.");
#endif

#if MODE == MODE_BT
    SerialBT.begin("ESP32");
    Serial.println("The device started, now you can pair it with bluetooth!");
#endif
}

void loop() {
    int lStick = 0, rStick = 0;

#if MODE == MODE_PS4
    if (PS4.isConnected()) {
        lStick = PS4.LStickY();  // -127 to 127
        rStick = PS4.RStickY();  // -127 to 127

        Serial.printf("Battery Level : %d\n", PS4.Battery());
        move(lStick, rStick);
    }
#endif

#if MODE == MODE_BT
    if (SerialBT.available()) {
        char c = SerialBT.read();
        Serial.println(c);
        if (c == 'F') {
            motors.forward(100);
        } else if (c == 'L') {
            motors.turn(100, 0);
        } else if (c == 'R') {
            motors.turn(0, 100);
        } else if (c == 'B') {
            motors.backward(100);
        } else if (c == 'S') {
            motors.stop();
        }
    }
#endif
}
