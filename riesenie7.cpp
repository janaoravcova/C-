#include <iostream>
#include <string>
#include <list>
using namespace std;

//#include "riesenie7.h"

//Toto je vlozeny hlavickovy subor riesenie7.h
#if !defined( _RIESENIE_H_ )
const string ZERO("0");
const string SMALLEST_NUMBER ("-9999999999999");
const string BIGGEST_NUMBER ("9999999999999");

//1.uloha
class VeryLargeNumber {
  string number;
  void changeNumberSign();
public:
  VeryLargeNumber(const string &input = ZERO);
  int numberOfDigits() const;
  bool negativeNumber() const;
  void put(const string &input);
  string value() const;
  bool allZeros(const string &input);
  //2.uloha
  VeryLargeNumber(long long inputNumber);
  VeryLargeNumber(const VeryLargeNumber &inputNumber);
  VeryLargeNumber &operator=(const VeryLargeNumber &inputNumber);
  VeryLargeNumber(VeryLargeNumber &&inputNumber);
  VeryLargeNumber &operator=(const string &inputNumber);
  VeryLargeNumber &operator=(VeryLargeNumber &&inputNumber);
  //3.uloha
  bool operator==(const VeryLargeNumber &inputNumber) const;
  bool operator==(const string &inputNumber) const;
  bool operator<(const VeryLargeNumber &inputNumber) const;
  bool operator<(const string &inputNumber) const;
  //5.uloha
  string minimum(const VeryLargeNumber *arrayOfNumbers, int sizeOfArray) const;
  string maximum(const VeryLargeNumber *arrayOfNumbers, int sizeOfArray) const;
  //6.uloha
  const VeryLargeNumber operator*(const VeryLargeNumber &inputNumber);
};
//4.uloha
const VeryLargeNumber operator+(const VeryLargeNumber &inputNumber1, const VeryLargeNumber &inputNumber2);
const VeryLargeNumber operator-(const VeryLargeNumber &inputNumber1, const VeryLargeNumber &inputNumber2);
const VeryLargeNumber calculate(const VeryLargeNumber (*calculateFuncion)(const VeryLargeNumber, const VeryLargeNumber),
                                const VeryLargeNumber &inputNumber1, const VeryLargeNumber &inputNumber2);

#endif

const string DUMMY_STRING = "";
const int DUMMY_INT = 0;
const bool DUMMY_BOOL = false;

//1.uloha
bool VeryLargeNumber::allZeros(const string &input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] != '0' && input[i]!='-' && input[i]!=' ')
		{
			return false;
		}
	}
	return true;
}
VeryLargeNumber::VeryLargeNumber(const string &input) {
	//number ="0";
	bool flag = false;
	int k = 0;
	int j = 0;
	while (input[j] == ' ')
	{
		j++;
		k++;
	}
	if (input[j] == '-')
	{
		number = "-";
		k += 1;
	}
	if (allZeros(input))
	{
		number = "0";
	}
	else {
		for (int i = k; i < input.length(); i++)
		{
			if ((input[i]>'0' && input[i]<='9') && !flag)
			{
				flag = true;
			}
			if ((input[i]<'0' || input[i]>'9')&& input[i]!=' '  )
			{
				number = "0";
				break;
			}
			else if(input[i]!=' ' && flag )
			{
				number += input[i];

			}
		}
	}
}

void VeryLargeNumber::put(const string &input) {
	bool flag = false;
	int k = 0;
	number = "0";
	int j = 0;
	while (input[j] == ' ')
	{
		j++;
		k++;
	}
	if (input[j] == '-')
	{
		number = "-";
		k += 1;
	}
	if (allZeros(input))
	{
		number = "0";
	}
	else {
		for (int i = k; i < input.length(); i++)
		{
			if ((input[i]>'0' && input[i] <= '9') && !flag)
			{
				flag = true;
				if (!k)
				{
					number = "";
				}
			}
			if ((input[i]<'0' || input[i]>'9') && input[i] != ' ')
			{
				number = "0";
				break;
			}
			else if (input[i] != ' ' && flag)
			{
				number += input[i];

			}
		}

	}
	cout << number<<'\n';
}

int VeryLargeNumber::numberOfDigits() const {
	return number.length();
}

string VeryLargeNumber::value() const {
  return number;
}

bool VeryLargeNumber::negativeNumber() const {
  return number[0]=='-';
}
//2.uloha
VeryLargeNumber::VeryLargeNumber(long long inputNumber) {
    string str;
	int n = 0;
	char ch;
	bool flag = false;
	if (inputNumber < 0)
	{
		flag = true;
		inputNumber *= (-1);
	}
	while (inputNumber>0)
	{
		n = inputNumber % 10;
		inputNumber /= 10;
		ch = n + '0';
		//cout << ch;
		str.push_back(ch);
	}
	if (flag)
	{
		str.push_back('-');
	}
	
	reverse(str.begin(), str.end());
	//cout << str << '\n';
	put(str);
}

VeryLargeNumber::VeryLargeNumber(const VeryLargeNumber &inputNumber) {
	number = inputNumber.number;
}

VeryLargeNumber::VeryLargeNumber(VeryLargeNumber &&inputNumber) {
	if (this != &inputNumber)
	{
		number = inputNumber.number;
		inputNumber.number = "0";
	}

}

VeryLargeNumber & VeryLargeNumber::operator=(const VeryLargeNumber &inputNumber) {
	number = inputNumber.number;
  return *this;
}

VeryLargeNumber & VeryLargeNumber::operator=(VeryLargeNumber &&inputNumber) {
	if (this != &inputNumber)
	{
		number = inputNumber.number;
		inputNumber.number = "0";
	}

  return *this;
}

VeryLargeNumber & VeryLargeNumber::operator=(const string &vstup) {
	put(vstup);
  return *this;
}

//3.uloha
bool VeryLargeNumber::operator==(const VeryLargeNumber &inputNumber) const {
	return number == inputNumber.number;
}

bool VeryLargeNumber::operator==(const string &inputNumber) const {
	return number == inputNumber;
}

bool VeryLargeNumber::operator<(const VeryLargeNumber &inputNumber) const {
  return number<inputNumber.number;
}

bool VeryLargeNumber::operator<(const string &inputNumber) const {
  return number>inputNumber;
}

//4.uloha
const VeryLargeNumber operator+(const VeryLargeNumber &inputNumber1, const VeryLargeNumber &inputNumber2) {
  VeryLargeNumber d(0);

  return d;
}

const VeryLargeNumber operator-(const VeryLargeNumber &inputNumber1, const VeryLargeNumber &inputNumber2) {
  VeryLargeNumber d(0);
  return d;
}

const VeryLargeNumber calculate(const VeryLargeNumber (*calculateFuncion)(const VeryLargeNumber, const VeryLargeNumber),
                                const VeryLargeNumber &inputNumber1, const VeryLargeNumber &inputNumber2) {
  VeryLargeNumber d(0);
  return d;
}

//5.uloha
string VeryLargeNumber::minimum(const VeryLargeNumber *arrayOfNumbers, int sizeOfArray) const {
  VeryLargeNumber d(0);
  return DUMMY_STRING;
}

string VeryLargeNumber::maximum(const VeryLargeNumber *arrayOfNumbers, int sizeOfArray) const {
  VeryLargeNumber d(0);
  return DUMMY_STRING;
}

//6.uloha
void VeryLargeNumber::changeNumberSign() {
}

const VeryLargeNumber VeryLargeNumber::operator*(const VeryLargeNumber &inputNumber) {
  VeryLargeNumber d(0);
  return d;
}



