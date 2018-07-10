#include <aes.h>

int c = 0;

AES* aes;

void setup() {
  Serial.begin(9600);
  aes = new AES();
}

void loop() {
  while (Serial.available() > 0) {
    unsigned char msg = Serial.read();

    if (c < 32) {
      // the first 32 bytes will be the key
      aes->key[c] = msg;
    } else if (c < 32+16) {
      // the next 16 bytes will be the counter
      aes->counter[c-32] = msg;
    } else {
      // everything after that is payload to be encrypted
      if (c == 32+16) {
        aes->reset();
      }
      aes->process(&msg);
      Serial.write(msg);
      // to change the key/counter, press the reset button on the Arduino
    }
    if (c < 32+16+1) {
      c++;
    }
  }
}
