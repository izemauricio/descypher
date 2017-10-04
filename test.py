from Crypto.Cipher import AES
import binascii

keys = []

# le o arquivo, formate e verifica se é multiplo de 16
def ChecaSeEhMultiplo():
	f = open("original.txt", "r")
	lines = f.readlines()
	msg = ''
	for line in lines:
		msg += (line[:len(line)-1])
	print(msg)
	print(len(msg))
	print(len(msg)%16)

# testa se o algoritmo escolhido esta correto
def TestaAlgoritmo():
	key = b"essasenhaehfraca"
	msg = b"Texto para teste"
	print("ORIGINAL: " + msg.hex())
	machine = AES.new(key, AES.MODE_ECB)
	criptado = machine.encrypt(msg)
	#print(criptado)
	c = criptado.hex().upper()
	print("CRIPTOGRAFADO: " + c)
	if(c == "A506A19333F306AC2C62CBE931963AE7"):
		print("OK")
	else:
		print("NO")
	#print(criptado.decode("latin-1"))

'''
>>> 
help(string)
...
DATA
    ascii_letters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    ascii_lowercase = 'abcdefghijklmnopqrstuvwxyz'
    ascii_uppercase = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    digits = '0123456789'
    hexdigits = '0123456789abcdefABCDEF'
    octdigits = '01234567'
    printable = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c'
    punctuation = '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
    whitespace = ' \t\n\r\x0b\x0c'
'''

# cria um dicionario
def CriaDicionario():
	keybase = "Key2Group17"
	'''
	# all lower cases
	for i5 in range(ord('a'), ord('z')+1):
		for i4 in range(ord('a'), ord('z')):
			for i3 in range(ord('a'), ord('z')):
				for i2 in range(ord('a'), ord('z')):
					for i1 in range(ord('a'), ord('z')):
						keys.append(keybase + chr(i5) + chr(i4) + chr(i3) + chr(i2) + chr(i1))
	'''
	letters2 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
	letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	for i5 in letters:
		#print(i5)
		for i4 in letters:
			for i3 in letters:
				for i2 in letters:
					for i1 in letters:
						keys.append(keybase + i5 + i4 + i3 + i2 + i1)
	# print("QUANTIDADE DE WORDS: " + len(keys))

# cria um dicionario
def CriaDicionario2(keybase, letters):
	for i3 in letters:
		for i2 in letters:
			for i1 in letters:
				keys.append(keybase + chr(i3) + chr(i2) + chr(i1))

# faz brute force ate achar a chave
def BruteForce():
	texto = "5D80B22B7AE8ECD2FE85DB34AF46436069F1959B24998C569078BDB9B137E7B7C098A1866273C219EAAF296B68EE224565A3D704BDEC51638A880002DC6188A97D007FD1D4F58C2794017272433F7235C31344841374F957485B39AA8D3DF4A2C6DE4332405BE51C065D38106840674C775C343D8068C5AEE95327B57DF0955C4C8B340B5C9848540DCD0494BAAB2ABBDC8D4D92105F757C02B6BB3189298BE172FF4D6B40435134FC677047C44D440C3D8D5E62FD8A2340085C93AFC53EF733FBA235553C89CCDFF3D478BAF467D3F15859643DF3CD2BFA74A561F8A8F822AE8FF5F3827BBA50AFC39CB2E390CAC23A2A9A291072E21186D5E144CAB7B3FE06EB0D68B27D5BD8E0A2EA37AD3AEC4F1E657264F53D53C45C81DFD9DAE9A8B1F3606E229B6F3DB0EC43949101110E7667AB33A862B82C5CB44694224099E2C8AA63704ACCDB22CDCE266B636CC400485C"
	textobyte = b"5D80B22B7AE8ECD2FE85DB34AF46436069F1959B24998C569078BDB9B137E7B7C098A1866273C219EAAF296B68EE224565A3D704BDEC51638A880002DC6188A97D007FD1D4F58C2794017272433F7235C31344841374F957485B39AA8D3DF4A2C6DE4332405BE51C065D38106840674C775C343D8068C5AEE95327B57DF0955C4C8B340B5C9848540DCD0494BAAB2ABBDC8D4D92105F757C02B6BB3189298BE172FF4D6B40435134FC677047C44D440C3D8D5E62FD8A2340085C93AFC53EF733FBA235553C89CCDFF3D478BAF467D3F15859643DF3CD2BFA74A561F8A8F822AE8FF5F3827BBA50AFC39CB2E390CAC23A2A9A291072E21186D5E144CAB7B3FE06EB0D68B27D5BD8E0A2EA37AD3AEC4F1E657264F53D53C45C81DFD9DAE9A8B1F3606E229B6F3DB0EC43949101110E7667AB33A862B82C5CB44694224099E2C8AA63704ACCDB22CDCE266B636CC400485C"
	latin = bytearray.fromhex(texto).decode("latin-1")
	#print(latin)
	# key = b"Key2Group17aaaaa"
	for key in keys:
		machine = AES.new(key.encode(), AES.MODE_ECB)
		claro = machine.decrypt(textobyte)
		# print(claro.hex().upper())
		# print(claro.decode("latin-1"))
		clarolatin = claro.decode("latin-1")
		if (clarolatin.find(" que ") != -1):
			print(key)
			print(claro)
			print(clarolatin)
			input('APERTE ENTER PARA CONTINUAR')
		if (clarolatin.find("cripto") != -1):
			print(key)
			print(claro)
			print(clarolatin)
			input('APERTE ENTER PARA CONTINUAR')
		if (clarolatin.find("agora") != -1):
			print(key)
			print(claro)
			print(clarolatin)
			input('APERTE ENTER PARA CONTINUAR')

# imprime o binario de uma string
def strToBin():
	st = 'teste'
	l = list(st)
	print(l)
	t = ''
	for x in l:
	   t+= format(ord(x),'b')
	print(t)

#TestaAlgoritmo()
#ChecaSeEhMultiplo()
#CriaDicionario()
#BruteForce()

letters = range(33, 126)
#letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#letters = "aeiouAEIOUWwBbrR123098"
for i5 in letters:
	for i4 in letters:
		print("Iteracao: " + chr(i5) + " " + chr(i4) + " - ", i5)
		keybase = "Key2Group17" + chr(i5) + chr(i4)
		CriaDicionario2(keybase, letters)
		BruteForce()
		print(keys[0])
		print(keys[44])
		del keys[:]