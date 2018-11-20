#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;
#define  _CTR_SECURE_NO_WARNINGS
//#include "riesenie4.h"

#ifndef _RIESENIE_H_
#define _RIESENIE_H_

#endif

const int DUMMY_INT = -999;
const bool DUMMY_BOOL = false;
char *DUMMY_CHARS = "";
const unsigned int MAX = 256;

//1. uloha
bool sign(const char c)
{
	if ((c == ' ' || c == '.' || c == ',' || c == ';' || c == '?' || c == '!' || c == '-' || c == ':'))
	{
		return true;
	}
	else
	{
		return false;
	}
}
int numberOfWords(const char *text) {
	int i = 1;
	int pocet = 0;
	if (text == NULL)
	{
		return 0;
	}
	if (text == "")
	{
		return 0;
	}
	else
	{
		while (text[i] != '\0')
		{

			if (sign(text[i]) && !sign(text[i-1]))
			{
				pocet++;

			}
			i++;
		}
		if (!sign(text[i - 1]))
		{
			pocet++;
		}
	}
	return pocet;
}

const char *pointerToNthWord(const char *text, int order) {

	if (text == NULL)
	{
		return "";
	}
	if (order < 0 || order> numberOfWords(text)-1)
	{
		return "";
	}

	else
	{

		int wordnum = -1;
		const char *prev = NULL;

		while (*text != '\0')
		{
			if (!sign(*text))
			{
				if (prev == NULL || sign(*prev))
				{
					wordnum++;
				}
				if (wordnum == order)
				{
					return text;
				}
				text++;
				prev = text - 1;
			}
			else if(sign(*text))
			{
				text++;
				prev = text - 1;
			}
		}
	}

}

//2. uloha
char *getNthWord(const char *text, char *word, int order) {
	const char *p = NULL;
	if (text == NULL)
	{
		return "";
	}
	if (word == NULL) 
	{
		return "";
	}
	if (text == "")
	{
		return "";
	}
	else
	{
		int len = 0;
		p = pointerToNthWord(text, order);
		
		while (!sign(*p))
		{
			*word = *p;
			word++;
			len++;
			p++;
			//cout << *word;
		}
		*word = '\0';
		while (len) //smernik vraciame na zaciatok slova
		{
			word--;
			len--;
		}
	}
	return word;
}

//3. uloha
char *listOfSelectedWords(const char *text, char *output, const int *listOfOrders, int numberOfOrders) {
	int len = 0;
	if (text == NULL)
	{
		return "";
	}
	if (output == NULL)
	{
		return "";
	}
	if (text == "")
	{
		return "";
	}
	for (int i = 0; i < numberOfOrders; i++)
	{
		char *vysledok = new char[256];
		char *p = getNthWord(text,vysledok, listOfOrders[i]);
		//cout << "p=" << *p<<'\n';
		while (*p != '\0')
		{
			*output = *p;
			output++;
			p++;
			len++;
		}
		if (i != numberOfOrders - 1)
		{
			*output = ',';
			len++;
			output++;
		}
		
	
	}
	*output = '\0';
	
	while (len)
	{
		output--;
		len--;
	}
	return output;


}
//4.uloha
int compareTwoWords(const void *a, const void *b)
{	
	const char *first = *(const char **)a;
	const char *second = *(const char **)b; 
	return strcmp(first, second);
} 


void sortAccordingToAsciiValues(char **listOfWords, int count) {
	//int max = 6;
	cout << "Usporiadaj pole slov: ";
	qsort(listOfWords, count, sizeof(char *), compareTwoWords);
	for (auto i = 0; i < count; i++)
	{
		cout << listOfWords[i] << ", ";
	}
}

void sortWithSmallLetters(char **listOfWords,const int count) {
	cout << "Usporiadaj pole slov: ";
	char **newList[256];
	string st = "";
	for (int j = 0; j < count; j++)
	{
		while(*listOfWords[j]!='\0')
		{
			
			cout << (char)tolower(*listOfWords[j])<< '\n';
			*newList[j] = (char)tolower(*listOfWords[j]);
			listOfWords[j]++;
			newList[j]++;
		}
	
		
	}
	qsort(listOfWords, count, sizeof(char *), compareTwoWords);
	for (auto i = 0; i < count; i++)
	{
		cout << listOfWords[i] << ", ";
	}
}

//5.uloha
void sortWithSmallAndCh(char **listOfWords, int count) {
}

char *sortAccordingToFuncion(const char *text, char *output, void sortingFunction(char **arrayOfText, int count)) {
  return DUMMY_CHARS;
}



