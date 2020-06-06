#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include<string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
#pragma warning(disable: 4996)
namespace spos {
	std::string shifr(std::string password) {
		int l = password.length();
		for (int i = 0; i < l; i++)
			password[i] = password[i] + 7;
		return password;
	}
	std::string deshifr(std::string password) {
		int l = password.length();
		for (int i = 0; i < l; i++)
			password[i] = password[i] - 7;
		return password;
	}

	int check_int(int choice, int max_numb)
	{
		while (!(std::cin >> choice) || (std::cin.peek() != '\n') || (choice < 0) || (choice > max_numb))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Повторите ввод!" << std::endl;
		}
		return choice;
	}
}


class Person// Абстрактный класс профиль
{
protected:
	static string login;
	string password;
public:
	//virtual int authorization(char* l, char* p) = 0;
	//virtual int authorization() = 0;
	virtual short int first_menu() = 0;
	virtual int second_menu() = 0;
	static string getlogin() {
		return login;
	}
	static void setlogin(string login) {
		Person::login = login;
	}
};

class staff {
	string name;
	string subject;
	string expierience;
	string email;
public:
	staff() { name = ""; subject = ""; expierience = ""; //email = ""; 
	}
	staff(string a, string b, string c) { name = a;  subject = b; expierience = c;}
	friend ostream& operator<<(ostream& stream, staff obj);
	friend bool operator==(staff a, string s);
	//friend bool operator==(staff a, staff b);
	friend bool operator>(staff a, staff b);
	void printInfo() {
		ifstream fin("staff.txt");
		if (fin.is_open()) {
			cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		cout << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
		while (getline(fin, name) && getline(fin, subject) && getline(fin, expierience)) {
			cout << setw(20) << name << setw(20) << subject << setw(12) << expierience << endl;
		}
		fin.close();
	}
	void addPerson() {
		ofstream fin("staff.txt", ofstream::app);
		if (fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		char c = 'y';
		while (c == 'y') {
			cout << "Введите ФИО преподавателя" << endl;  cin.ignore();  getline(cin, name);
			cout << "Введите название предмета" << endl;  cin >> subject;
			cout << "Введите опыт работы преподавателя" << endl;  cin >> expierience;
			fin << name << endl; fin << subject << endl;  fin << expierience << endl;
			cout << "Продолжить добавление записи?(y/n)" << endl; cin >> c;
		}
		fin.close();
	}
	void redactionInfo() {
		vector<staff> v;
		ifstream fin("staff.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, subject) && getline(fin, expierience)) {
			v.push_back(staff(name, subject, expierience));
		}
		fin.close();
		cout << setw(3) << "№" << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
		for (int j = 0; j < v.size(); j++)
			cout << setw(3) << j + 1 << setw(20) << v[j].name << setw(20) << v[j].subject << setw(12) << v[j].expierience << endl;
		cout << "Введите номер записи о преподавателе для редактирования." << endl; int J = 0; J = spos::check_int(J, v.size()); J = J - 1;
		cout << "Введите имя и фамилию преподаваля: "; string n; cin.ignore(); getline(cin, n);
		cout << "Введите название предмета: "; string p; getline(cin, p);
		cout << "Введите опыт работы преподавателя: "; string e; cin.ignore(); getline(cin, e);
		v[J].name = n; v[J].subject = p; v[J].expierience = e;

		ofstream f("staff.txt", ios::out);
		if (!f.is_open()) {
			cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		for (int j = 0; j < v.size(); j++) {
			f << v[j].name << endl << v[j].subject << endl << v[j].expierience << endl;
		}
		f.close();
		cout << "Редактирование произведено успешно!" << endl;
		system("pause");
	}
	string getName() {
		return name;
	}
	string getSub() {
		return subject;
	}
	string getExp() {
		return expierience;
	}
	void deleteInfo() {
		vector<staff> v;
		ifstream fin("staff.txt");
		if (!fin.is_open()) {
			cout << "Файл не обнаружен. Будет создан файл с указанным именем" << endl;
		}
		else {
			cout << "Файл открыт успешно!" << endl;
		}
		system("cls");
		int i = 0; int k = 0;
		while (getline(fin, name) && getline(fin, subject) && getline(fin, expierience)) {
			v.push_back(staff(name, subject, expierience));
		}
		fin.close();
		for (int j = 0; j < v.size(); j++)
			cout << v[j];
		cout << "Введите имя и фамилию преподавателя, запись о котором вы хотите удалить." << endl; string n; cin.ignore(); getline(cin, n);
		vector<staff>::iterator d = find(v.begin(), v.end(), n);
		if (d != v.end()) {
			v.erase(d);
			for (int j = 0; j < v.size(); j++)
				cout << v[j];

			ofstream f("staff.txt", ios::out);
			if (!f.is_open()) {
				//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
			}
			else {
				//cout << "Успешное открытие файла!" << endl;
			}
			system("cls");
			for (int j = 0; j < v.size(); j++) {
				f << v[j].name << endl << v[j].subject << endl << v[j].expierience << endl;
			}
			f.close();
			//cout << "Успешное удаление файла!" << endl;
		}
		else cout << "Такие имя и фамилия преподавателя не найдены!" << endl;
		system("pause");
	}
	void sorting(int k) {
		vector<staff> v;
		ifstream fin("staff.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, subject) && getline(fin, expierience)) {
			v.push_back(staff(name, subject, expierience));
		}
		fin.close();
		cout << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
		for (int j = 0; j < v.size(); j++)
			cout << setw(20) << v[j].name << setw(20) << v[j].subject << setw(12) << v[j].expierience << endl;
		if (k == 1) sort(v.rbegin(), v.rend(), greater<staff>());
		else if (k == 2) sort(v.rbegin(), v.rend(), greater<staff>());

		cout << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
		for (int j = 0; j < v.size(); j++)
			cout << setw(20) << v[j].name << setw(20) << v[j].subject << setw(12) << v[j].expierience << endl;

	}
	void filtration(int k) {
		vector<staff> v;
		ifstream fin("staff.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, subject) && getline(fin, expierience)) {
			v.push_back(staff(name, subject, expierience));
		}
		fin.close();
		int c;
		cout << "Ваши действия: " << endl;
		cout << "1. Фильтрация по опыту работы." << endl;
		cout << "2. Фильтрация по названию предмета." << endl;
		cin >> c;
	   
		if (c == 1) {
			cout << "Введите диапазон опыта работы: "; int d1 = 0, d2 = 0; cin >> d1 >> d2;
			for (int j = 0; j < v.size(); j++)
				if (atoi(v[j].expierience.c_str()) >= d1 && atoi(v[j].expierience.c_str()) <= d2) {
					cout << setw(20) << v[j].name << setw(20) << v[j].subject << setw(12) << v[j].expierience << endl;
				}
		}
		else if (c == 2) {
			cout << "Введите название предмета, который вас интересует: "; string s1, s2; cin >> s1;
			cout << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
			for (int j = 0; j < v.size(); j++)
				if (v[j].subject == s1) {
					cout << setw(20) << v[j].name << setw(20) << v[j].subject << setw(12) << v[j].expierience << endl;
				}
		}
	}
	void search(int k) {
		vector<staff> v;
		ifstream fin("staff.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, subject) && getline(fin, expierience)) {
			v.push_back(staff(name, subject, expierience));
		}
		fin.close();
		if (k == 1) {
			cout << "Введите ФИО преподавателя, запись о котором вы хотите найти." << endl; string n; cin.ignore(); getline(cin, n);
			vector<staff>::iterator d = find(v.begin(), v.end(), n);
			if (d != v.end()) {
				cout << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
				cout << setw(20) << d->name << setw(20) << d->subject << setw(12) << d->expierience << endl;
			}
			else cout << "Такого преподавателя не найдено!" << endl;
		}
		if (k == 2) {
			cout << "Введите предмет преподавателя, запись о котором вы хотите найти." << endl; string n; cin.ignore(); getline(cin, n);
			for (int j = 0; j < v.size(); j++)
				if (v[j].subject == n) {
					cout << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
					cout << setw(20) << v[j].name << setw(20) << v[j].subject << setw(12) << v[j].expierience << endl;
				}
		}
		if (k == 3) {
			cout << "Введите опыт работы преподавателя, запись о котором вы хотите найти." << endl; string n; cin.ignore(); getline(cin, n);
			for (int j = 0; j < v.size(); j++)
				if (v[j].expierience == n) {
					cout << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
					cout << setw(20) << v[j].name << setw(20) << v[j].subject << setw(12) << v[j].expierience << endl;
				}
		}
		system("pause");
	}

	int getMount() {
		vector<staff> v;
		ifstream fin("staff.txt");
		if (!fin.is_open()) {
			//cout << "Файл не обнаружен. Будет создан файл с указанным именем." << endl;
		}
		else {
			//cout << "Файл открыт успешно!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, subject) && getline(fin, expierience)) {
			v.push_back(staff(name, subject, expierience));
		}
		fin.close();
		return v.size();
	}

};
ostream& operator<<(ostream& stream, staff obj) {
	stream << obj.name << "  " << obj.subject << "  " << obj.expierience << endl;
	return stream;
}
bool operator==(staff a, string s) {
	return (a.name) == s;
}
bool operator>(staff a, staff b) {
	return a.name > b.name;
}


class student {
	string name;
	string email;
	string group;
	string marks;
	
public:
	student() {
		name = ""; email = ""; group = "";
	}
	student(string a, string b, string c) { name = a;  email = b; group = c; }
	friend ostream& operator<<(ostream& stream, student obj);
	friend bool operator==(student a, string s);
	friend bool operator>(student a, student b);
	void printInfo() {
		ifstream fin("student.txt");
		if (fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		cout << setw(20) << "ФИО" << setw(25) << "E-mail" << setw(20) << "Номер группы" << endl;
		while (getline(fin, name) && getline(fin, email) && getline(fin, group)) {
			cout << setw(20) << name << setw(25) << email << setw(20) << group << endl;
		}
		fin.close();
	}
	void addPerson() {
		ofstream fin("student.txt", ofstream::app);
		if (fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		char c = 'y';
		while (c == 'y') {
			cout << "Введите ФИО студента" << endl;  cin.ignore();  getline(cin, name);
			cout << "Введите e-mail студента" << endl;  cin >> email;
			cout << "Введите номер группы" << endl;  cin >> group;
			fin << name << endl; fin << email << endl;  fin << group << endl;
			cout << "Продолжить добавление записи?(y/n)" << endl; cin >> c;
		}
		fin.close();
	}
	void redactionInfo() {
		vector<student> vl;
		ifstream fin("student.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, email) && getline(fin, group)) {
			vl.push_back(student(name, email, group));
		}
		fin.close();
		cout << setw(3) << "№" << setw(20) << "ФИО" << setw(25) << "Предмет" << setw(20) << "Опыт работы" << endl;
		for (int j = 0; j < vl.size(); j++)
			cout << setw(3) << j + 1 << setw(20) << vl[j].name << setw(25) << vl[j].email << setw(20) << vl[j].group << endl;
		cout << "Введите номер записи о студенте для редактирования информации." << endl; int J = 0; J = spos::check_int(J, vl.size()); J = J - 1;
		cout << "Ведите имя и фамилию студента: "; string n; cin.ignore(); getline(cin, n);
		cout << "Введите e-mail студента: "; string p; getline(cin, p);
		cout << "Введите номер группы: "; string e; cin.ignore(); getline(cin, e);
		vl[J].name = n; vl[J].email = p; vl[J].group = e;

		ofstream f("student.txt", ios::out);
		if (!f.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		for (int j = 0; j < vl.size(); j++) {
			f << vl[j].name << endl << vl[j].email << endl << vl[j].group << endl;
		}
		f.close();
		cout << "Редактирование произведено успешно!" << endl;
		system("pause");
	}
	void deleteInfo() {
		vector<student> vl;
		ifstream fin("student.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		int i = 0; int k = 0;
		while (getline(fin, name) && getline(fin, email) && getline(fin, group)) {
			vl.push_back(student(name, email, group));
		}
		fin.close();
		for (int j = 0; j < vl.size(); j++)
			cout << vl[j];
		cout << "Введите имя и фамилию студента, запись о котором вы хотите удалить." << endl; string n; cin.ignore(); getline(cin, n);
		vector<student>::iterator d = find(vl.begin(), vl.end(), n);
		if (d != vl.end()) {
			vl.erase(d);
			for (int j = 0; j < vl.size(); j++)
				cout << vl[j];

			ofstream f("student.txt", ios::out);
			if (!f.is_open()) {
				//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
			}
			else {
				//cout << "Успешное открытие файла!" << endl;
			}
			system("cls");
			for (int j = 0; j < vl.size(); j++) {
				f << vl[j].name << endl << vl[j].email << endl << vl[j].group << endl;
			}
			f.close();
			//cout << "Успешное удаление файла!" << endl;
		}
		else cout << "Такие имя и фамилия преподавателя не найдены!" << endl;
		system("pause");
	}
	void sorting(int k) {
		vector<student> vl;
		ifstream fin("student.txt");
		if (!fin.is_open()) {
			cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, email) && getline(fin, group)) {
			vl.push_back(student(name, email, group));
		}
		fin.close();
		cout << setw(20) << "ФИО" << setw(30) << "Email" << setw(12) << "Номер группы" << endl;
		for (int j = 0; j < vl.size(); j++)
			cout << setw(20) << vl[j].name << setw(25) << vl[j].email << setw(20) << vl[j].group << endl;
		if (k == 1) sort(vl.rbegin(), vl.rend(), greater<student>());
		else if (k == 2) sort(vl.rbegin(), vl.rend(), greater<student>());

		cout << setw(20) << "ФИО" << setw(25) << "Email" << setw(20) << "Номер группы" << endl;
		for (int j = 0; j < vl.size(); j++)
			cout << setw(20) << vl[j].name << setw(25) << vl[j].email << setw(20) << vl [j] .group << endl;

	}
	void filtration(int k) {
		vector<student> vl;
		ifstream fin("student.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, email) && getline(fin, group)) {
			vl.push_back(student(name, email, group));
		}
		fin.close();
		cout << "Введите диапазон значений для вывода группы: " << endl; int d1 = 0, d2 = 0; cin >> d1 >> d2;
		//cout << "Введите email, которые вас интересуют: " << endl; string s1, s2; cin >> s1 >> s2;
		cout << setw(20) << "ФИО" << setw(25) << "E-mail" << setw(20) << "Номер группы" << endl;
		for (int j = 0; j < vl.size(); j++)
			if (atoi(vl[j].group.c_str()) >= d1 && atoi(vl[j].group.c_str()) <= d2) {

				cout << setw(20) << vl[j].name << setw(25) << vl[j].email << setw(20) << vl[j].group << endl;
			}
	}
	void search(int k) {
		vector<student> vl;
		ifstream fin("student.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, email) && getline(fin, group)) {
			vl.push_back(student(name, email, group));
		}
		fin.close();
		if (k == 1) {
			cout << "Введите ФИО студента, запись о котором вы хотите найти." << endl; string n; cin.ignore(); getline(cin, n);
			vector<student>::iterator d = find(vl.begin(), vl.end(), n);
			if (d != vl.end()) {
				cout << setw(20) << "ФИО" << setw(25) << "E-mail" << setw(20) << "Номер группы" << endl;
				cout << setw(20) << d->name << setw(25) << d->email << setw(20) << d->group << endl;
			}
			else cout << "Такого студента не найдено!" << endl;
		}
		if (k == 2) {
			cout << "Введите email студента, запись о котором вы хотите найти." << endl; string n; cin.ignore(); getline(cin, n);
			for (int j = 0; j < vl.size(); j++)
				if (vl[j].email == n) {
					cout << setw(20) << "ФИО" << setw(25) << "E-mail" << setw(20) << "Номер группы" << endl;
					cout << setw(20) << vl[j].name << setw(25) << vl[j].email << setw(20) << vl[j].group << endl;
				}
		}
		if (k == 3) {
			cout << "Введите номер группы студента, запись о котором вы хотите найти." << endl; string n; cin.ignore(); getline(cin, n);
			for (int j = 0; j < vl.size(); j++)
				if (vl[j].group == n) {
					cout << setw(20) << "ФИО" << setw(25) << "E-mail" << setw(20) << "Номер группы" << endl;
					cout << setw(20) << vl[j].name << setw(25) << vl[j].email << setw(20) << vl[j].group << endl;
				}
		}
		system("pause");
	}
};
ostream& operator<<(ostream& stream, student obj) {
	stream << obj.name << "  " << obj.email << "  " << obj.group << endl;
	return stream;
}
bool operator==(student a, string s) {
	return (a.name) == s;
}
bool operator>(student a, student b) {
	return a.name > b.name;
}



template<class T>
T check(T t1, T t2) {
	T p; cin >> p;
	if (p >= t1 && p <= t2) return p;
}





class timetable {

public:

	int metod() {
		vector<staff> v;
		string nam, subject, expierience;
		ifstream fin("staff.txt");
		if (fin.is_open()) {
			//cout << "Файл не найден. Создается файл с данным именем!" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, nam) && getline(fin, subject) && getline(fin, expierience)) {
			v.push_back(staff(nam, subject, expierience));
		}
		fin.close();
		cout << setw(3) << "№" << setw(20) << "ФИО" << setw(20) << "Предмет" << setw(12) << "Опыт работы" << endl;
		for (int i = 0; i < v.size(); i++)
			cout << setw(3) << i + 1 << setw(20) << v[i].getName() << setw(20) << v[i].getSub() << setw(12) << v[i].getExp() << endl;
		cout << "Выберите преподавателя и предмет по номеру записи:" << endl; int k = 0; k = spos::check_int(k, v.size()); k = k - 1;
		ifstream f1("timetable.txt");
		string sub, d;
		int kol=0;
		if (!f1.is_open()) {
			cout << "Файл не найден. Создается файл с данным именем!" << endl;
			string fname = v[k].getSub() + ".txt";
			double R12, R21,  R31, R13, R23, R32;
			ifstream fsub(fname);
			fsub >> R12;
			fsub >> R13;
			fsub >> R21;
			fsub >> R23;
			fsub >> R31;
			fsub >> R32;
			fsub.close();
			cout << "Оценка компетентности:"; double r1 = (R21 + R31) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r1; cout << endl;
			cout << "Оценка компетентности:"; double r2 = (R12 + R32) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r2; cout << endl;
			cout << "Оценка компетентности:"; double r3 = (R13 + R23) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r3; cout << endl;

			double Rj;

			cout << "Оценка дисперсии:"; double d1 = pow((R12 + R13 + (R21 + R31) / 2), 2); cout << d1; cout << endl;
			cout << "Оценка дисперсии:"; double d2 = pow((R21 + R23 + (R12 + R32) / 2), 2); cout << d2; cout << endl;
			cout << "Оценка дисперсии:"; double d3 = pow((R31 + R32 + (R13 + R23) / 2), 2); cout << d3; cout << endl;
			string data[3];
			cout << "Введите возможные даты проведения экзамена по предмету " << v[k].getSub() << " :"; cin >> data[0] >> data[1] >> data[2];

			cout << "Введите оценки целей первого эксперта: "; double c11, c12, c13; cin >> c11 >> c12 >> c13; cout << endl;
			cout << "Введите оценки целей второго эксперта: "; double c21, c22, c23; cin >> c21 >> c22 >> c23; cout << endl;
			cout << "Введите оценки целей третьего эксперта: "; double c31, c32, c33; cin >> c31 >> c32 >> c33; cout << endl;


			double k1 = r1 * (c11 + c21 + c31) / (r1 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));
			double k2 = r2 * (c12 + c22 + c32) / (r2 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));
			double k3 = r3 * (c13 + c23 + c33) / (r3 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));

			cout << "Оценка дисперсии вариантов 1:"; double D1 = pow((c11 + c12 + c13 + (c11 + c21 + c31) / 2), 2); cout << D1; cout << endl;
			cout << "Оценка дисперсии вариантов 2:"; double D2 = pow((c21 + c22 + c23 + (c12 + c22 + c32) / 2), 2); cout << D2; cout << endl;
			cout << "Оценка дисперсии ывриантов 3:"; double D3 = pow((c31 + c32 + c33 + (c13 + c23 + c33) / 2), 2); cout << D3; cout << endl;

			double w1 = k1 * c11 + k2 * c12 + k3 * c13;
			double w2 = k1 * c21 + k2 * c22 + k3 * c23;
			double w3 = k1 * c31 + k2 * c32 + k3 * c33;
			string better_data;
			cout << "Наиболее подходящая дата: ";
			if (w1 > w2 && w1 > w3) {
				better_data = data[0];
				cout << data[0];
			}
			if (w2 > w1 && w2 > w3) {
				better_data = data[1];
				cout << data[1];
			}
			if (w3 > w1 && w3 > w2) {
				better_data = data[2];
				cout << data[2];
			}
			cout << endl;
			system("pause");
			ofstream ff("timetable.txt");
			if (ff.is_open()) {
				cout << "Файл не найден. Создается файл с данным именем!" << endl;
			}
			else {
				cout << "Успешное открытие файла!" << endl;
			}
			system("cls");
			for (int i = 0; i < 4; i++) {
				ff << v[k].getSub() << endl;;
				ff << better_data << endl;
			}
			ff.close();

		}
		else {
			cout << "Успешное открытие файла!" << endl;
			system("pause");
			while (getline(f1, sub) && getline(f1, d)) {
				if (sub == v[k].getSub()) {
					cout << "По этому предмету уже есть расписание!" << endl;
					cout << "Продолжить редактирование даты?(1/0)" << endl; int c; cin >> c;
					if (c == 1) {
						string fname = v[k].getSub() + ".txt";
						double R12,  R21,  R31, R13, R23, R32;
						ifstream fsub(fname);
						fsub >> R12;
						fsub >> R13;
						fsub >> R21;
						fsub >> R23;
						fsub >> R31;
						fsub >> R32;
						fsub.close();

						cout << "Оценка компетентности:"; double r1 = (R21 + R31) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r1; cout << endl;
						cout << "Оценка компетентности:"; double r2 = (R12 + R32) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r2; cout << endl;
						cout << "Оценка компетентности:"; double r3 = (R13 + R23) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r3; cout << endl;

						double Rj;

						cout << "Оценка дисперсии:"; double d1 = pow((R12 + R13 + (R21 + R31) / 2), 2); cout << d1; cout << endl;
						cout << "Оценка дисперсии:"; double d2 = pow((R21 + R23 + (R12 + R32) / 2), 2); cout << d2; cout << endl;
						cout << "Оценка дисперсии:"; double d3 = pow((R31 + R32 + (R13 + R23) / 2), 2); cout << d3; cout << endl;
						string data[3];
						cout << "Введите возсожные даты проведения экзамена по предмету " << v[k].getSub() << " :"; cin >> data[0] >> data[1] >> data[2];

						cout << "Введите оценки целей первого эксперта: "; double c11, c12, c13; cin >> c11 >> c12 >> c13; cout << endl;
						cout << "Введите оценки целей второго эксперта: "; double c21, c22, c23; cin >> c21 >> c22 >> c23; cout << endl;
						cout << "Введите оценки целей третьего эксперта: "; double c31, c32, c33; cin >> c31 >> c32 >> c33; cout << endl;


						double k1 = r1 * (c11 + c21 + c31) / (r1 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));
						double k2 = r2 * (c12 + c22 + c32) / (r2 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));
						double k3 = r3 * (c13 + c23 + c33) / (r3 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));

						cout << "Коэффициент предпочтительности 1: "; cout << k1; cout << endl;
						cout << "Коэффициент предпочтительности 2: "; cout << k2; cout << endl;
						cout << "Коэффициент предпочтительности 3: "; cout << k3; cout << endl;

						cout << "Оценка дисперсии вариантов 1:"; double D1 = pow((c11 + c12 + c13 + (c11 + c21 + c31) / 2), 2); cout << D1; cout << endl;
						cout << "Оценка дисперсии вариантов 2:"; double D2 = pow((c21 + c22 + c23 + (c12 + c22 + c32) / 2), 2); cout << D2; cout << endl;
						cout << "Оценка дисперсии вариантов 3:"; double D3 = pow((c31 + c32 + c33 + (c13 + c23 + c33) / 2), 2); cout << D3; cout << endl;

						double w1 = k1 * c11 + k2 * c12 + k3 * c13;
						double w2 = k1 * c21 + k2 * c22 + k3 * c23;
						double w3 = k1 * c31 + k2 * c32 + k3 * c33;
						string better_data;
						cout << "Наиболее подходящая дата: ";
						if (w1 > w2 && w1 > w3) {
							better_data = data[0];
							cout << data[0];
						}
						if (w2 > w1 && w2 > w3) {
							better_data = data[1];
							cout << data[1];
						}
						if (w3 > w1 && w3 > w2) {
							better_data = data[2];
							cout << data[2];
						}
						cout << endl;
						system("pause");
						string subj[4], final_data[4];
						ifstream ff("timetable.txt");
						if (ff.is_open()) {
							cout << "Файл не найден. Создается файл с данным именем!" << endl;
						}
						else {
							cout << "Успешное открытие файла!" << endl;
						}
						system("cls");
						for (int i = 0; i < 4; i++) {
							ff >> subj[i];
							ff >> final_data[i];
						}
						ff.close();

						for (int i = 0; i < 4; i++) {
							if (subj[i] == v[k].getSub()) {
								final_data[i] = better_data;;
							}
						}

						ofstream f("timetable.txt", ios::out);
						if (f.is_open()) {
							cout << "Файл не найден. Создается файл с данным именем!" << endl;
						}
						else {
							cout << "Успешное открытие файла!" << endl;
						}
						system("cls");
						for (int i = 0; i < 4; i++) {
							f << subj[i] << endl;
							f << final_data[i] << endl;
						}
						f.close();
						
						
						return 0;
					}
					else return 0;
				}
				else {

				string fname = v[k].getSub() + ".txt";
				double R12,  R21,  R31, R13, R23, R32;
				ifstream fsub(fname);
				fsub >> R12;
				fsub >> R13;
				fsub >> R21;
				fsub >> R23;
				fsub >> R31;
				fsub >> R32;
				fsub.close();

					cout << "Оценка компетентности:"; double r1 = (R21 + R31) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r1; cout << endl;
					cout << "Оценка компетентности:"; double r2 = (R12 + R32) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r2; cout << endl;
					cout << "Оценка компетентности:"; double r3 = (R13 + R23) / (R12 + R13 + R21 + R23 + R31 + R32); cout << r3; cout << endl;

					double Rj;

					cout << "Оценка дисперсии:"; double d1 = pow((R12 + R13 + (R21 + R31) / 2), 2); cout << d1; cout << endl;
					cout << "Оценка дисперсии:"; double d2 = pow((R21 + R23 + (R12 + R32) / 2), 2); cout << d2; cout << endl;
					cout << "Оценка дисперсии:"; double d3 = pow((R31 + R32 + (R13 + R23) / 2), 2); cout << d3; cout << endl;
					string data[3];
					cout << "Введите возсожные даты проведения экзамена по предмету " << v[k].getSub() << " :"; cin >> data[0] >> data[1] >> data[2];
					cout << "Введите оценки целей первого эксперта: "; double c11, c12, c13; cin >> c11 >> c12 >> c13; cout << endl;
					cout << "Введите оценки целей второго эксперта: "; double c21, c22, c23; cin >> c21 >> c22 >> c23; cout << endl;
					cout << "Введите оценки целей третьего эксперта: "; double c31, c32, c33; cin >> c31 >> c32 >> c33; cout << endl;
					double k1 = r1 * (c11 + c21 + c31) / (r1 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));
					double k2 = r2 * (c12 + c22 + c32) / (r2 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));
					double k3 = r3 * (c13 + c23 + c33) / (r3 * (c11 + c12 + c13 + c21 + c22 + c23 + c31 + c32 + c33));
					cout << "Оценка дисперсии:"; double D1 = pow((c11 + c12 + c13 + (c11 + c21 + c31) / 2), 2); cout << D1; cout << endl;
					cout << "Оценка дисперсии:"; double D2 = pow((c21 + c22 + c23 + (c12 + c22 + c32) / 2), 2); cout << D2; cout << endl;
					cout << "Оценка дисперсии:"; double D3 = pow((c31 + c32 + c33 + (c13 + c23 + c33) / 2), 2); cout << D3; cout << endl;
					double w1 = k1 * c11 + k2 * c12 + k3 * c13;
					double w2 = k1 * c21 + k2 * c22 + k3 * c23;
					double w3 = k1 * c31 + k2 * c32 + k3 * c33;
					string better_data;
					cout << "Наиболее подходящая дата: ";
					if (w1 > w2 && w1 > w3) {
						better_data = data[0];
						cout << data[0];
					}
					if (w2 > w1 && w2 > w3) {
						better_data = data[1];
						cout << data[1];
					}
					if (w3 > w1 && w3 > w2) {
						better_data = data[2];
						cout << data[2];
					}
					cout << endl;
					system("pause");
					string subj[4], final_data[4];
					ifstream ff("timetable.txt");
					if (ff.is_open()) {
						//cout << "Файл не найден. Создается файл с данным именем!" << endl;
					}
					else {
						//cout << "Успешное открытие файла!" << endl;
					}
					system("cls");
					for (int i = 0; i < 4; i++) {
						ff >> subj[i];
						ff >> final_data[i];
					}
					ff.close();

					for (int i = 0; i < 4; i++) {
						if (subj[i] == v[k].getSub()) {
							final_data[i] = better_data;;
						}
					}
					ofstream f("timetable.txt", ios::out);
					if (f.is_open()) {
						//cout << "Файл не найден. Создается файл с данным именем!" << endl;
					}
					else {
						//cout << "Успешное открытие файла!" << endl;
					}
					system("cls");
					for (int i = 0; i < 4; i++) {
						f << subj[i] << endl;
						f << final_data[i] << endl;
					}
					f.close();
					return 0;
				}
			}
		}
		f1.close();
	}
	void kusok() {

	}
};
	
