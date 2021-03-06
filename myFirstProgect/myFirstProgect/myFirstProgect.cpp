// myFirstProgect.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

class Parket
{
private:
	string material;


public:
	string paramParket() {
		cout << "\nВведите материал паркета: ";
		cin >> material;

		return material;
	}
};

class Ceiling
{
private:
	string type;
public:
	string paramCeiling() {
		cout << "\nВведите тип потолка: ";
		cin >> type;

		return type;
	}
};

class Windows
{
private:
	float lenght;
	float height;
	float width;
public: 
	void paramWindow() {
		cout << "\nДля расчета параметров окон введите их общую длину, ширину и высоту:\n ";
		cin >> lenght;
		cin >> width;
		cin >> height;
	}

	float volumeWin() 
	{
		float volume = lenght + height + width;
		return volume;
	}
};

class Room
{
private:

	string color;
	float paintLitersForSqM;
	float paintLitersAll;
	float lenght;
	float height;
	float width;
	Windows *win;
	Ceiling *ceiling;
	Parket *parket;

public:
	void paramOfRoom() {
		ceiling = new Ceiling();
		parket = new Parket();
		win = new Windows();
		win->paramWindow();
		cout << "\nДля расчета количества краски введите длину, ширину и высоту комнаты:\n ";
		cin >> lenght;
		cin >> width;
		cin >> height;
		cout << "\nВведите цвет комнаты:\n ";
		cin >> color;
		cout << "\nВведите нужное количество краски на квадратный метр:\n ";
		cin >> paintLitersForSqM;

	}

	~Room()
	{
		delete win;
		delete parket;
		delete ceiling;
	}

	int countRLiters() {
		paintLitersAll = paintLitersForSqM * (lenght*height * 2 + width*height * 2) - win->volumeWin();
		return paintLitersAll;
	}

	void infForRoom() {
		cout << "Был произведен рассчет для одной комнаты:"
			<< "\n-длина: " << lenght 
			<< "\n-высота: " << height 
			<< "\n-ширина: " << width
			<< "\n-цвет краски: " << color 
			<< "\n-количество литров краски на квадратный метр: " << paintLitersForSqM
			<< "\n-количество краски на комнату: " << countRLiters() 
			<< "\nМатериал паркета: " << parket->paramParket()
			<< "\nТип потолка: " << ceiling->paramCeiling() 
			<< "\nПлощадь паркета/потолка: "<< lenght*width 
			<< std::endl; //очищает буфер потока
	}

};


class Flat
{
private:
	int countRooms;
	Room *room;
	int paintLitersForFlat;

public:

	void paramFlat() {
		cout << "\nВведите количество комнат в каждой квартире: ";
		cin >> countRooms;
		room = new Room();
		room->paramOfRoom();
	}

	void infForFlat() {
		cout << "\nКоличество комнат в каждой квартире: " << countRooms << std::endl;
		room->infForRoom();
	}

	int countLiters() {
		paintLitersForFlat = countRooms * room->countRLiters();
		return paintLitersForFlat;
	}

	~Flat() {
		delete room;
	}

};

class House
{
private:
	int countFloors;
	int countFlatsOnFloor;
	//int countLiters;
	Flat *flat;

public:

	void paramHouse() {
		cout << "\nВведите количество этажей в кажом доме: ";
		cin >> countFloors;
		cout << "\nВведите количество квартир на одном этаже: ";
		cin >> countFlatsOnFloor;
		flat = new Flat();
		flat->paramFlat();
	}

	int countAllFlats() {
		return (countFlatsOnFloor * countFloors);
	}
	void infForHouse() {
		cout << "\nКоличество этажей в каждом доме: \n" << countFloors << "\nКоличество квартир в каждом доме: " << countFlatsOnFloor * countFloors << std::endl;
		flat->infForFlat();
	}

	int countHLiters() {
		int countLiters;
		countLiters = countFlatsOnFloor * countFloors * flat->countLiters();
		return countLiters;
	}

	~House() {
		delete flat;
	}
};


class Street
{
private:
	string name;
	int countHouses;
	int countLiters;
	House *house;

public:

	void paramHouse() {
		cout << "\nВведите название улицы: ";
		cin >> name;
		cout << "\nВведите количество домов на улице "<< name << ": ";
		cin >> countHouses;
		house = new House();
		house->paramHouse();
	}

	int countHLiters() {
		countLiters = countHouses*house->countHLiters();
		return countLiters;
	}

	void infForHouse() {
		cout << "\nКоличество домов: " << countHouses << std::endl;
		cout << "\nОбщее количество квартир в домах: " << countHouses*house->countAllFlats() << std::endl; //
		house->infForHouse();
		cout << "\nОбщее количество краски: " << countHLiters() << std::endl;
	}

	~Street()
	{
		delete house;
	}

};


int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Для корректной работы программы нужно принять во внимание, что все дома на улице должны быть идентичными!";
	Street street;
	street.paramHouse();
	street.infForHouse();

	return 0;
}

