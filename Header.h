#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void GoTo(short x, short y);

static string alfrusanden = "- àáâãäå¸æùèéêëìíîïğñòóôõö÷øùúûüışÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static int hereworker = 0;

struct project
{
	string FIO;
	string work;
	float cost;
	int hours;

};

struct Workers
{
	string FIO;
	string passw;
	int access;

	void Checkaccount(Workers& worker, int herework)
	{
		if (worker.FIO == FIO && worker.passw == passw) { worker.access = access; hereworker = herework; }
	}
};

static vector <Workers> listworkers;
static vector <project> listofproj;
static vector <int> poisk;
static char choice = '1', chois = '0', contin = '1';
static string f, i, o, namef, way = "_";
static bool opened = false, nonumbers;
static Workers worker, add;
static project person, ad;

bool checkalf(string st1, string st2);
void swapinpr(project* p1, project* p2);
void showpoisk();
void showtotal();
void changepassw();
void logIn();
void chooseproj();
void menuAdmsort();
void menuAdmadd();
void menuAdmpoisk();
void menuAdm();
void menuUser();