class univer{
	string name;
	string adress;
	string contacts;
	string time;
public:
	univer() {
		name = ""; adress = ""; contacts = ""; time = "";
	}
	univer(string a, string b, string c, string d) { name = a;  adress = b; contacts = c; time = d;}
	void printInfo() {
		ifstream fin("univer.txt");
		if (fin.is_open()) {
			cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		//cout << "Университет N" << endl;
		cout << setw(15) << "Название" << setw(20) << "Адрес" << setw(20) << "Контакты" << setw(20) << "Время работы" << endl;
		while (getline(fin, name) && getline(fin, adress) && getline(fin, contacts) && getline(fin, time)) {
			cout << setw(15) << name << setw(20) << adress << setw(20) << contacts << setw(20) << time << endl;
		}
		system("pause");
		fin.close();
	}
	void addInfo() {
		ofstream fin("univer.txt", ofstream::app);
		if (fin.is_open()) {
		//	cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		char c = 'y';
		while (c == 'y') {
			cout << "Введите название учреждения." << endl;  cin.ignore();  getline(cin, name);
			cout << "Введите адрес учреждения." << endl;  cin >> adress;
			cout << "Введите контакты." << endl;  cin >> contacts;
			cout << "Введите режим работы." << endl;  cin >> time;
			fin << name << endl; fin << adress << endl;  fin << contacts << endl; fin << time << endl;
			//c == 'n';
			cout << "Продолжить добавление записи?(y/n)" << endl; cin >> c;
		}
		fin.close();
	}
	void redact() {
		vector<univer> vl;
		ifstream fin("univer.txt");
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, adress) && getline(fin, contacts) && getline(fin, time)) {
			vl.push_back(univer(name, adress, contacts, time));
		}
		fin.close();
		cout << setw(15) << "Название" << setw(20) << "Адрес" << setw(20) << "Контакты" << setw(20) << "Время работы" << endl;
		for (int j = 0; j < vl.size(); j++)
			cout << setw(15) << vl[j].name << setw(20) << vl[j].adress << setw(20) << vl[j].contacts << setw(20) << vl[j].time << endl;
		cout << "Редактирование информации об университете." << endl; int J = 0; J = spos::check_int(J, vl.size()); J = J - 1;
		cout << "Введите название учреждения: "; string n; cin.ignore(); getline(cin, n);
		cout << "Введите адрес: "; string p; getline(cin, p);
		cout << "Введите контакты: "; string e; cin.ignore(); getline(cin, e);
		cout << "Введите режим работы: "; string q; cin.ignore(); getline(cin, q);
		vl[J].name = n; vl[J].adress = p; vl[J].contacts = e; vl[J].time = q;

		ofstream f("univer.txt", ios::out);
		if (!f.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
			//cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		for (int j = 0; j < vl.size(); j++) {
			f << vl[j].name << endl << vl[j].adress << endl << vl[j].contacts << endl << vl[j].time << endl;
		}
		f.close();
		cout << "Редактирование  завершено!" << endl;
		system("pause");
	}

