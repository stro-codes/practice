# this is a test program for python

def main():
	print("this is a test program")

	test = "true"

	x = 1
	y = 0

	print(x + y)

	question = input("how much money is on the table")
	numero = int(question)

	if(numero > 3):
		print("hey this test is pretty good")
	elif(numero < 3):
		print("wow this test sucks")
	else:
		print("test is true");
		
	
def sum(one, two):
	return one + two
	
	
def minus(one, two):
	return one - two