/* An implementation of AES in counter mode with a key length of 256 bits.

This code is designed to run on an Arduino.

The implementation has been tested for correctness,
but is likely to be prone to side-channel attacks.

In counter mode, the plaintext is XOR-ed with an encrypted counter,
thereby effectively using a one-time pad for the size of the plaintext:

	ciphertext = ecb(key, c++) ^ plaintext

Encryption is done the same way:

	plaintext = ecb(key, c++) ^ ciphertext

The counter (in this implementation) is blocksize = 128 bit long.

https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
https://en.wikipedia.org/wiki/Counter_mode#Counter_.28CTR.29
https://en.wikipedia.org/wiki/Side-channel_attack
*/
class AES {

	private:

		unsigned char enckey[32];
		unsigned char otp[16];
		unsigned char otpPos;

		void ecb(unsigned char* plaintext);
		unsigned char getNextCtrOtp();

	public:

		unsigned char key[32];
		unsigned char counter[16];

		void reset();
		void process(unsigned char* buffer);
};
