#include <iostream>
#include <string>
#include <cstring>  /* strcpy */

using namespace std;

//#include "riesenie6.h"

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_
//1.uloha
string subString(const string &item0, char del, int whichElement);

enum RoomType { ROOM, APARTMENT };
const string ROOM_STR = "Room";
const string APARTMENT_STR = "Apartment";

class Cleaning {
  int cleaningRoom = 30;
  int cleaningApartment = 50;
  int cleaningSecondGuest = 10;
public:
  int getCleaningTime(RoomType roomType, int numberOfGuests) const {
    switch (roomType) {
      case ROOM:
        return (numberOfGuests == 1) ? cleaningRoom : cleaningRoom + cleaningSecondGuest;
      case APARTMENT:
        return (numberOfGuests == 1) ? cleaningApartment : cleaningApartment + cleaningSecondGuest;
    }
    return -1;
  };
};

class HotelRoom {
  string firstGuest = "";
  string secondGuest = "";
  RoomType roomType = ROOM;
  bool roomIsCleaned = true;
  int cleaningTime = 0;
public:
	
	void setRoomType(RoomType roomType0) { roomType = roomType0; }
  const string getRoomType() const {
    return (roomType == APARTMENT) ? APARTMENT_STR : ROOM_STR;
  };
  bool isCleaned() const { return roomIsCleaned; };
  bool checkIn(const string &guestNames);
  const string guestNames() const ;
  bool occupiedRoom() const ;
  int numberOfGuests() const ;
  bool isOne(const string &guestNames);
  int splitNames(const string &guestNames);
//2.uloha
  bool checkOut();
  int cleaningUp();
  bool moveFromRoom(HotelRoom &&from);
};

//3.uloha
class Hotel {
  int floors = 0;
  int roomsPerFloor = 0;
  HotelRoom **rooms = nullptr;
public:
  Hotel(int floors0, int roomsPerFloor0, int apartmentsPerFloor);
  ~Hotel();
  int numberOfAllRooms(const string &roomType) const ;
  bool isEmpty();
//4.uloha
  int checkIn(const string &guestNames, const string &typeOfRoom);
  int numberOfGuests() const ;
  string guestNames(int roomNumber) const;
  int free(const string room)const;
  int freeApartments() const;
  int freeRooms() const;
  //5.uloha
  int split(const string str,const char ch);
  int importOrders(const char **database, int numberOfOrders);
  bool checkOut(int roomNumber);
  int cleaningAllRooms();
  int moveGuestsToOtherRoom(int roomNumber);
};

#endif


const bool DUMMY_BOOL = false;
const int DUMMY_INT = 0;
const string DUMMY_STRING = "";