	int getAmount() {
		vector<univer> vl;
		ifstream fin("univer.txt");
		if (!fin.is_open()) {
			//cout << "Файл не обнаружен. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "Файл открыт успешно!" << endl;
		}
		system("cls");
		while (getline(fin, name) && getline(fin, adress) && getline(fin, contacts) && getline(fin, time)) {
			vl.push_back(univer(name, adress, contacts, time));
		}
		fin.close();
		return vl.size();
	}
};

class Admin: public Person
{
	string login, password;
public:
	string log, passw;
	Admin(){}
	Admin(string log, string pass) { login = log; password = pass; }
	friend ostream& operator<<(ostream& stream, Admin obj);
	friend bool operator==(Admin a, string s);
	virtual int  authorization() {
		while (true)
		{
			int k = 0;
			ifstream fin("admin.txt");
			if (!fin.is_open()) {
				//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
			}
			else {
				//cout << "Успешное открытие файла!" << endl;
			}
			cout << "Введите логин: ";  cin >> login;
			cout << "Введите пороль: "; cin >> password;
			password = spos::shifr(password);
			while (!fin.eof())
			{
				fin >> log;
				fin >> passw;
				if ((login == log) && (password == passw))
				{
					k++;
					break;
				}
			}
			fin.close();
			if (k != 0) return 5;//{ second_menu(); break; }
			else {
				system("cls");
				cout << "Неправильно введен логин или пароль" << endl;
				return 0;
				break;
			}

		}
	}
	void registration(string fname) {
		ofstream fin(fname, iostream::app);
		if (!fin.is_open()) {
		//	cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "Успешное открытие файла!" << endl;

			system("cls");
			cout << "Введите логин: ";  cin >> login;
			cout << "Введите пороль: "; cin >> password;
			password = spos::shifr(password);
			fin << login << endl;
			fin << password << endl;

		}
		fin.close();
	}
	void del(string fname) {
		vector<Admin> v;
		ifstream fin(fname);
		if (!fin.is_open()) {
		//	cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		int i = 0; int k = 0;
		while (fin >> login && fin >> password) {
			v.push_back(Admin(login, password));
		}
		fin.close();
		for (int j = 0; j < v.size(); j++)
			cout << v[j];
		cout << "Введите логин пользователя, запись о котором вы хотите удалить." << endl; string log; cin.ignore(); getline(cin, log);
		vector<Admin>::iterator d = find(v.begin(), v.end(), log);
		if (d != v.end()) {
			v.erase(d);
			for (int j = 0; j < v.size(); j++)
				cout << v[j];

			ofstream f(fname, ios::out);
			if (!f.is_open()) {
				//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
			}
			else {
			//	cout << "Успешное открытие файла!" << endl;
			}
			system("cls");
			for (int j = 0; j < v.size(); j++) {
				f << v[j].login << endl << v[j].password << endl;
			}
			f.close();
		}
		else cout << "Такой логин не найден!" << endl;
	}
	void print(string fname) {
		ifstream fin(fname);
		if (!fin.is_open()) {
			//cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "Успешное открытие файла!" << endl;
		}
		system("cls");
		cout << "логин " << " пароль " << endl;
		while (fin >> login && fin >> password) {
			cout << login << "  " << password << endl;
		}
		system("pause");
		fin.close();
	}
	short int first_menu()
	{
		system("cls");
		int choice = 0;
		cout << "Меню:" << endl
			<< "1. Информация об университете." << endl
			<< "2. Информация о преподавателях." << endl
			<< "3. Информация о студентах." << endl
			<< "4. Управление пользователями." << endl
			<< "5. Расписание" << endl
			<< "6. Выход." << endl;
		choice = spos::check_int(choice, 6);
		return choice;
	}

	int second_menu()
	{
		int i = 0, x = 0;
		short int choice = 1;
		Admin admin;
		univer uni;
		staff person;
		student stud;
		timetable table;
		while (true)
		{
			choice = first_menu();
			system("cls");
			switch (choice) {
			case 1:
				system("cls");
				cout << "1. Добавление информации" << endl
					 << "2. Просмотр информации" << endl
					 << "3. Редактирование информации" << endl
					 << "4. Выход" << endl;
				choice = spos::check_int(choice, 4);
				if (choice == 1) {
					uni.addInfo();
				}
				else if (choice == 2)
				{
					uni.printInfo();
				}
				else if (choice == 3)
				{
					uni.redact();
				}
				else 
					break;
				break;
			case 2:
				cout << "1. Сортировка преподавателей." << endl
					<< "2. Поиск преподавателя. " << endl
					<< "3. Добавление преподавателя." << endl
					<< "4. Просмотр всех преподавателей.  " << endl
					<< "5. Фильтрация преподавателей." << endl
					<< "6. Редактирование информации о преподавателях." << endl
					<< "7. Удаление записи о преподавателях." << endl
					<< "8. Выход." << endl;
				choice = spos::check_int(choice, 8);
				if (choice == 1)
				{
					system("cls");
					cout << "1. Сортировать по ФИО(по возрастанию) " << endl
						<< "2. Сортировать по ФИО(по убыванию) " << endl
						<< "3. Выход" << endl;
					i = spos::check_int(i, 5);
					if (i == 1)
						person.sorting(1);
					if (i == 2)
						person.sorting(2);
					system("pause");
					break;
				}
				else if (choice == 2)
				{
					cout << "1.поиск по ФИО" << endl <<
						    "2.поиск по названию предмета" << endl <<
						    "3.поиск по опыту работы" << endl;
					i = spos::check_int(i, 3);
					system("cls");
					person.search(i);
					system("pause");
				}
				else if (choice == 3)
				{
					system("cls");
					person.addPerson();
					system("pause");
				}
				else if (choice == 4)
				{
					system("cls");
					person.printInfo();
					system("pause");
				}
				else if (choice == 5)
				{
					system("cls");
					person.filtration(5
					);
					system("pause");
				}
				else if (choice == 6)
				{
					system("cls");
					person.redactionInfo();
					system("pause");
				}
				else if (choice == 7)
				{
					person.deleteInfo();
				}
				else
					break;
				break;
			case 3:
				cout << "1. Сортировка информации о студентах." << endl
					<< "2. Поиск студента. " << endl
					<< "3. Добавление студента." << endl
					<< "4. Просмотр всех студентов.  " << endl
					<< "5. Фильтрация студентов." << endl
					<< "6. Редактирование информации о студентах." << endl
					<< "7. Удаление записи о студенте." << endl
					<< "8. Выход." << endl;
				choice = spos::check_int(choice, 8);
				if (choice == 1)
				{
					system("cls");
					cout << "1. Сортировка по ФИО (по возрастанию)" << endl
						<< "2. Сортировка по ФИО (по убыванию)" << endl
						<< "3. Выход" << endl;
					i = spos::check_int(i, 5);
					if (i == 1)
						stud.sorting(1);
					if (i == 2)
						stud.sorting(2);
					system("pause");
					break;
				}
				else if (choice == 2)
				{
					cout << "1.поиск по ФИО" << endl <<
						"2.поиск по email" << endl <<
						"3.поиск по номеру группы" << endl;
					i = spos::check_int(i, 3);
					system("cls");
					stud.search(i);
					system("pause");
				}
				else if (choice == 3)
				{
					system("cls");
					stud.addPerson();
					system("pause");
				}
				else if (choice == 4)
				{
					system("cls");
					stud.printInfo();
					system("pause");
				}
				else if (choice == 5)
				{
					system("cls");
					stud.filtration(5);
					system("pause");
				}
				else if (choice == 6)
				{
					system("cls");
					stud.redactionInfo();
					system("pause");
				}
				else if (choice == 7)
				{
					stud.deleteInfo();
				}
				else
					break;
				break;
			case 4:
				system("cls");
				cout << "1. Создать пользователя " << endl
					 << "2. Удалить пользователя " << endl
					 << "3. Просмотр всех пользователей" << endl
					 << "4. Выход " << endl;
				i = spos::check_int(i, 4);
				if (i == 1) {
					cout << "1.Создать учетную запись от имени администратора" << endl << "2.Создать учетную запись от имени пользователя" << endl; int c = 0; c = spos::check_int(c, 2);
					if (c == 1)
						admin.registration("admin.txt");
					else if (c == 2) admin.registration("user.txt");
					break;
				}
				else if (i == 2) {
					cout << "1.Удалить учетную запись от имени администратора" << endl << "2.Удалить учетную запись от имени пользователя" << endl; int c = 0; c = spos::check_int(c, 2);
					if (c == 1)
						admin.del("admin.txt");
					else if (c == 2) admin.del("user.txt");
					break;
				}
				else if (i == 3) {
					cout << "1. Просмотреть  учетные записи от имени администратора" << endl << "2. Просмотреть  учетные записи от имени пользователя" << endl; int c = 0; c = spos::check_int(c, 2);
					if (c == 1)
						admin.print("admin.txt");
					else if (c == 2) admin.print("user.txt");
					break;
				}
				else
					break;
			case 5:
				table.metod();
				break;
			case 6:
				system("cls");
				return 0;
				break;
			}
		}
	}
};
ostream& operator<<(ostream& stream, Admin obj) {
	stream << obj.login << "  " << obj.password << endl;
	return stream;
}
bool operator==(Admin a, string s) {
	return (a.login) == s;
}
class User: public Person
{
	string login, password;
public:
	string log, passw;
	User() { login = ""; password = ""; }
	User(string a, string b) { login = a; password = b; }
	friend ostream& operator<<(ostream& stream, User obj);
	friend bool operator==(User a, string s);

