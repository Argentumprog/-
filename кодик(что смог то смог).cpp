#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void GoTo(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

static int hereworker = 0;

struct project
{
	string FIO;
	string work;
	int cost;
	int hours;

}person, ad;

struct Workers
{
	string FIO;
	string passw;
	int access;

	void Checkaccount(Workers& worker, int herework)
	{
		if (worker.FIO == FIO && worker.passw == passw) { worker.access = access; hereworker = herework; }
	}
}worker, add;

static vector <Workers> listworkers;
static vector <project> listofproj;
static vector <int> poisk;


bool checkalf(string st1, string st2) {
	bool first = true;
	int i = -1;

	do {
		i++;
		if (i >= size(st1) - 1 || i >= size(st2) - 1) { return first; }
		if (st1[i] > st2[i]) { first = false; }
	} while (st1[i] == st2[i]);

	return first;
}
void swapinpr(project* p1, project* p2) {
	project p;
	p.FIO = (*p1).FIO;
	p.work = (*p1).work;
	p.cost = (*p1).cost;
	p.hours = (*p1).hours;
	(*p1).FIO = (*p2).FIO;
	(*p1).work = (*p2).work;
	(*p1).cost = (*p2).cost;
	(*p1).hours = (*p2).hours;
	(*p2).FIO = p.FIO;
	(*p2).work = p.work;
	(*p2).cost = p.cost;
	(*p2).hours = p.hours;
}
void showpoisk() {
	system("CLS");
	GoTo(0, 2);
	for (int k = 0;k < 119;k++) { cout << "-"; }
	GoTo(0, 3);
	cout << "|ФИО:";
	GoTo(49, 3);
	cout << "|Вид работы:";
	GoTo(79, 3);
	cout << "|Почасовая стоимость:";
	GoTo(100, 3);
	cout << "|Количество часов:|";
	GoTo(0, 4);
	for (int k = 0;k < 119;k++) { cout << "-"; }
	for (int k = 0;k < size(poisk);k++) {
		GoTo(0, 5 + k * 2);
		cout << "|" << listofproj[poisk[k]].FIO;
		GoTo(49, 5 + k * 2);
		cout << "|" << listofproj[poisk[k]].work;
		GoTo(79, 5 + k * 2);
		cout << "|" << listofproj[poisk[k]].cost;
		GoTo(100, 5 + k * 2);
		cout << "|" << listofproj[poisk[k]].hours;
		GoTo(118, 5 + k * 2);
		cout << "|";
		GoTo(0, 6 + k * 2);
		for (int k = 0;k < 119;k++) { cout << "-"; }
	}
}
void showtotal() {
	system("CLS");
	GoTo(0, 2);
	for (int k = 0;k < 119;k++) { cout << "-"; }
	GoTo(0, 3);
	cout << "|ФИО:";
	GoTo(49, 3);
	cout << "|Вид работы:";
	GoTo(79, 3);
	cout << "|Почасовая стоимость:";
	GoTo(100, 3);
	cout << "|Количество часов:|";
	GoTo(0, 4);
	int kon = 0, total = 0;
	for (int k = 0;k < 119;k++) { cout << "-"; }
	for (int k = 0;k < size(listofproj);k++, kon++) {
		GoTo(0, 5 + k * 2);
		cout << "|" << listofproj[k].FIO;
		GoTo(49, 5 + k * 2);
		cout << "|" << listofproj[k].work;
		GoTo(79, 5 + k * 2);
		cout << "|" << listofproj[k].cost;
		GoTo(100, 5 + k * 2);
		cout << "|" << listofproj[k].hours;
		GoTo(118, 5 + k * 2);
		cout << "|";
		GoTo(0, 6 + k * 2);
		for (int k = 0;k < 119;k++) { cout << "-"; }
		total = total + listofproj[k].cost * listofproj[k].hours;
	}
	GoTo(0, 5 + kon * 2);
	cout << "|" << "Итоговая стоимость проекта: " << total;
	GoTo(118, 5 + kon * 2);
	cout << "|";
	GoTo(0, 6 + kon * 2);
	for (int k = 0;k < 119;k++) { cout << "-"; }
}
void changepassw() {
	string passw, passw1;
	system("CLS");
	cout << "Смена пароля.Подтвердите предыдущий пароль ещё раз:" << endl;
	cin >> passw;
	if (worker.passw == passw) {
		cout << "Введите новый пароль:" << endl;
		cin >> passw;
		cout << "Подтвердите новый пароль:" << endl;
		cin >> passw1;
		if (passw == passw1) {
			worker.passw = passw;
			listworkers[hereworker].passw = passw;
			cout << "Пароль успешно изменён!" << endl;
		}
		else cout << "Пароли не совпали! Попробуйте ещё раз." << endl;
	}
	else cout << "Введён неправильный пароль!" << endl;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char choice = '1';	
	string f, i, o, namef, way = "___";
	bool opened = false;
	char chois = '0';

	ifstream fin;
	fin.open("workers.txt");
	if (!fin.is_open()) {
		std::cout << "Нет файла с работникими!";
	}
	else while (!fin.eof())
	{
		getline(fin, worker.FIO);
		fin >> worker.passw;
		fin >> worker.access;
		fin.get();
		if (fin.eof()) { break; }
		listworkers.push_back(worker);
	}
	fin.close();
	worker.access = 0;

	while (worker.access == 0) {
		system("CLS");
		cout << "Введите ФИО и пароль:" << endl;
		
		cin >> f >> i >> o >> worker.passw;
		worker.FIO = f + " " + i + " " + o;
		worker.access = 0;

		for (int k = 0; k < size(listworkers); k++) {
			listworkers[k].Checkaccount(worker,k);
		}
		if (worker.access == 0) {
			cout << "Неправильное ФИО или пароль.\nВы можете повторить попытку или выти из приложения."<< endl;
			system("pause");
		}
	}

	do {
		if (worker.access != 0) {
			system("CLS");
			cout << "Введите название проекта" << endl;
			cin >> namef;
			way = namef + ".txt";

			ifstream fin;
			fin.open(way);

			if (!fin.is_open()) {
				cout << "Нет проекта с данным названием!\nВы можете повторить попытку или выти из приложения." << endl;
				system("pause");
			}
			else {
				opened = true;
				while (!fin.eof())
				{
					getline(fin, person.FIO);
					getline(fin, person.work);
					fin >> person.cost;
					fin >> person.hours;
					fin.get();
					if (fin.eof()) { break; }
					listofproj.push_back(person);
				}
				fin.close();
			}
		}
	} while (!opened);	
	system("CLS");

	if (worker.access == 1 && opened) {
		while (choice != '0') {

			cout << endl << "Выберите действие:" << endl << "1.Отсортировать" << endl << "2.Добавить новый аккаунт" << endl << "3.Изменить аккаунт" << endl << "4.Удалить аккаунт" << endl << "5.Поиск" << endl << "6. Изменить свой пароль" << endl << "0.Закончить работу" << endl;
			cin >> choice;
			switch (choice) {
			case '1':
			{
				chois = '0';
				cout << "Выберите подходящий вариант сортировки:" << endl << "1. По алфавиту" << endl << "2. По названию работы" << endl << "3. По количеству часов" << endl << "4. По стоимости одного часа" << endl;
				cin >> chois;
				switch (chois) {
				case '1':
				{
					for (int k = 0;k < size(listofproj);k++) {
						for (int j = 0;j < size(listofproj) - 1;j++) {
							if (checkalf(listofproj[j + 1].FIO, listofproj[j].FIO)) {
								swapinpr(&listofproj[j], &listofproj[j + 1]);
							}

						}
					}

					break;
				}
				case '2':
				{
					for (int k = 0;k < size(listofproj);k++) {
						for (int j = 0;j < size(listofproj) - 1;j++) {
							if (checkalf(listofproj[j + 1].work, listofproj[j].work)) {
								swapinpr(&listofproj[j], &listofproj[j + 1]);
							}

						}
					}

					break;
				}
				case '3':
				{
					for (int k = 0;k < size(listofproj);k++) {
						for (int j = 0;j < size(listofproj) - 1;j++) {
							if (listofproj[j].hours < listofproj[j + 1].hours) {
								swapinpr(&listofproj[j], &listofproj[j + 1]);
							}

						}
					}
					break;
				}
				case '4':
				{
					for (int k = 0;k < size(listofproj);k++) {
						for (int j = 0;j < size(listofproj) - 1;j++) {
							if (listofproj[j].cost < listofproj[j + 1].cost) {
								swapinpr(&listofproj[j], &listofproj[j + 1]);
							}

						}
					}
					break;
				}
				default:
				{
					cout << "Неправильная цифра!" << endl;
					break;
				}
				}
				break;
			}
			case '2':
			{
				chois = '0';
				cout << "Выберите подходящий вариант:" << endl << "1. Создать аккаунт и добавить в проект" << endl << "2. Создать аккаунт" << endl << "3. Добавить аккаунт в проект" << endl;
				cin >> chois;
				switch (chois) {
				case '1':
				{
					cout << "Введите ФИО сотрудника:" << endl;
					cin >> f >> i >> o;
					string fio = f + " " + i + " " + o;
					for (int k = 0;k < size(listworkers);k++) {
						if (fio == listworkers[k].FIO) {
							cout << "Человек с этим ФИО уже зарегистрирован!" << endl;
							system("pause");
							break;
						}
					}
					for (int k = 0;k < size(listofproj);k++) {
						if (fio == listofproj[k].FIO) {
							cout << "Человек с этим ФИО уже зарегистрирован в проекте!" << endl;
							system("pause");
							break;
						}
					}
					add.FIO = f + " " + i + " " + o;
					ad.FIO = add.FIO;
					cout << "Введите пароль к его аккаунту:" << endl;
					cin >> add.passw;
					cout << "Введите его статус:" << endl << "1.Администратор" << endl << "2.Пользователь" << endl;
					cin >> add.access;
					cout << "Введите название его деятельности(вид работы):" << endl;
					cin.ignore();
					getline(cin, ad.work);
					cout << "Введите количество часов его работы:" << endl;
					cin >> ad.cost;
					cout << "Введите стоимость одного часа данного сотрудника:" << endl;
					cin >> ad.hours;
					listworkers.push_back(add);
					listofproj.push_back(ad);
					break;
				}
				case '2':
				{
					cout << "Введите ФИО сотрудника:" << endl;
					cin >> f >> i >> o;
					string fio = f + " " + i + " " + o;
					for (int k = 0;k < size(listworkers);k++) {
						if (fio == listworkers[k].FIO) {
							cout << "Человек с этим ФИО уже зарегистрирован!" << endl;
							system("pause");
							break;
						}
					}
					add.FIO = f + " " + i + " " + o;
					cout << "Введите пароль к его аккаунту:" << endl;
					cin >> add.passw;
					cout << "Введите его статус:" << endl << "1.Администратор" << endl << "2.Пользователь" << endl;
					cin >> add.access;
					listworkers.push_back(add);
					break;
				}
				case '3':
				{
					cout << "Введите ФИО сотрудника:" << endl;
					cin >> f >> i >> o;
					string fio = f + " " + i + " " + o;
					for (int k = 0;k < size(listofproj);k++) {
						if (fio == listofproj[k].FIO) {
							cout << "Человек с этим ФИО уже зарегистрирован в проекте!" << endl;
							system("pause");
							break;
						}
					}
					bool exist = false;
					for (int k = 0;k < size(listworkers);k++) {
						if (fio == listworkers[k].FIO) {
							exist = true;
						}
					}
					if (!exist) {
						cout << "Данный пользователь не зарегистрирован!" << endl;
						system("pause");
						break;
					}
					ad.FIO = fio;
					cout << "Введите название его деятельности(вид работы):" << endl;
					cin.ignore();
					getline(cin, ad.work);
					cout << "Введите количество часов его работы:" << endl;
					cin >> ad.cost;
					cout << "Введите стоимость одного часа данного сотрудника:" << endl;
					cin >> ad.hours;
					listofproj.push_back(ad);
					break;
				}
				default:
				{
					cout << "Неправильная цифра!" << endl;
					break;
				}
				}
				break;
			}
			case '3':
			{
				cout << "Введите ФИО сотрудника:" << endl;
				cin >> f >> i >> o;
				string fio = f + " " + i + " " + o;
				bool exist = false;
				for (int k = 0;k < size(listworkers);k++) {
					if (fio == listworkers[k].FIO) {
						exist = true;
						break;
					}
				}
				if (!exist) {
					cout << "Данный пользователь не зарегистрирован!" << endl;
					system("pause");
					break;
				}
				exist = false;
				for (int k = 0;k < size(listofproj);k++) {
					if (fio == listofproj[k].FIO) {
						exist = true;
						break;
					}
				}
				if (!exist) {
					int p1 = -1;
					for (int k = 0;k < size(listworkers);k++) {
						if (fio == listworkers[k].FIO) { p1 = k; break; }
					}
					chois = '0';
					while (chois != '3') {
						cout << "Выберите, что желаете изменить:" << endl << "1. ФИО" << endl << "2. Статус сотрудника" << endl << "3.Все изменения завершены" << endl;
						cin >> chois;
						switch (chois) {
						case '1':
						{
							cout << "Введите новое ФИО сотрудника:" << endl;
							cin >> f >> i >> o;
							listworkers[p1].FIO = f + " " + i + " " + o;
							break;
						}
						case '2':
						{
							cout << "Введите его новый статус:" << endl << "1.Администратор" << endl << "2.Пользователь" << endl;
							cin >> listworkers[p1].access;
							break;
						}
						case '3':
						{
							break;
						}

						default:
						{
							cout << "Неправильная цифра!" << endl;
							break;
						}
						}
					}
					break;
				}
				else {
					int p1 = -1, p2 = -1;
					for (int k = 0;k < size(listworkers);k++) {
						if (fio == listworkers[k].FIO) { p1 = k; break; }
					}
					for (int k = 0;k < size(listofproj);k++) {
						if (fio == listofproj[k].FIO) { p2 = k; break; }
					}
					char chois = 0;
					if (p1 == -1 || p2 == -1) {
						cout << "Данный сотрудник не добавлен в базу данных!" << endl;
						break;
					}
					while (chois != '6') {
						cout << "Выберите, что желаете изменить:" << endl << "1. ФИО" << endl << "2. Статус сотрудника" << endl << "3.Название деятельности работника" << endl << "4. Количество часов работы сотрудника" << endl << "5. Стоимость одного часа его работы" << endl << "6.Все изменения завершены" << endl;
						cin >> chois;
						switch (chois) {
						case '1':
						{for (int k = 0;k < size(listworkers);k++) {
							if (fio == listworkers[k].FIO) { p1 = k; break; }
						}
						for (int k = 0;k < size(listofproj);k++) {
							if (fio == listofproj[k].FIO) { p2 = k; break; }
						}
						cout << "Введите новое ФИО сотрудника:" << endl;
						cin >> f >> i >> o;
						listofproj[p2].FIO = f + " " + i + " " + o;
						listworkers[p1].FIO = listofproj[p2].FIO;
						break;
						}
						case '2':
						{
							cout << "Введите его новый статус:" << endl << "1.Администратор" << endl << "2.Пользователь" << endl;
							cin >> listworkers[p1].access;
							break;
						}
						case '3':
						{
							cout << "Введите название его деятельности(вид работы):" << endl;
							cin >> listofproj[p2].work;
							break;
						}
						case '4':
						{
							cout << "Введите количество часов его работы:" << endl;
							cin >> listofproj[p2].hours;
							break;
						}
						case '5':
						{
							cout << "Введите стоимость одного часа данного сотрудника:" << endl;
							cin >> listofproj[p2].cost;
							break;
						}
						case '6':
						{
							break;
						}
						default:
						{
							cout << "Неправильная цифра!" << endl;
							break;
						}
						}
					}
					break;
				}
			}
			case '4':
			{
				cout << "Введите ФИО сотрудника:" << endl;
				cin >> f >> i >> o;
				string fio = f + " " + i + " " + o;
				int p1 = -1, p2 = -1;
				for (int k = 0;k < size(listworkers);k++) {
					if (fio == listworkers[k].FIO) { p1 = k; break; }
				}
				for (int k = 0;k < size(listofproj);k++) {
					if (fio == listofproj[k].FIO) { p2 = k; break; }
				}
				chois = '0';
				cout << "Выберите подходящий вариант:" << endl << "1. Удалить только из проекта" << endl << "2. Удалить всё об аккаунте и в проекте" << endl;
				cin >> chois;
				switch (chois) {
				case '1':
				{
					if (p2 == -1) {
						cout << "Нет данных о человеке с данным ФИО для удаления" << endl;
						system("pause");
						break;
					}
					else { listofproj.erase(listofproj.begin() + p2); }
					break;
				}
				case '2':
				{
					if (p1 == -1) {
						cout << "Нет аккаунта с таким ФИО в проекте" << endl;
						system("pause");
						break;
					}
					else {
						listworkers.erase(listworkers.begin() + p1);

						if (p2 == -1) {
							cout << "Нет данных о человеке с данным ФИО в проекте для удаления, поэтому произошло удаление только аккаунта" << endl;
							system("pause");
							break;
						}
						else { listofproj.erase(listofproj.begin() + p2); }
					}
					break;
				}
				default:
				{
					cout << "Неправильная цифра!" << endl;
					break;
				}
				}
				break;
			}
			case '5':
			{
				chois = '0';
				cout << "Выберите подходящий вариант поиска:" << endl << "1. По имени" << endl << "2. По названию работы" << endl << "3. По количеству часов" << endl << "4. По стоимости одного час" << endl;
				cin >> chois;
				switch (chois) {
				case '1':
				{
					string fio;
					int place = -1, k;
					poisk.clear();
					cout << "Введите корректное ФИО" << endl;
					cin >> f >> i >> o;
					fio = f + " " + i + " " + o;

					for (k = 0;k < size(listofproj);k++) {
						if (listofproj[k].FIO == fio) {
							place = k;
							poisk.push_back(k);
						}
					}

					if (place == -1) {
						cout << "Неверное ФИО" << endl;
					}
					else {
						showpoisk();
					}
					cout << endl;
					system("pause");

					break;
				}
				case '2':
				{
					string work;
					int place = -1, k;
					poisk.clear();
					cout << "Введите корректное название деятельности сотрудника" << endl;
					cin.ignore();
					getline(cin, work);

					for (k = 0;k < size(listofproj);k++) {
						if (listofproj[k].work == work) {
							place = k;
							poisk.push_back(k);
						}
					}

					if (place == -1) {
						cout << "Нет таких данных" << endl;
					}
					else {
						showpoisk();
						}
					cout << endl;
					system("pause");

					break;
				}
				case '3':
				{

					int place = -1, k, time;
					poisk.clear();
					cout << "Введите корректное количество часов сотрудника" << endl;
					cin >> time;

					for (k = 0;k < size(listofproj);k++) {
						if (listofproj[k].hours == time) {
							place = k;
							poisk.push_back(k);
						}
					}

					if (place == -1) {
						cout << "Нет таких данных" << endl;
					}
					else {
						showpoisk();
						}
					cout << endl;
					system("pause");

					break;
				}
				case '4':
				{

					int place = -1, k, cost;
					poisk.clear();
					cout << "Введите корректную стоимость одного часа сотрудника" << endl;
					cin >> cost;

					for (k = 0;k < size(listofproj);k++) {
						if (listofproj[k].cost == cost) {
							place = k;
							poisk.push_back(k);
						}
					}

					if (place == -1) {
						cout << "Нет таких данных" << endl;
					}
					else {
						showpoisk();
						}
					cout << endl;
					system("pause");

					break;
				}
				default:
				{
					cout << "Неправильная цифра!" << endl;
					break;
				}
				}
				break;
			}
			case '6':
			{
				changepassw();
				system("pause");
			}
			default:
			{
				cout << "Неправильная цифра!" << endl;
				break;
			}
			}
			showtotal();
			ofstream fout;
			fout.open(way, ofstream::trunc);
			for (int k = 0;k < size(listofproj);k++)
			{
				fout << listofproj[k].FIO << endl;
				fout << listofproj[k].work << endl;
				fout << listofproj[k].cost << endl;
				fout << listofproj[k].hours << endl;
			}
			fout.close();

			ofstream fut;
			fut.open("workers.txt", ofstream::trunc);
			for (int k = 0;k < size(listworkers);k++)
			{
				fut << listworkers[k].FIO << endl;
				fut << listworkers[k].passw << endl;
				fut << listworkers[k].access << endl;
			}
			fut.close();
		}
	}

	if (worker.access == 2 && opened) {
		int hereinpr=-1;

		for (int k = 0;k < size(listofproj);k++) {
			if (worker.FIO == listofproj[k].FIO) {
				hereinpr = k;
				break;
			}
		}
		if (hereinpr == -1) {
			cout << "Вас нет в данном проекте." << endl;
		}

		while (choice != '0' && hereinpr != -1) {
			cout << endl << "Выберите действие:" << endl << "1.Узнать информацию о себе в проекте" << endl << "2. Изменить пароль" << endl;
			cin >> choice;
			switch (choice) {
			case '1':
			{
				system("CLS");
				GoTo(0, 2);
				for (int k = 0;k < 119;k++) { cout << "-"; }
				GoTo(0, 3);
				cout << "|ФИО:";
				GoTo(49, 3);
				cout << "|Вид работы:";
				GoTo(79, 3);
				cout << "|Почасовая стоимость:";
				GoTo(100, 3);
				cout << "|Количество часов:|";
				GoTo(0, 4);
				for (int k = 0;k < 119;k++) { cout << "-"; }
				GoTo(0, 5);
				cout << "|" << listofproj[hereinpr].FIO;
				GoTo(49, 5);
				cout << "|" << listofproj[hereinpr].work;
				GoTo(79, 5);
				cout << "|" << listofproj[hereinpr].cost;
				GoTo(100, 5);
				cout << "|" << listofproj[hereinpr].hours;
				GoTo(118, 5);
				cout << "|";
				GoTo(0, 6);
				for (int k = 0;k < 119;k++) { cout << "-"; }
				cout << endl;
				system("pause");
				break;
			}
			case '2':
			{
				changepassw();
				system("pause");
			}
			default:
			{
				cout << "Неправильная цифра!" << endl;
				break;
			}
			}
			ofstream fout;
			fout.open(way, ofstream::trunc);
			for (int k = 0;k < size(listofproj);k++)
			{
				fout << listofproj[k].FIO << endl;
				fout << listofproj[k].work << endl;
				fout << listofproj[k].cost << endl;
				fout << listofproj[k].hours << endl;
			}
			fout.close();

			ofstream fut;
			fut.open("workers.txt", ofstream::trunc);
			for (int k = 0;k < size(listworkers);k++)
			{
				fut << listworkers[k].FIO << endl;
				fut << listworkers[k].passw << endl;
				fut << listworkers[k].access << endl;
			}
			fut.close();

		}
	}
}