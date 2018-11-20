#include <iostream>
#include <math.h>
#include <locale>

using namespace std;

//#include "riesenie5.h"

#ifndef _RIESENIE_H_
#define _RIESENIE_H_

//1. uloha
class Item {
protected :string item;
 protected:
	 int toInt(const string &item0) const;

  bool characterInInterval(char inputChar, char beginning, char end) const;
  string subString(const string &item0, char del, int whichElement) const;
  int countOccurrencesOfChar(const string &item0, char c0) const;
 public:
  virtual bool put(const string &item0);
  virtual string get() const { return item; };
};

class Name : public Item {
 public:
  bool put(const string &name);
};

//2. uloha
enum DateFormat {EU_FORMAT, US_FORMAT, NONE};

class Date : public Item {
  int d = 0, m = 0, y = 0;
  bool checkDayMonth(int day, int month, int year) const;
  bool inputDate(const string &date);
 public:
  bool put(const string &date) ; //EU_FORMAT: day-month-year (15-3-2018), US_FORMAT: month/day/year (3/15/2018)
  string getInFormat(const DateFormat dateFormat) const;
  int day() const { return d;};
  int month() const { return m;};
  int year() const { return y;};
  bool splitAndCheck(const string &date, const char sign);
  DateFormat returnFormat(const string date);
};

//3. uloha
class Record : public Item{
  Name firstN, secondN;
  Date date;

 public:
  bool put(const string &record);
  bool equal(const Record &record) const;
  string firstName() const { return firstN.get(); };
  string secondName() const { return secondN.get(); };
  string day() const { return subString(date.get(),'-',1); };
  string month() const { return subString(date.get(),'-',2); };
  string year() const { return subString(date.get(),'-',3); };
};

//4. uloha
class ListOfRecords : public Item {
  Record *array = nullptr;
  int numberOfRecs = 0;
  int maximum = 0;
 public:
  bool put(const string &list);
  int numberOfRecords() { return numberOfRecs; };
  string get(int recordNumber);
//5. uloha
  Record record(int recordNumber);
  ListOfRecords getList(const string &criteria);
};

#endif



const int WRONG_INT = -99;
const bool DUMMY_BOOL = false;
const int DUMMY_INT = -1;
const string DUMMY_STRING;

//1. uloha
int Item::toInt(const string &item0) const {
  int number = 0;
  for (auto c : item0) {
	  if ('0' > c || c > '9')
	  {
		  return -99;
	  }
    number *= 10;
    number += c - '0';
  }
  return number;
}

bool Item::characterInInterval(char inputChar, char beginning, char end) const {
  if (inputChar < beginning || inputChar > end) {
    return false;
  }
  return true;
}

string Item::subString(const string &item0, char del, int whichElement) const {
  int number = 1;
  string element;
  for (auto c : item0) {
    if (number > whichElement) {
      break;
    }
    if (c == del) {
      number++;
      continue;
    }
    if (number == whichElement) {
      element += c;
    }
  }
  return element;
}

bool Item::put(const string &item0) {
	if (item0.length() == 0)
	{
		return false;
	}
	else
	{
		item = item0;
		return true;
	}
}

bool isSmallAlpha(const char c)
{
	if ('a' <= c && c <= 'z')
	{
		return true;
	}
	return false;
}

bool isLargeAlpha(const char c)
{
	if ('A' <= c && c <= 'Z')
	{
		return true;
	}
	return false;
}

bool Name::put(const string &name) {
	int i = 0;
	if (name.length() == 0)
	{
		return false;
  }
	else
	{
		if (!isLargeAlpha(name[0]))
		{

			return false;

		}
		const char c = name[name.length() - 1];
		while (name[i] != '\0')
		{
			
		    if (i != 0 && ((!isSmallAlpha(name[i])) && (!isLargeAlpha(name[i])) && name[i] != '-' && name[i] !=' '))
			{

				return false;
			}
			if (!isSmallAlpha(c) && !isLargeAlpha(c))
			{

				return false;
			}
			i++;
		}
		item = name;
		return true;
		
	}
}

//2. uloha

int Item::countOccurrencesOfChar(const string &item0, char c0) const {
  return DUMMY_INT;
}

bool Date::checkDayMonth(int day, int month, int year) const {
  if (day < 1 || month < 1 || year < 0) {
    return false;
  }
  if (month > 12) {
    return false;
  }
  int daysInMonth[]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  if (year % 4 == 0) {
    if (month == 2 && day == 29) {
      return true;
    }
  }
  if (day > daysInMonth[month - 1]) {

    return false;
  }
  return true;
}

