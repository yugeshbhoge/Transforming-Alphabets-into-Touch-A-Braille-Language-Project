#include <Servo.h>
#include <SoftwareSerial.h>
// Define motor control constants
const int motorPins[6] = {3, 5, 6, 9, 10, 11};
Servo motors[6];
// Braille Alphabet Mapping (a-z)
bool brailleAlphabet[26][6] = {
{1, 0, 0, 0, 0, 0}, // a
{1, 1, 0, 0, 0, 0}, // b
{1, 0, 0, 1, 0, 0}, // c
{1, 0, 0, 1, 1, 0}, // d
{1, 0, 0, 0, 1, 0}, // e
{1, 1, 0, 1, 0, 0}, // f
{1, 1, 0, 1, 1, 0}, // g
{1, 1, 0, 0, 1, 0}, // h
{0, 1, 0, 1, 0, 0}, // i
{0, 1, 0, 1, 1, 0}, // j
{1, 0, 1, 0, 0, 0}, // k
{1, 1, 1, 0, 0, 0}, // l
{1, 0, 1, 1, 0, 0}, // m
{1, 0, 1, 1, 1, 0}, // n
{1, 0, 1, 0, 1, 0}, // o
{1, 1, 1, 1, 0, 0}, // p
{1, 1, 1, 1, 1, 0}, // q
{1, 1, 1, 0, 1, 0}, // r
{0, 1, 1, 1, 0, 0}, // s
{0, 1, 1, 1, 1, 0}, // t
{1, 0, 1, 0, 0, 1}, // u
{1, 1, 1, 0, 0, 1}, // v
{0, 1, 0, 1, 1, 1}, // w
{1, 0, 1, 1, 0, 1}, // x
{1, 0, 1, 1, 1, 1}, // y
{1, 0, 1, 0, 1, 1} // z
};
void setup() {
Serial.begin(9600);
Serial.println("Hello Arduino\n");
for (int i = 0; i < 6; i++) {
motors[i].attach(motorPins[i]);
}
}
void loop() {
if (Serial.available() > 0) {
char input = Serial.read();
if (isAlpha(input)) {
bool* brailleDots = charToBraille(tolower(input));
controlMotors(brailleDots);
while (!Serial.available()) {
// Wait here until next input is available
delay(10); // Small delay to prevent locking up
}
}
}
}
bool* charToBraille(char input) {
return brailleAlphabet[input - 'a'];
}
void controlMotors(bool dots[6]) {
for (int i = 0; i < 6; i++) {
if (dots[i]) {
motors[i].write(0);
} else {
motors[i].write(90);
}
}
}
