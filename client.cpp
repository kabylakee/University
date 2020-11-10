#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <strstream>
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
int main()
{
	setlocale(LC_ALL, "Russian");
	char* login, * passw;
	char ch = '2';
	while (true) {

		cout << "Hello user of our service!" << endl;

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

		SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);


		if (connect(Connection, (sockaddr*)&addr, sizeof(addr)) != 0) {
			cout << "Error:failed connect to server" << endl;
			return 1;
		}
		cout << "Connected!!!";
		char choise = '0';
		char msg[40];


		while (true) {
			cout << "Выберите действие:" << endl <<
				"1.Регистрация" << endl <<
				"2.Вход пользователя" << endl <<
				"3.Выход" << endl;
			cin >> choise;

			send(Connection, &choise, sizeof(choise), NULL);
			if (choise == '1') {
				cout << "Введите логин и пароль:" << endl;
				string s_login, s_passw;
				cout << "Login:" << endl; cin >> s_login; int len_log = s_login.length(); cout << "kol-vo elementov logina: " << len_log << endl;
				cout << "Password:" << endl; cin >> s_passw; int len_pas = s_passw.length(); cout << "kol-vo elementov parolia: " << len_pas << endl;
				login = new char[len_log];
				passw = new char[len_pas];
				strcpy(login, s_login.c_str());
				strcpy(passw, s_passw.c_str());
				send(Connection, login, strlen(login), NULL);
				send(Connection, passw, strlen(passw), NULL);

				recv(Connection, &ch, sizeof(ch), NULL);
				if (ch == 1) cout << "Регистрация прошла успешно!" << endl;
				else  cout << "Ошибка регистрации!" << endl;

			}
			if (choise == '2') {
				cout << "Введите логин и пароль:" << endl;
				string s_login, s_passw;
				cout << "Login:" << endl; cin >> s_login; int len_log = s_login.length(); cout << "kol-vo elementov logina: " << len_log << endl;
				cout << "Password:" << endl; cin >> s_passw; int len_pas = s_passw.length(); cout << "kol-vo elementov parolia: " << len_pas << endl;
				char clen_log[2]; itoa(len_log, clen_log, 10);
				char clen_pas[2]; itoa(len_pas, clen_pas, 10);
				send(Connection, clen_log, sizeof(clen_log), NULL);
				send(Connection, clen_pas, sizeof(clen_pas), NULL);
				login = new char[len_log];
				passw = new char[len_pas];
				strcpy(login, s_login.c_str());
				strcpy(passw, s_passw.c_str());
				send(Connection, login, strlen(login), NULL);
				send(Connection, passw, strlen(passw), NULL);

				recv(Connection, &ch, sizeof(ch), NULL);
				if (ch == '1') {
					while (true) {
						cout << "Меню:" << endl
							<< "1. Информация о печатном издательстве." << endl
							<< "2. Заказ" << endl
							<< "3. Выход." << endl;
						cin >> choise;
						send(Connection, &choise, sizeof(choise), NULL);
						if (choise == '1') {
							char m;
							recv(Connection, &m, sizeof(m), NULL);
							int k1 = atoi(&m);
							recv(Connection, &m, sizeof(m), NULL);
							int k2 = atoi(&m);
							recv(Connection, &m, sizeof(m), NULL);
							int k3 = atoi(&m);
							char* m1, * m2, * m3;
							m1 = new char[k1]; m2 = new char[k2]; m3 = new char[k3];
							cout << "Название: ";
							recv(Connection, m1, k1, NULL);
							string s1 = m1;
							cout << s1 << endl;
							cout << "Адрес: ";
							recv(Connection, m2, k2, NULL);
							cout << m2 << endl;
							cout << "Контакты: ";
							recv(Connection, m3, k3, NULL);
							cout << m3 << endl;
						}
						if (choise == '2') {

							char R2[3];
							cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
							cout << setw(25) << "Занимаемая должность |" << setw(30) << "Не работал в этой сфере |" << setw(30) << "Работал в этой сфере |" << setw(32) << "Постоянно работаю в этой сфере |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl <<
								setw(25) << "Художник |" << setw(30) << "1 |" << setw(30) << "- |" << setw(32) << "- |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl <<
								setw(25) << "Маркетолог |" << setw(30) << "3 |" << setw(30) << "4 |" << setw(32) << "5 |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl <<
								setw(25) << "Креатив. директор |" << setw(30) << "5 |" << setw(30) << "7 |" << setw(32) << "10 |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl;
							//while (true) {
							cout << "Введите значение,находящееся на перекрестии: ";
							cin >> R2;
							//if (R2 == "1" || R2 == "3" || R2 == "4" || R2 == "5" || R2 == "7" || R2 == "10") {

							send(Connection, R2, sizeof(R2), NULL);
							//break;
						//}
					//}
							cout << endl << "---------------------------------------------------------------------------------------------------------------------" << endl;
							cout << setw(52) << "Источники аргументаций |" << setw(65) << "Степень влияния источника на ваше мнение |" << endl <<
								setw(52) << " |" << "-----------------------------------------------------------------" << endl <<
								setw(52) << " |" << setw(22) << "высокая |" << setw(21) << "средняя |" << setw(22) << "низкая |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl <<
								setw(52) << "Проведенный вами теоретический анализ |" << setw(22) << "0.3 |" << setw(21) << "0.2 |" << setw(22) << "0.1 |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl <<
								setw(52) << "Ваш производственный опыт |" << setw(22) << "0.5 |" << setw(21) << "0.4 |" << setw(22) << "0.2 |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl <<
								setw(52) << "Обобщение работ зарубежных авторов |" << setw(22) << "0.05 |" << setw(21) << "0.05 |" << setw(22) << "0.05 |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl <<
								setw(52) << "Ваше личное знакомство с состояниемдел за рубежом |" << setw(22) << "0.05 |" << setw(21) << "0.05 |" << setw(22) << "0.05 |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl <<
								setw(52) << "Ваша интуиция |" << setw(22) << "0.05 |" << setw(21) << "0.05 |" << setw(22) << "0.05 |" << endl <<
								"---------------------------------------------------------------------------------------------------------------------" << endl;

							char r1[4], r2[4];
							cout << "Введите оценки по критериям: " << endl <<
								"Проведенный вами теоретический анализ: ";
							//while (true) {
							cin >> r1;
							//	if (r1 == "0.3" || r1 == "0.2" || r1 == "0.1") {
							send(Connection, r1, sizeof(r1), NULL);
							//break;
					//	}
					//}
							cout << endl << "Ваш производственный опыт: ";
							//while (true) {
							cin >> r2;
							//	if (r2 == "0.5" || r2 == "0.4" || r2 == "0.2")
							//	{	
							send(Connection, r2, sizeof(r2), NULL);
							//break;
					//	}
					//}
							char o1[4], o2[4], o3[4];
							cout << "Выставьте ваши оценки важности критериев от 0 до 1!" << endl;
							cout << "Стоимость: "; cin >> o1; //o1 *= 0.1;
							cout << "Размер (от А6  до А1): ";  cin >> o2; //o2 *= 0.1;
							cout << "Насыщенность цвета краски: "; cin >> o3;// o3 *= 0.1;

							char sr2[5];

							//itoa(o1, sr2, 10);
							send(Connection, o1, sizeof(o1), NULL);
							//itoa(o2, sr2, 10);
							send(Connection, o2, sizeof(o2), NULL);
							//itoa(o3, sr2, 10);
							send(Connection, o3, sizeof(o3), NULL);
							char ch;
							recv(Connection, &ch, sizeof(ch), NULL);
							cout << "Наиболее подходящий вариант книги для вас:" << endl; cout << ch << endl;
							if (ch == '1') {
								cout << "1.Книга не большого размера (А5-А6) в мягком переплете со средней плотностью бумаги и низкой насыщенностью цвета краски." << endl;
							}
							if (ch == '2') {
								cout << "1.Книга размера А4 в мягком или твердом переплете со средней плотностью бумаги и средней насыщенностью цвета краски." << endl;
							}
							if (ch == '3') {
								cout << "1.Книга размера (А5-А6) в мягком переплете со средней плотностью бумаги и насыщенностыми картинками и четким текстом." << endl;
							}
							system("pause");
						}
						if (choise == '3') { break; }
					}
				}
				else cout << "Неправильный логин или пароль!" << endl;
			}

			if (choise == '3') {
				return 0;
			}

		}
		//send(Connection, &choise, sizeof(choise), NULL);
		//recv(Connection, msg, sizeof(msg), NULL);
		//cout << msg << endl;
		/*
		string s_login, s_passw;
		cout << "Login:" << endl; cin >> s_login; int len_log = s_login.length(); cout << "kol-vo elementov logina: " << len_log << endl;
		cout << "Password:" << endl; cin >> s_passw; int len_pas =s_passw.length(); cout << "kol-vo elementov parolia: " << len_pas << endl;
		char clen_log[2]; itoa(len_log, clen_log,10);
		char clen_pas[2]; itoa(len_pas, clen_pas, 10);
		login = new char[len_log];
		passw = new char[len_pas];
		strcpy(login, s_login.c_str());
		strcpy(passw, s_passw.c_str());
		send(Connection, &ch, sizeof(ch), NULL);
		send(Connection, clen_log, sizeof(clen_log), NULL);
		send(Connection, clen_pas, sizeof(clen_pas), NULL);
		send(Connection, login, strlen(login), NULL);
		send(Connection, passw, strlen(passw), NULL);
		recv(Connection, &ch, sizeof(ch), NULL);
		cout << "Answer is " << ch << endl;
		*/
		closesocket(Connection);
		WSACleanup();
		system("pause");
		return 0;
	
	}
}
???