	virtual int  authorization(char *l, char *p ) {
		login = l; password = p;
		while (true)
		{
			int c = 0;
			ifstream fin("user.txt");
			if (!fin.is_open()) {
			//	cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
				//break;
			}
			else {
			//	cout << "Успешное открытие файла!" << endl;
			}

				//system("cls");
			password = spos::shifr(password);
			while (!fin.eof()) {
					//getline(fin, log);
					//getline(fin, passw);
					//password = spos::deshifr(password);
				fin >> log;
				fin >> passw;
				if ((login == log) && (password == passw))
					{
						c++;
						break;
					}

				}
				fin.close();
				if (c != 0)  return 1; //{ second_menu(); break; }
				else {
					system("cls");
					cout << "Неправильно введен логин или пароль" << endl;
					return 0;
					break;
				}
			}
		}
	void redactLogin() {
		vector<User> v;
		ifstream fin("user.txt");
		if (!fin.is_open()) {
		//	cout << "Файл не обнаружен. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "Файл открыт успешно!" << endl;
		}
		system("cls");
		int i = 0; int k = 0;
		while (fin >> login && fin >> password) {
			v.push_back(User(login, password));
		}
		fin.close();
		k = 0;
		cout << "Введите свой логин: "; string log; cin >> log;
		cout << "Введите свой пароль: "; string pas; cin >> pas;
		for (int j = 0; j < v.size(); j++) {
			if (v[j].login == log && v[j].password == pas) {
				cout << "Введите новый логин:"; cin >> log;
				cout << "Введите новый пароль:"; cin >> pas;
				v[j].login = log; v[j].password = pas;
				ofstream f("user.txt", ios::out);
				if (!f.is_open()) {
				//	cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
				}
				else {
					//cout << "Успешное открытие файла!" << endl;
				}
				system("cls");
				for (int j = 0; j < v.size(); j++) {
					f << v[j].login << endl << v[j].password << endl;
				}
				f.close();
				k++;
			}
		}
		if (k == 0) cout << "Такого логина или пароля нет!" << endl;
	}

