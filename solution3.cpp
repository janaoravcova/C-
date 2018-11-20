#include <iostream>
#include <limits>
#include <cmath>
#include <string>

using namespace std;

const int DUMMY_INT = -999;
const bool DUMMY_BOOL = false;
const string DUMMY_STRING = "";
const int WRONG_NUMBER = -99;

#ifndef _RIESENIE_H_
#define _RIESENIE_H_

enum NumberType {DECIMAL_INT, BINARY_INT, OCTAL_INT, HEXADECIMAL_INT};
#endif

//1. uloha
NumberType numberType(const string &number0) {
	int i=0;
	if (number0[0] == '-')
	{
		 i = 1;
		

	}
	else
	{
		 i = 0;
	}
		if (number0[i] == '0')
		{
			if (number0[i+1] == 'x')
			{
				return HEXADECIMAL_INT;
			}
		    if (number0[i+1] == 'b')
			{
				return BINARY_INT;
			}
			if (number0[i+1] != '\0')
			{
				return OCTAL_INT;
			}
			if (number0[i + 1] == '\0')
			{
				return DECIMAL_INT;
			}
			

		}
		else
		{
			return DECIMAL_INT;
		}
		
	

}

bool onlyDigits(const string &number) {
	if (number == "")
	{
		return false;
  }
	else
	{
		for (int i = 0; i < number.length(); i++)
		{
			if (number[i] >= 'a' && 'x' >= number[i] || number[i] <= 'X' && 'A' <= number[i] || number[i]==' ')
			{
				return false;
			}
		}
	}
	return true;
}