DateFormat Date::returnFormat(const string date)
{
	int len = date.length();
	if (len < 5) //date format of invalid length
	{
		return NONE;
	}
	int pom = 0;
	int lom = 0;
	int i = 0;
	while (date[i] != '\0')
	{
		if (date[i] == '-')
		{
			pom++;
			
		}
		if (date[i] == '/')
		{
			lom++;
		
		}
		i++;
	}
	if (pom == 0 && lom == 2)
	{
		return US_FORMAT;
	}
	else if (pom == 2 && lom == 0)
	{
		return EU_FORMAT;
	}
	else
	{
		return NONE;
	}



}

bool Date::splitAndCheck(const string &date, const char sign)
{
	string d = "";
	string m = "";
	string y = "";
	int pom = 0;
	int i = 0;
	while (date[i] != '\0')
	{
		if (date[i] == sign)
		{
			pom++;
			
		}
		if (pom == 0 && date[i] != sign)
		{
			d += date[i];
		}
		if (pom == 1 && date[i] != sign)
		{
			m += date[i];
		}
		if (pom == 2 && date[i] !=sign)
		{
			y += date[i];
		}
		i++;
	}
	if (sign == '-')
	{

		return checkDayMonth(toInt(d), toInt(m), toInt(y));
	}
	else
	{
		return checkDayMonth(toInt(m), toInt(d), toInt(y));
	}
}

bool Date::inputDate(const string &date) {
	if (returnFormat(date) == EU_FORMAT)
	{
		return 	splitAndCheck(date,'-');
	}
	else if (returnFormat(date) == US_FORMAT)
	{
		return 	splitAndCheck(date, '/');
	}
	else
	{
		return false;
	}
}

string decimalNumberIntoDecimalString(int decimalNumber) {
	int remainder = 0;
	string str;
	int znamienko = 0;
	char znak;
	if (decimalNumber == 0 || decimalNumber == -0)
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

bool Date::put(const string &date) {
	if (!inputDate(date))
	{

		return false;
	}
	else
	{
		string day = "";
		string month = "";
		string year = "";
		int pom = 0;
		int i = 0;
		while (date[i] != '\0')
		{
			if (date[i] == '-' || date[i]=='/')
			{
				pom++;
			
			}
			if (pom == 0 && date[i]!='/' && date[i]!='-')
			{
				day += date[i];
			}
			if (pom == 1 && date[i] != '/' && date[i] != '-')
			{
				month += date[i];
			}
			if (pom == 2 && date[i] != '/' && date[i] != '-')
			{
				year += date[i];
			}
			i++;
		}
		DateFormat f = returnFormat(date);
		if (f == US_FORMAT)
		{
			string temp = day;
			day = month;
			month = temp;
		}
		item = day + '-' + month + '-' + year;
		d = toInt(day);
		m = toInt(month);
		y = toInt(year);
		return true;
	}

}

string Date::getInFormat(const DateFormat dateFormat) const {
	if (d == 0 && m == 0 && y == 0)
	{
		
		return "";
	}
	else
	{
		if (dateFormat == EU_FORMAT)
		{
			return decimalNumberIntoDecimalString(d) + '-' + decimalNumberIntoDecimalString(m) + '-' + decimalNumberIntoDecimalString(y);
		}
		else if (dateFormat == US_FORMAT)
		{
			return decimalNumberIntoDecimalString(m) + '/' + decimalNumberIntoDecimalString(d) + '/' + decimalNumberIntoDecimalString(y);
		}
	}

}

//3.uloha
bool Record::put(const string &record) {
	string firstname = "";
	string lastname = "";
	string dat = "";
	int c = 0;

	int i = 0;
	while (record[i] != '\0')
	{
		if (record[i] == ',')
		{
			c++;
		}
		else if (record[i] != 'c' && c == 0)
		{
			firstname += record[i];
		}
		else if (record[i] != 'c' && c == 1)
		{
			lastname += record[i];
		}
		else if (record[i] != 'c' && c == 2)
		{
			dat += record[i];
		}
		i++;
	}
	if (!firstN.put(firstname) ||!date.put(dat)|| !secondN.put(lastname))
	{
		cout << firstname << ' ' << lastname << ' ' << dat << '\n';
		return false;
	}
	else
	{
		firstN.put(firstname);
		date.put(dat);
		secondN.put(lastname);
		item = firstname + ',' + lastname + ',' + date.getInFormat(EU_FORMAT);
		return true;
	}

}

bool Record::equal(const Record &record) const {
	
	if ((record.firstN.get() == firstN.get()) && (record.secondN.get() == secondN.get()) && (record.date.get()==date.get()))
	{
		return true;
	}
	else
	{
		return false;
	}
  
}

//4. uloha
bool ListOfRecords::put(const string &list) {
  return DUMMY_BOOL;
}

string ListOfRecords::get(int recordNumber) {
  return DUMMY_STRING;
}

//5. uloha
Record ListOfRecords::record(int recordNumber) {
  Record empty;
  return empty;
}

ListOfRecords ListOfRecords::getList(const string &criteria) {
  ListOfRecords records;
  return records;
}