string subString(const string &item0, char del, int whichElement) {
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

//1.uloha
bool HotelRoom::isOne(const string &guestNames)
{
	for (int i = 0; i < guestNames.length(); i++)
	{
		if (guestNames[i] == ';')
		{
			return false;
		}
	}
	return true;
}
int HotelRoom::splitNames(const string &guestNames)
{
	for (int i = 0; i < guestNames.length(); i++)
	{
		if (guestNames[i] == ';')
		{
			return i;
		}
	}
}
bool HotelRoom::checkIn(const string &guestNames) {
	int n = 0;
	if (firstGuest != "" || secondGuest!="" || !isCleaned())
	{
		return false;
  }
	else if (guestNames == "")
	{
		return false;

	}
	else
	{
		if (isOne(guestNames))
		{
			for (int i = 0; i < guestNames.length(); i++)
			{
				firstGuest += guestNames[i];
			}
		}
		else
		{
			n = splitNames(guestNames);
			for (int j = 0; j < guestNames.length() ; j++)
			{
				if (j < n  )
				{

					firstGuest += guestNames[j];
				}
				if (j > n  )
				{

					secondGuest += guestNames[j];
				}
			}
		}
		roomIsCleaned = false;
		return true;
	}
	
}

const string HotelRoom::guestNames() const {
	if (firstGuest != "" && secondGuest != "")
	{
		return firstGuest + ';' + secondGuest;
  }
	else if (firstGuest != "")
	{
		return firstGuest;
	}
	else
	{
		return secondGuest;
	}
}

bool HotelRoom::occupiedRoom() const {
	if (firstGuest != "" || secondGuest != "")
	{
		return true;
  }
	else
	{
		return false;
	}
}

int HotelRoom::numberOfGuests() const {

	if (firstGuest != "" && secondGuest != "")
	{
		return 2;
  }
	else if (firstGuest != "" || secondGuest != "")
	{
		return 1;
	}
	else
	{
		return 0;
	}
};

//2.uloha

bool HotelRoom::checkOut() {
	if (!occupiedRoom())
	{
		return false;
  }
	else
	{
	
		Cleaning cl;
		cleaningTime = cl.getCleaningTime(roomType, numberOfGuests());
		firstGuest = "";
		secondGuest = "";
		return true;
	}
}

int HotelRoom::cleaningUp() {
	if (roomIsCleaned || occupiedRoom())
	{
		return 0;
  }
	else
	{
		roomIsCleaned = true;
		return cleaningTime;
	}
}

bool HotelRoom::moveFromRoom(HotelRoom &&from) {
	if (roomType != from.roomType)
	{
		return false;
	}
	if (occupiedRoom() || !roomIsCleaned)
	{
		return false;
	}
	else
	{
		if (this != &from)
		{

			firstGuest = from.firstGuest;
			secondGuest = from.secondGuest;
			roomType = from.roomType;
			roomIsCleaned = from.roomIsCleaned;
			cleaningTime = from.cleaningTime;
			from.firstGuest = "";
			from.secondGuest = "";
			from.roomIsCleaned = false;
			from.cleaningTime = 0;

		}
			
	}
}

//3.uloha
Hotel::Hotel(int floors0, int roomsPerFloor0, int apartmentsPerFloor) {
	if (floors0 < 1 || roomsPerFloor0 < 1)
	{
		floors0 = 0;
		roomsPerFloor0 = 0;
		return;
	}
	else
	{
		floors = floors0;
		roomsPerFloor = roomsPerFloor0;
	}

	rooms = new HotelRoom *[floors0];
	for (size_t i = 0; i < floors0; i++)
	{
		rooms[i] = new HotelRoom [roomsPerFloor0];
	}
	for (size_t i = 0; i < floors0; i++)
	{
		for (size_t j = 0; j < roomsPerFloor0; j++)
		{
			if (j < apartmentsPerFloor)
			{
				rooms[i][j].setRoomType(APARTMENT);
			}
			else
			{
				rooms[i][j].setRoomType(ROOM);
			}
		}
	}




}
bool Hotel::isEmpty()
{
	for (size_t i = 0; i < floors; i++)
	{
		if (sizeof(rooms[i]) == 0)
		{
			return true;
		}
	}
	return false;
}
Hotel::~Hotel() {
	if (!isEmpty())
	{
		for (size_t i = 0; i < floors; i++)
		{
			
			delete[] rooms[i];
		}
		delete[] rooms;
	}
}

int Hotel::free(const string room)const
{
	string str="";
	if (room == "Room")
	{
		str = ROOM_STR;
	}
	else
	{
		str = APARTMENT_STR;
	}
	int count = 0;
	for (size_t i = 0; i < floors; i++)
	{
		for (size_t j = 0; j < roomsPerFloor; j++)
		{
			if (rooms[i][j].getRoomType() == str && !rooms[i][j].occupiedRoom())
			{
				count++;
			}
		}
	}
	return count;
}
int Hotel::numberOfAllRooms(const string &roomType) const {
	string str = "";
	if (roomType == "Room")
	{
		str = ROOM_STR;
	}
	else
	{
		str = APARTMENT_STR;
	}
	int count = 0;
	for (size_t i = 0; i < floors; i++)
	{
		for (size_t j = 0; j < roomsPerFloor; j++)
		{
			if (rooms[i][j].getRoomType() == str)
			{
				count++;
			}
		}
	}
	return count;
}
int Hotel::freeApartments() const
{
	return free("Apartment");
 }
int Hotel::freeRooms() const {
	return free("Room");
}


//4.uloha
int Hotel::checkIn(const string &guestNames, const string &typeOfRoom) {
	string type;

	if (guestNames == "")
	{
		return 0;
	}
	if (typeOfRoom == "Apartment")
	{
		
		type = APARTMENT_STR;
	}
	else if (typeOfRoom == "Room")
	{
		type = ROOM_STR;
	}
	for (size_t i = 0; i < floors; i++)
	{
		for (size_t j = 0; j < roomsPerFloor; j++)
		{
			if (!rooms[i][j].occupiedRoom() && rooms[i][j].isCleaned() && rooms[i][j].getRoomType()==typeOfRoom)
			{
				rooms[i][j].checkIn(guestNames);
				//cout >> rooms[i][j].guestNames();
				//cout << guestNames<<'\n';
				return (i + 1) * 100 + j + 1;
			}
		}
  }
	return 0;
}
int Hotel::moveGuestsToOtherRoom(int roomNumber) {
  return DUMMY_INT;
}

int Hotel::numberOfGuests() const {
	int count = 0;
	for (size_t i = 0; i < floors; i++)
	{
		for (size_t j = 0; j < roomsPerFloor; j++)
		{
			count += rooms[i][j].numberOfGuests();
		}

  }
	return count;
}

//5.uloha
int Hotel::split(const string str,const char ch)
{
	//cout << str << '\n';
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == ch)
		{
			return i;
			
		}
	}
	return -1;
}
int Hotel::importOrders(const char **database, int numberOfOrders) {
	string guestn = "";
	string rm = "";
	int k = 0;
	int count = 0;
	int m = 0;
	int l = 0;
	int p = 0;
	int o = 0;
	for (int i = 0; i < numberOfOrders; i++)
	{
		int n = split(database[i],':');
		if (n < 0)
		{
			k=checkIn(database[i], "Room");
			if (k > 0)
			{
				count = count + ((split(database[i], ';') > 0) ? 2 : 1);
			}
		}
		else
		{
			
			int j = 0;
			while (*database[i] != '\0')
			{
				if (j < n)
				{
					guestn += *database[i];

				}
				else if (j>n)
				{
			
					rm += *database[i];
				}
				database[i]++;
				j++;
				
			}
			while (j)
			{
				database[i]--;
				j--;
			}
			k=checkIn(guestn, rm);
			rm = "";
			guestn = "";
			if (k > 0)
			{
				count = count +  ((split(database[i], ';') > 0) ? 2: 1);
			}

		}
	
	}
	return count;
}

bool Hotel::checkOut(int roomNumber) {
	int r = roomNumber % 100;
	int f = roomNumber / 100;
	cout << r << '\n';
	cout << f << '\n';
	if (f - 1 > floors || r - 1 > roomsPerFloor)
	{
		return false;
	}
	if (!rooms[f - 1][r - 1].occupiedRoom())
	{
		return false;
	}
	else
	{
		return rooms[f - 1][r - 1].checkOut();
	}
}
string Hotel::guestNames(int roomNumber) const {
  return "";
}

int Hotel::cleaningAllRooms() {
	Cleaning cl;
	RoomType type;
	int total = 0;
	for (size_t i = 0; i < floors; i++)
	{
		for (size_t j = 0; j < roomsPerFloor; j++)
		{
			if (!rooms[i][j].occupiedRoom() && !rooms[i][j].isCleaned())
			{
				if (rooms[i][j].getRoomType() == APARTMENT_STR)
				{
					type = APARTMENT;
				}
				else
				{
					type = ROOM;
				}
				total += cl.getCleaningTime(type, rooms[i][j].numberOfGuests());


			}
		}
	}
	return total;
}

