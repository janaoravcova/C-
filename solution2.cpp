#include <iostream>

using namespace std;

const int DUMMY_INT = -999;
const bool DUMMY_BOOL = false;
const string DUMMY_STRING = "";

const int MINIMAL_LENGTH = 8;

enum CharacterType {CHAR_DIGIT, CHAR_ALPHA, CHAR_NOT_ALLOWED, CHAR_OTHER};

//1. uloha
CharacterType typeOfCharacter(char character){
	switch (character)
	{
	case 1:
		return CHAR_DIGIT;
	case 2:
		return CHAR_ALPHA;
	case 3:
		return CHAR_NOT_ALLOWED;
	case 4:
		return CHAR_OTHER;
	}
	
}

bool isDigit(char character) {
	if (48 <= character && character <= 57)
	{
		return true;
  }
	else
	{
		return false;
	}
}

bool isAlpha(char character) {
	if (65 <= character && character <= 90 || 97 <= character && character <= 122) {
		return true;
	}
	else {
		return false;
	}
}

bool notAllowedChar(char character) {
	if (0 <= character &&  character <= 32 || character==92 || character == 34 || character == 39) {
		return true;
	}
	else {
		return false;
	}
}
bool otherChar(char character) {
	if (33 <= character && character < 34 || 34 < character && character <= 47 || 40 <= character && character <= 47 || 58 <= character && character <= 64 || 91 <= character && character <92|| 92< character && character <= 47 || 123 <= character && character <= 126 ) {
		return true;
  }
	else {
		return false;
	}
}

//2. uloha
int numberOfAllCharacters(const string &letters) {
	int pocet = 0;
	
	for (int i = 0; i < letters.length(); i++)
	{
		
			pocet++;
		
	}
	return pocet;
}

int numberOfAllDigits(const string &letters) {
	int pocet = 0;

	for (int i = 0; i < letters.length(); i++)
	{
		if (isDigit(letters[i]))
		{
			pocet++;
		}
	}
	return pocet;
}

int numberOfAllAlphas(const string &letters) {
	int pocet = 0;

	for (int i = 0; i < letters.length(); i++)
	{
		if (isAlpha(letters[i]))
		{
			pocet++;
		}
	}
	return pocet;
}

bool notAllowedCharacters(const string &letters) {
	int pocet = 0;

	for (int i = 0; i < letters.length(); i++)
	{
		if (notAllowedChar(letters[i]))
		{
			return true;
		}
	}
	return false; 
}

int numberOfOtherCharacters(const string &letters){
	int pocet = 0;

	for (int i = 0; i < letters.length(); i++)
	{
		if (otherChar(letters[i]))
		{
			pocet++;
		}
	}
	return pocet;
}

//3. uloha
string passwordStrength(const string &password) {
	if (password == "")
	{
		return "Empty password";
  }
	if (notAllowedCharacters(password))
	{
		return "Password with not allowed character";
	}
	if (numberOfAllCharacters(password) < 8)
	{
		if (numberOfAllAlphas(password) == password.length() || numberOfAllDigits(password) == password.length())
		{
			return "Very weak password";
		}
		else
		{
			return "Weak password";
		}
	}
	else
	{
		if (numberOfAllAlphas(password) == password.length() || numberOfAllDigits(password) == password.length())
		{
			return "Weak password";
		}
		if (numberOfAllAlphas(password) > 0 && numberOfAllDigits(password) > 0 && notAllowedCharacters(password) == 0 && numberOfOtherCharacters(password) == 0)
		{
			return  "Strong password";
		}
		if (numberOfAllAlphas(password) > 0 && numberOfAllDigits(password) > 0 && notAllowedCharacters(password) == 0 && numberOfOtherCharacters(password) > 0)
		{
			return "Very strong password";
		}
		else
		{
			return "Strong password";
		}
	}
}

//4. uloha
int find_char(char input[], char character)
{
	int i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == character)
		{
			return i;
		}
		i++;
	}
	return -1;
	
}
bool occurrenceOfACharacter(const string &input, char character) {
	int n = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == character) {
			n += 1;
		}
	}
	return n;
}

int sumOccurrencesOfACharacter(const string &input, char character) {
	int pocet = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i]==character)
		{
			pocet++;
		}
	}
	return pocet;
}

int maximumOccurrencesOfOneCharacter(const string &input) {
	int count[255] = { 0 };

	// Construct character count array from the input 
	// string. 
	for (int i = 0; i< input.size(); i++)
		count[input[i]]++;

	int max = 0;  // Initialize max count 
	char result;   // Initialize result 

				   // Traversing through the string and maintaining 
				   // the count of each character 
	for (int i = 0; i < input.size(); i++) {
		if (max < count[input[i]]) {
			max = count[input[i]];
			result = input[i];
		}
	}

	return max;
}

string adaptedPasswordStrength(const string &password) {
	if (maximumOccurrencesOfOneCharacter(password) > password.length() / 2)
	{
		if (passwordStrength(password)=="Weak password")
		{
			return "Very weak password";
		}
		else if (passwordStrength(password) == "Strong password")
		{
			return "Weak password";
		}
		else if (passwordStrength(password) == "Very strong password")
		{
			return "Strong password";
		}
		else
		{
			return passwordStrength(password);
		}
  }
}

//5. uloha

string encodingPassword(const string &password) {
	string password1 = password;

	if (password1 != "")
	{
		for (int i = 0; i < password1.length(); i++)
		{
			password1[i] = password1[i] - 1;
		}
	}
	return password1;
}

string decodingPassword(const string &encodedPassword) {
	string password1 = encodedPassword;

	if (password1 != "")
	{
		for (int i = 0; i < password1.length(); i++)
		{
			password1[i] = password1[i] + 1;
		}
	}
	return password1;

}