#include <iostream>
#include <string.h>

#define DUMMY_STRING ""
#define DUMMY_INT -1
#define DUMMY_BOOL false

//Uloha 1.
std::string getText(const std::string inputText) {
	if (inputText == "")
	{
		return "Empty input";
	}
  return inputText;
}

//Uloha 2. a 5.
int numberOfOccurrences(const std::string text, const std::string subtext) {
	int len1 = text.size();
	int len2 = subtext.size();
	int i = 0;
	int pocet = 0;
	int vysl = 0;
	int temp;
	while (i<len1)
	{	
		temp = i;
		for (int j = 0; j < len2; j++)
		{
			if (text[i] == subtext[j])
			{
				pocet++;
				i++;
				if (i == len1)
				{
					break;
				}
			}

		}
		if (pocet == len2)
		{
			vysl++;
			pocet = 0;
			
		}
		i = temp + 1;

		pocet = 0;

	}
	return vysl;
}

//Uloha 3. a 4.
bool realNumber(const std::string number) {
	int pocet = 0;
	if (number == "")
	{
		return false;
	}
	for (int i = 0; i < number.size(); i++)
	{
		if (number[i] == '-' && i != 0)
		{
			return false;
		}
		if (number[i] == '.')
		{
			pocet++;
			if (pocet > 1)
			{
				return false;
			}

		}
	}
	return true;
}