	short int first_menu()
	{
		system("cls");
		int choice = 0;
		cout << "Меню:" << endl
			<< "1. Информация об университете." << endl
			<< "2. Управление информацией о студентах." << endl
			<< "3. Управление пользователями." << endl
			<< "4. Расписание" << endl
			<< "5. Выход." << endl;
		choice = spos::check_int(choice, 5);
		return choice;
	}
	int second_menu()
	{
		int i = 0, x = 0;
		short int choice = 1;
		User user;
		univer u;
		timetable tab;
		while (true)
		{
			choice = first_menu();
			system("cls");
			switch (choice) {
			case 1:
				system("cls");
				u.printInfo();
				break;
				//cout << "1. Просмотр информации" << endl
				//	 << "2. Редактировать информацию" << endl
				//	 << "3. Выход" << endl;
				//choice = spos::check_int(choice, 3);
				//if (choice == 1)
				//	break;
				//break;
			case 2:
				//cout << "1. Сортировка товара." << endl
				//	 << "2. Поиск товара. " << endl
				//	 << "3. Добавление товара." << endl
					// << "4. Просмотр всего товара.  " << endl
					 //<< "5. Фильтрация товара." << endl
					 //<< "6. Редактирование информации о товаре." << endl
					 //<< "7. Удаление записи о товаре." << endl
					 //<< "8. Выход." << endl;
				//choice = spos::check_int(choice, 8);
				//if (choice == 1)
				//{
					//system("cls");
					//cout << "1. Сортировать по цене(по возрастанию) " << endl
						//<< "2. Сортировать по цене(по убыванию) " << endl
						//<< "3. Сортировать по поназванию (А до Я)" << endl
						//<< "4. Сортировать по названию (Я до А)" << endl
						//<< "5. Выход" << endl;
					//i = spos::check_int(i, 5);
					//if (i == 1)
					//	if (i == 2)
						//	if (i == 3)
						//		if (i == 4)
						//			system("pause");
					//break;
			//	}
			//	else if (choice == 2)
			//	{
				//	system("cls");
				//	system("pause");
				//}
				//else if (choice == 3)
				//{
				//	system("cls");
				//	system("pause");
				//}
				//else if (choice == 4)
				//{
					//system("cls");
				//	system("pause");
				//}
				//else if (choice == 5)
				//{
					//system("cls");
				//	system("pause");
				//}
				//else if (choice == 6)
				//{
					//system("cls");
					//system("pause");
				//}
			//	else if (choice == 7)
				//{
					////obl.changestudent();
				//}
				//else if (choice == 8)
				//	break;
				system("cls");
				user.redactLogin();
				system("pause");
				break;
			case 3:
				system("cls");
				//cout << "1. Создание пользователя " << endl
				//	 << "2. Удаление пользователя " << endl
				//	 << "3. Просмотр всех пользователей" << endl
				//	 << "4. Выход " << endl;
				//i = spos::check_int(i, 4);
				tab.metod();
				break;
			case 4:
				system("cls");
				system("pause");
				break;
			case 5:
				system("cls");
				return false;
				break;
			}
		}
	}
	void registration() {
		ofstream fin("user.txt", iostream::app);
		if (!fin.is_open()) {
		//	cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
		}
		else {
		//	cout << "успешное открытие файла!" << endl;

			system("cls");
			cout << "Введите логин: ";  cin >> login;
			cout << "Введите пороль: "; cin >> password;
			password = spos::shifr(password);
			fin << login << endl;
			fin << password << endl;

		}
		fin.close();
	}
};
ostream& operator<<(ostream& stream, User obj) {
	stream << obj.login << "  " << obj.password << endl;
	return stream;
}
bool operator==(User a, string s) {
	return (a.login) == s;
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 1);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}
	struct sockaddr_in addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1111);//1280
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");     
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	Admin admin;
	cout << "Продолжить работу на сервере?(y/n)" << endl;
	char s; cin >> s;
	if (s=='y')
		if (admin.authorization() == 5) {
			if (admin.second_menu() == 0)
				s = 'n';
		}
	if (s == 'n') {
		listen(sListen, SOMAXCONN);
		SOCKET newConnection;
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		User user;
		timetable tab;
		staff st;
		univer un;
		int ch = -1;
		char c;
		char c_msg[40];
		char login[200] = { 0 }, passw[200] = { 0 };
		if (newConnection == 0) {
			cout << "Error" << endl;
		}
		else {
			cout << "Client connected!\n";
			while (true) {
				recv(newConnection, &c, sizeof(c), NULL);

				if (c == '1') {
					recv(newConnection, login, sizeof(login), NULL);
					recv(newConnection, passw, sizeof(passw), NULL);
					user.registration();
				}
				if (c == '2') {
					char clen_log[2] = { 0 }, clen_pas[2] = { 0 };
					recv(newConnection, clen_log, sizeof(clen_log), NULL);
					int len_log = atoi(clen_log);
					cout << "amount of login elements: " << len_log << endl;

					recv(newConnection, clen_pas, sizeof(clen_pas), NULL);
					int len_pas = atoi(clen_pas);
					cout << "amount of password elements: " << len_pas << endl;

					recv(newConnection, login, len_log, NULL);
					recv(newConnection, passw, len_pas, NULL);

					cout << login << "  " << passw << endl;
					if (user.authorization(login, passw) == 1) {
						c = '1';
						send(newConnection, &c, sizeof(c), NULL);
						while (true) {
							recv(newConnection, &c, sizeof(c), NULL);
							if (c == '1') {
								string name, subject, exp;
								ifstream f("staff.txt");
								if (!f.is_open()) {
									cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
								}
								else {
									cout << "успешное открытие файла!" << endl;
									char a[255] = {}, b[255] = {}, d[255] = {};

									int m = st.getMount();
									char M[2]; itoa(m, M, 10);
									send(newConnection, M, sizeof(M), NULL);
									while (getline(f, name) && getline(f, subject) && getline(f, exp))
									{
										strcpy(a, name.c_str());
										strcpy(b, subject.c_str());
										strcpy(d, exp.c_str());
										char z1[2], z2[2], z3[2];
										itoa(strlen(a), z1, 10);
										itoa(strlen(b), z2, 10);
										itoa(strlen(d), z3, 10);

										send(newConnection, z1, sizeof(z1), NULL);
										send(newConnection, z2, sizeof(z2), NULL);
										send(newConnection, z3, sizeof(z3), NULL);
										send(newConnection, a, strlen(a), NULL);
										send(newConnection, b, strlen(b), NULL);
										send(newConnection, d, strlen(d), NULL);
									}
								}
								f.close();
							}
							else if (c == '2') {
								string sub, dat;
								int size = 0; char csize[2] = {};
								ifstream ff("timetable.txt");
								while (getline(ff, sub) && getline(ff, dat)) {
									size++;
								}
								ff.close();
								itoa(size, csize, 10);
								send(newConnection, csize, sizeof(csize), NULL);
								ifstream f("timetable.txt");
								while (getline(f, sub) && getline(f, dat)) {
									int i1, i2;
									i1 = sub.length();
									i2 = dat.length();
									char* s = {}, * d = {}; s = new char[i1]; d = new char[i2];
									strcpy(s, sub.c_str());
									strcpy(d, dat.c_str());
									char ci1[2], ci2[2];
									itoa(i1, ci1, 10);
									itoa(i2, ci2, 10);
									send(newConnection, ci1, sizeof(ci1), NULL);
									send(newConnection, ci2, sizeof(ci2), NULL);
									send(newConnection, s, strlen(s), NULL);
									send(newConnection, d, strlen(d), NULL);
								}
							}
							else if (c == '3') {

								string nam, em, gr;
								ifstream f("student.txt");
								if (!f.is_open()) {
									cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
								}
								else {
									cout << "успешное открытие файла!" << endl;
									char a[255] = {}, b[255] = {}, d[255] = {};

									int m = st.getMount();
									char M[2]; itoa(m, M, 10);
									send(newConnection, M, sizeof(M), NULL);
									while (getline(f, nam) && getline(f, em) && getline(f, gr))
									{
										strcpy(a, nam.c_str());
										strcpy(b, em.c_str());
										strcpy(d, gr.c_str());
										char z1[2], z2[2], z3[2];
										itoa(strlen(a), z1, 10);
										itoa(strlen(b), z2, 10);
										itoa(strlen(d), z3, 10);

										send(newConnection, z1, sizeof(z1), NULL);
										send(newConnection, z2, sizeof(z2), NULL);
										send(newConnection, z3, sizeof(z3), NULL);
										send(newConnection, a, strlen(a), NULL);
										send(newConnection, b, strlen(b), NULL);
										send(newConnection, d, strlen(d), NULL);
									}
								}
								f.close();

							}
							else if (c == '4') {
								string name, adress, contacts, time;
								ifstream f("univer.txt");
								if (!f.is_open()) {
									cout << "Файл не найден. Будет создан файл с указанным именем" << endl;
								}
								else {
									cout << "успешное открытие файла!" << endl;
									char a[255] = {}, b[255] = {}, d[255] = {}, e[255] = {};

									int m = un.getAmount();
									char M[2]; itoa(m, M, 10);
									send(newConnection, M, sizeof(M), NULL);
									while (getline(f, name) && getline(f, adress) && getline(f, contacts) && getline(f, time))
									{
										strcpy(a, name.c_str());
										strcpy(b, adress.c_str());
										strcpy(d, contacts.c_str());
										strcpy(e, time.c_str());
										char z1[2], z2[2], z3[2], z4[2];
										itoa(strlen(a), z1, 10);
										itoa(strlen(b), z2, 10);
										itoa(strlen(d), z3, 10);
										itoa(strlen(e), z4, 10);
										send(newConnection, z1, sizeof(z1), NULL);
										send(newConnection, z2, sizeof(z2), NULL);
										send(newConnection, z3, sizeof(z3), NULL);
										send(newConnection, z4, sizeof(z3), NULL);
										send(newConnection, a, strlen(a), NULL);
										send(newConnection, b, strlen(b), NULL);
										send(newConnection, d, strlen(d), NULL);
										send(newConnection, e, strlen(e), NULL);
									}
								}
								f.close();
							}
							else if (c == '5') break;
						}
					}
					else cout << "Неправильный логин или пароль!" << endl;
				}
				if (c == '3') {
					break;
				}
			}
		}
	//	send(newConnection, c_msg, sizeof(c_msg), NULL);
		closesocket(newConnection);
		closesocket(sListen);
		WSACleanup();
		system("pause");
		return 0;
	}
}
