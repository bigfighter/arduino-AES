#!/usr/bin/env python3

import Crypto.Cipher.AES, Crypto.Util.Counter, random, serial, sys

def generate_random_key():
	return bytes(random.randrange(256) for i in range(32))

with serial.Serial(sys.argv[1], 9600) as f:
	key = generate_random_key()

	f.write(key)
	f.write(bytes([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]))
	f.flush()

	aes = Crypto.Cipher.AES.new(
		key=key,
		mode=Crypto.Cipher.AES.MODE_CTR,
		counter=Crypto.Util.Counter.new(128)
	)
	while True:
		message = input('User input: ')
		result = []
		for i in message.encode('utf-8'):
			f.write(bytes([i]))
			result.append(ord(f.read(1)))
		print('Encrypted : %s' % ' '.join('%02X' % i for i in result))
		print('Decrypted : %s' % aes.decrypt(bytes(result)).decode())