bool onlyBinaryDigits(const string &number) {
	if (number == "")
	{
		return false;

	}
	else
	{
		for (int i = 0; i < number.length(); i++)
		{
			if (number[i] != '0' && number[i] != '1')
			{
				return false;
			}
		}
		return true;
	}
}
bool notAllowed(const char c)
{
	if (c=='a'|| c=='b'|| c=='c' || c=='d' || c=='e' || c=='f' || c=='A' ||c=='B' || c=='C' || c=='D' || c=='E' || c=='F')
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool onlyOctalDigits(const string &number) {
	if (number == "")
	{
		return false;
  }
	else
	{
		for (int i = 0; i < number.length(); i++)
		{
			if (number[i] < '0' || number[i]>'7')
			{
	
					return false;
				
			}
		}
		return true;


	}
}

bool onlyHexadecimalDigits(const string &number) {
	if (number == "")
	{
		return false;
	}
	else
	{
		for (int i = 0; i < number.length(); i++)
		{
			if (number[i] < '0' || number[i]>'9')
			{
				if (notAllowed(number[i]))
				{
					return false;
				}
			}
		}
		return true;


	}
}
//2. uloha
bool correctNumber(const string &number0) {
	int i=0;
	string number;
	if (number0 == "") //empty string
	{
		return false;
	}
	if (number0[0] == '-')
	{
		number = number0.substr(1, number0.length() - 1);
		if (number.length() == 0) //only sign
		{
			return false;
		}
	}
	else
	{
		number = number0;
	}

	//find out what numeric system is used
	if (number[0] != '0') //decimal
	{
		if (onlyDigits(number.substr(1, number.length() - 1)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (number[0] == '0' && number[1] == 'b')//binary system 
	{
		if (onlyBinaryDigits(number.substr(2, number.length() - 1)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (number[0] == '0' && number[1] == 'x')//hexadecimal system
	{
		if (onlyHexadecimalDigits(number.substr(2, number.length() - 1)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (number[0] == '0') //octal numbers or just zero
	{
		if (number.length() == 1)
		{
			return true;
		}

		else if (onlyOctalDigits(number.substr(1, number.length() - 1)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

//3. uloha
string decimalNumberIntoDecimalString(int decimalNumber) {
	int remainder = 0;
	string str;
	int znamienko = 0;
	char znak;
	if (decimalNumber == 0 || decimalNumber==-0)
	{
		return "0";
	}
	if (decimalNumber < 0)
	{
		znamienko = 1;
		decimalNumber *= (-1);

	}


	while (decimalNumber > 0)
	{
		remainder = decimalNumber % 10;
		decimalNumber /= 10;
		znak = remainder + '0';
		//cout << znak << '\n';
		str = znak + str;

	}


	if (znamienko)
	{
		str = '-' + str;
	}


	return str;
}

string decimalNumberIntoNumberTypeString(int number, NumberType numberType) {
	string str;
	int remainder;
	char  c;
	int sign = 0;
	int letters[6] = { 'a','b','c','d','e','f' };
	if (number < 0)
	{
		sign = 1;
		number *= (-1);

	}

	if (numberType == BINARY_INT) //to binary
	{
		while (number > 0)
		{
			remainder = number % 2;
			number /= 2;
			c = remainder + '0';
			str = c + str;

		}
		str = "0b" + str;
		if (sign)
		{
			str = '-' + str;
		}
	}
	
	if (numberType == DECIMAL_INT)//to decimal
	{
		str = decimalNumberIntoDecimalString(number);
		if (sign)
		{
			str = '-' + str;
		}
	}

	if (numberType == OCTAL_INT) //to octal
	{
		while (number > 0)
		{
			remainder = ((double)number / 8 - number / 8) * 8;
			number = number / 8;
			c = remainder + '0';
			str = c + str;


		}
		str = '0' + str;
		if (sign)
		{
			str = '-' +str;
		}
	}

	if (numberType == HEXADECIMAL_INT)
	{
		while (number > 0)
		{
			remainder = number % 16;
			if (remainder > 9)
			{
				c = letters[remainder - 10];
			}
			else
			{
				c = remainder + '0';
			}
			number /= 16;
			str = c + str;

		}
		str = "0x" + str;
		if (sign)
		{
			str = '-' + str;
		}
	}

	return str;
}

//4. uloha
 long long conversion(string number, NumberType type)
{
	long long result = 0;
	int j = 0;
	int num = 0;
	int letters[] = { 10,11,12,13,14,15 };
	if (type == DECIMAL_INT)
	{
		for (int i = 0; i < number.length(); i++)
		{
			j = number.length() - 1 - i;
			num = number[i] - '0';
			result += num*pow(10, j);
		}
	}
	if (type == BINARY_INT)
	{

		for (int i = 0; i < number.length(); i++)
		{
			j = number.length() - 1 - i;
			if (number[i] == '1')
			{
				result += pow(2, j);
			}
		}

	}
	if (type == OCTAL_INT)
	{
		for (int i = 0; i < number.length() && result<2147483647 && result>=-2147483647; i++)
		{
			j = number.length() - 1 - i;
			num = number[i] - '0';
			//cout << result << '\n';
			result += num*pow(8, j);
		}
	}
	if (type == HEXADECIMAL_INT)
	{
		for (int i = 0; i < number.length(); i++)
		{
			j = number.length() - 1 - i;
			if ('0' <= number[i] && number[i] <= '9')
			{

				num = number[i] - '0';
				//cout << num << '\n';
				result += num*pow(16, j);
			}
			else if ('a' <= number[i] && number[i] <= 'z')
			{
				int l = (int)number[i];
				int k = l - 97;
				num = letters[k];
				//cout << num << '\n';
				result += num*pow(16, j);

			}
			else if ('A' <= number[i] && number[i] <= 'Z')
			{
				int l = (int)number[i];
				int k = l - 65;
				num = letters[k];
				//cout << num << '\n';
				result += num*pow(16, j);

			}
		}
	}
	return result;
}

bool numberTypeStringInNumericLimits(const string &numberInNumberType) {
	long long limit = numeric_limits<int>::max();
	long long limit_z = (-1)*(limit + 1);
	int cislo;
	string number="";
	int sign = 1;
	
	switch (numberType(numberInNumberType))
	{
	case DECIMAL_INT:
		if (numberInNumberType[0] == '-')
		{
			number = numberInNumberType.substr(1, numberInNumberType.length() - 1);
			sign *= (-1);
		}
		else
		{
			number = numberInNumberType;
		}
		if (!onlyDigits(number))
		{
			return false;
		}
		if (conversion(number, DECIMAL_INT) <= limit && limit_z<= conversion(number, DECIMAL_INT)*sign )
		{
			return true;
		}
		else
		{
			return false;
		}
	

	case BINARY_INT:
		if (numberInNumberType[0] == '-')
		{
			number = numberInNumberType.substr(1, numberInNumberType.length() - 1);
			sign *= (-1);
		}
		else
		{
			number = numberInNumberType;
		}

		 if (number[0] == '0' && number[1] == 'b')
		{
			number = number.substr(2, number.length() - 1);

		}
		
		if (!onlyBinaryDigits(number))
		{
			
			return false;
		}
	
		else if (conversion(number, BINARY_INT) <= limit && limit_z <= conversion(number, BINARY_INT)*sign)
		{
			return true;
		}
		else
		{
			//cout << conversion(number, BINARY_INT) << '\n';
			return false;
		}
	case HEXADECIMAL_INT:
		if (numberInNumberType[0] == '-')
		{
			number = numberInNumberType.substr(1, numberInNumberType.length() - 1);
			sign *= (-1);
		}

		else
		{
			number = numberInNumberType;
		}

		if (number[0] == '0' && number[1] == 'x')
		{
			number = number.substr(2, number.length() - 1);

		}

		if (!onlyHexadecimalDigits(number))
		{
			return false;
		}
		
	    if (conversion(number, HEXADECIMAL_INT) <= limit && limit_z <= conversion(number, HEXADECIMAL_INT)*sign)
		{
			return true;
		}
		else
		{
			return false;
		}
	case OCTAL_INT:
		if (numberInNumberType[0] == '-')
		{
			number = numberInNumberType.substr(1, numberInNumberType.length() - 1);
			sign *= (-1);
		}
		else
		{
			number = numberInNumberType;
		}
		if (!onlyOctalDigits(number))
		{
			return false;
		}
		else if (conversion(number, OCTAL_INT) <= limit && limit_z <= conversion(number, OCTAL_INT)*sign)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

int numberTypeStringIntoDecimal(const string &numberInNumberType) {
	long long limit = numeric_limits<int>::max();
	long long limit_z = (-1)*(limit + 1);
	int cislo;
	string number = "";
	int sign = 1;

	switch (numberType(numberInNumberType))
	{
	case DECIMAL_INT:
		if (numberInNumberType[0] == '-')
		{
			number = numberInNumberType.substr(1, numberInNumberType.length() - 1);
			sign *= (-1);
		}
		else
		{
			number = numberInNumberType;
		}
		if (!onlyDigits(number))
		{
			return -99;
		}
		if (conversion(number, DECIMAL_INT) <= limit && limit_z <= conversion(number, DECIMAL_INT)*sign)
		{
			return sign*conversion(number, DECIMAL_INT);
		}
		else
		{
			return -99;
		}


	case BINARY_INT:
		if (numberInNumberType[0] == '-')
		{
			number = numberInNumberType.substr(1, numberInNumberType.length() - 1);
			sign *= (-1);
		}
		else
		{
			number = numberInNumberType;
		}

		if (number[0] == '0' && number[1] == 'b')
		{
			number = number.substr(2, number.length() - 1);

		}

		if (!onlyBinaryDigits(number))
		{

			return -99;
		}

		else if (conversion(number, BINARY_INT) <= limit && limit_z <= conversion(number, BINARY_INT)*sign)
		{
			return sign*conversion(number, BINARY_INT);
		}
		else
		{
			//cout << conversion(number, BINARY_INT) << '\n';
			return -99;
		}
	case HEXADECIMAL_INT:
		if (numberInNumberType[0] == '-')
		{
			number = numberInNumberType.substr(1, numberInNumberType.length() - 1);
			sign *= (-1);
		}

		else
		{
			number = numberInNumberType;
		}

		if (number[0] == '0' && number[1] == 'x')
		{
			number = number.substr(2, number.length() - 1);

		}

		if (!onlyHexadecimalDigits(number))
		{
			return -99;
		}

		if (conversion(number, HEXADECIMAL_INT) <= limit && limit_z <= conversion(number, HEXADECIMAL_INT)*sign)
		{
			return sign*conversion(number, HEXADECIMAL_INT);
		}
		else
		{
			return -99;
		}
	case OCTAL_INT:
		if (numberInNumberType[0] == '-')
		{
			number = numberInNumberType.substr(1, numberInNumberType.length() - 1);
			sign *= (-1);
		}
		else
		{
			number = numberInNumberType;
		}
		if (!onlyOctalDigits(number))
		{
			return -99;
		}
	    if (conversion(number, OCTAL_INT) <= limit && limit_z <= conversion(number, OCTAL_INT)*sign)
		{
			return sign*conversion(number, OCTAL_INT);
		}
		else
		{
			return -99;
		}
	}
}


//5. uloha
string conversionFromOneNumberTypeIntoOther(const string &inputNumber, NumberType numberType) {
	if (!correctNumber(inputNumber))
	{
		return "Wrong number";
  }
	if (!numberTypeStringInNumericLimits(inputNumber))
	{
		return "Out of limit";
	}
	else
	{
		if (numberType == DECIMAL_INT)
		{
			return decimalNumberIntoDecimalString(numberTypeStringIntoDecimal(inputNumber));
		}
		else if (numberType == BINARY_INT)
		{
			return decimalNumberIntoNumberTypeString(numberTypeStringIntoDecimal(inputNumber), BINARY_INT);
		}
		else if (numberType == OCTAL_INT)
		{
			return decimalNumberIntoNumberTypeString(numberTypeStringIntoDecimal(inputNumber), OCTAL_INT);
		}
		else if (numberType == HEXADECIMAL_INT)
		{
			return decimalNumberIntoNumberTypeString(numberTypeStringIntoDecimal(inputNumber), HEXADECIMAL_INT);
		}

	}
}
