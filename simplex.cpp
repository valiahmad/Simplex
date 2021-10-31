//simplex
/*
*
* Solving Simplex
* =============PROJECT============
* Copyright (c) vali ahmad rahmani
* Date Jul,12,2020
* name simplex
*
*/
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

int Lola_R = 0;                           //row of Lola
int Lola_C = 0;                           //column of Lola
int RHS = 0;                              //Right Hand Side
int First_Friend = 0;                     //The row that is up or down of Lola
int Second_Friend = 0;                    //The row that is up or down of Lola
#define Third_Friend 3                     //The row that is up or down of Lola
int First_Child_Friend = 0;               //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+All column except Lola column
int Second_Child_Friend = 0;              //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+All column except Lola column
int MAX = 0;                              //MAX Function 
int min = 0;                              //min Function
#define Limit 3                            //limit of fnction
int Variable = 0;
int _Limit = 0;

void setting(int MAX_min, int variable, int limit) {
	if (MAX_min == 1)MAX = 1;
	else min = 1;
	Variable = variable;
	_Limit = limit;
}
float iif(float rhs, float lo) {
	if (lo == 0)
		return 10000;
	else return rhs / lo;
}
float iff(float rhs, float lo) {
	if (lo == 0)
		return -10000;
	else return rhs / lo;
}
void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X = x;
	cursorCoord.Y = y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

class Simplex {//for MAx 3
	int j, i, temp;
	float lola, grid[4][4], limit[4][3];
	//RHS, First_Friend, Second_Frirnd, First_Child_Friend, Second_Child_Friend
	const int address00[5] = { 3,1,2,1,2 };
	const int address01[5] = { 3,1,2,0,2 };
	const int address02[5] = { 3,1,2,0,1 };
	const int address10[5] = { 3,0,2,1,2 };
	const int address11[5] = { 3,0,2,0,2 };
	const int address12[5] = { 3,0,2,0,1 };
	const int address20[5] = { 3,0,1,1,2 };
	const int address21[5] = { 3,0,1,0,2 };
	const int address22[5] = { 3,0,1,0,1 };
	//Simplex* simplex;
public:
	Simplex() {
		for (i = 0; i < 4; i++)//put in all elemnet 0 and in s1, s2 and s3 1
			for (j = 0; j < 4; j++) {
				grid[i][j] = 0;
				if (i < 4 && j < 3)
					limit[i][j] = 0;
			}
		set_limit();
	}
	void find_min_target() {
		temp = grid[3][0] <= grid[3][1] ? 0 : 1;
		if (Variable == 3) {
			if (temp)
				temp = grid[3][1] <= grid[3][2] ? 1 : 2;

			else temp = grid[3][0] <= grid[3][2] ? 0 : 2;
		}
		Lola_C = temp;
	}
	void find_MAX_target() {
		temp = grid[3][0] >= grid[3][1] ? 0 : 1;
		if (Variable == 3) {
			if (temp) {
				temp = grid[3][1] >= grid[3][2] ? 1 : 2;
			}
			else temp = grid[3][0] >= grid[3][2] ? 0 : 2;
		}
		Lola_C = temp;
	}
	void find_min_RHS() {
		temp = (iif(grid[0][3], grid[0][Lola_C])) <= (iif(grid[1][3], grid[1][Lola_C])) ? 0 : 1;
		if (_Limit == 3) {
			if (temp)
				temp = (iif(grid[1][3], grid[1][Lola_C])) <= (iif(grid[2][3], grid[2][Lola_C])) ? 1 : 2;

			else temp = (iif(grid[0][3], grid[0][Lola_C])) <= (iif(grid[2][3], grid[2][Lola_C])) ? 0 : 2;
		}
		Lola_R = temp;
	}
	void find_MAX_RHS() {
		temp = (iff(grid[0][3], grid[0][Lola_C])) >= (iff(grid[1][3], grid[1][Lola_C])) ? 0 : 1;
		if (_Limit == 3) {
			if (temp)
				temp = (iff(grid[1][3], grid[1][Lola_C])) >= (iff(grid[2][3], grid[2][Lola_C])) ? 1 : 2;

			else temp = (iff(grid[0][3], grid[0][Lola_C])) >= (iff(grid[2][3], grid[2][Lola_C])) ? 0 : 2;
		}
		Lola_R = temp;
	}
	void set_address() {
		find_lola();
		if (Lola_R == 0 && Lola_C == 0) {
			RHS = address00[0];
			First_Friend = address00[1];
			Second_Friend = address00[2];
			First_Child_Friend = address00[3];
			Second_Child_Friend = address00[4];
		}
		if (Lola_R == 0 && Lola_C == 1) {
			RHS = address01[0];
			First_Friend = address01[1];
			Second_Friend = address01[2];
			First_Child_Friend = address01[3];
			Second_Child_Friend = address01[4];
		}
		if (Lola_R == 0 && Lola_C == 2) {
			RHS = address02[0];
			First_Friend = address02[1];
			Second_Friend = address02[2];
			First_Child_Friend = address02[3];
			Second_Child_Friend = address02[4];
		}
		if (Lola_R == 1 && Lola_C == 0) {
			RHS = address10[0];
			First_Friend = address10[1];
			Second_Friend = address10[2];
			First_Child_Friend = address10[3];
			Second_Child_Friend = address10[4];
		}
		if (Lola_R == 1 && Lola_C == 1) {
			RHS = address11[0];
			First_Friend = address11[1];
			Second_Friend = address11[2];
			First_Child_Friend = address11[3];
			Second_Child_Friend = address11[4];
		}
		if (Lola_R == 1 && Lola_C == 2) {
			RHS = address12[0];
			First_Friend = address12[1];
			Second_Friend = address12[2];
			First_Child_Friend = address12[3];
			Second_Child_Friend = address12[4];
		}
		if (Lola_R == 2 && Lola_C == 0) {
			RHS = address20[0];
			First_Friend = address20[1];
			Second_Friend = address20[2];
			First_Child_Friend = address20[3];
			Second_Child_Friend = address20[4];
		}
		if (Lola_R == 2 && Lola_C == 1) {
			RHS = address21[0];
			First_Friend = address21[1];
			Second_Friend = address21[2];
			First_Child_Friend = address21[3];
			Second_Child_Friend = address21[4];
		}
		if (Lola_R == 2 && Lola_C == 2) {
			RHS = address22[0];
			First_Friend = address22[1];
			Second_Friend = address22[2];
			First_Child_Friend = address22[3];
			Second_Child_Friend = address22[4];
		}
	}
	void eval_limit() {
		for (j = 0; j < Limit; j++)
			limit[First_Friend][j] = -(grid[First_Friend][Lola_C] / lola) * limit[Lola_R][j] + limit[First_Friend][j];
		for (j = 0; j < Limit; j++)
			limit[Second_Friend][j] = -(grid[Second_Friend][Lola_C] / lola) * limit[Lola_R][j] + limit[Second_Friend][j];
		for (j = 0; j < Limit; j++)
			limit[Third_Friend][j] = -(grid[Third_Friend][Lola_C] / lola) * limit[Lola_R][j] + limit[Third_Friend][j];
		for (j = 0; j < Limit; j++)//must be in the last of funtion
			limit[Lola_R][j] = limit[Lola_R][j] / lola;
	}
	void eval_simplex() {/////////////////////////////*******************COMLETED****************************************
		grid[First_Friend][First_Child_Friend] = -(grid[First_Friend][Lola_C] / lola) *
			grid[Lola_R][First_Child_Friend] + grid[First_Friend][First_Child_Friend];
		grid[First_Friend][Second_Child_Friend] = -(grid[First_Friend][Lola_C] / lola) *
			grid[Lola_R][Second_Child_Friend] + grid[First_Friend][Second_Child_Friend];

		grid[First_Friend][RHS] = -(grid[First_Friend][Lola_C] / lola) * grid[Lola_R][RHS] + grid[First_Friend][RHS];
		/////////////////////////////////////////////////**///////////////////////////////////////////////////////////////////
		grid[Second_Friend][First_Child_Friend] = -(grid[Second_Friend][Lola_C] / lola) *
			grid[Lola_R][First_Child_Friend] + grid[Second_Friend][First_Child_Friend];

		grid[Second_Friend][Second_Child_Friend] = -(grid[Second_Friend][Lola_C] / lola) *
			grid[Lola_R][Second_Child_Friend] + grid[Second_Friend][Second_Child_Friend];

		grid[Second_Friend][RHS] = -(grid[Second_Friend][Lola_C] / lola) * grid[Lola_R][RHS] + grid[Second_Friend][RHS];
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		grid[Third_Friend][First_Child_Friend] = -(grid[Third_Friend][Lola_C] / lola) *
			grid[Lola_R][First_Child_Friend] + grid[Third_Friend][First_Child_Friend];

		grid[Third_Friend][Second_Child_Friend] = -(grid[Third_Friend][Lola_C] / lola) *
			grid[Lola_R][Second_Child_Friend] + grid[Third_Friend][Second_Child_Friend];

		grid[Third_Friend][RHS] = -(grid[Third_Friend][Lola_C] / lola) * grid[Lola_R][RHS] + grid[Third_Friend][RHS];
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		eval_limit();
		set_limit();
		/////////////////////////////////////////////////**///////////////////////////////////////////////////////////////////
		for (j = 0; j < 3; j++)//must be before of the last loop
			grid[Lola_R][j] = grid[Lola_R][j] / lola;
		grid[Lola_R][RHS] = grid[Lola_R][RHS] / lola;
		//******************************************************************************************
		for (i = 0; i < 4; i++)//put in Lola 1 and in his friend 0***********must be end of calculate
			grid[i][Lola_C] = 0;
		grid[Lola_R][Lola_C] = 1;//end*************************************************************COMPLETED********
	}
	bool find_lola() {
		if (MAX)find_min_target();
		if (min)find_MAX_target();
		//first of all check the column that which is 0
		if (grid[0][Lola_C] == 0 && grid[1][Lola_C] && grid[2][Lola_C]) {
			cout << "***three of element of Lola are 0***";
			return false;
		}
		if (MAX)find_MAX_RHS();
		if (min)find_min_RHS();
		lola = grid[Lola_R][Lola_C];
	}
	void set_limit() {
		limit[0][0] = 1;
		limit[1][1] = 1;
		limit[2][2] = 1;
	}
	void get_func() {
		cout << "\nenter x1 when s1 : ";
		cin >> grid[0][0];
		cout << "\nenter x1 when s2 : ";
		cin >> grid[1][0];
		if (_Limit == 3) {
			cout << "\nenter x1 when s3 : ";
			cin >> grid[2][0];
		}
		cout << "\nenter x1 when z : ";
		cin >> grid[3][0];

		cout << "\nenter x2 when s1 : ";
		cin >> grid[0][1];
		cout << "\nenter x2 when s2 : ";
		cin >> grid[1][1];
		if (_Limit == 3) {
			cout << "\nenter x2 when s3 : ";
			cin >> grid[2][1];
		}
		cout << "\nenter x2 when z : ";
		cin >> grid[3][1];
		if (Variable == 3) {
			cout << "\nenter x3 when s1 : ";
			cin >> grid[0][2];
			cout << "\nenter x3 when s2 : ";
			cin >> grid[1][2];
			if (_Limit == 3) {
				cout << "\nenter x3 when s3 : ";
				cin >> grid[2][2];
			}
			cout << "\nenter x3 when z : ";
			cin >> grid[3][2];
		}

		cout << "\nenter RHS when s1 : ";
		cin >> grid[0][3];
		cout << "\nenter RHS when s2 : ";
		cin >> grid[1][3];
		if (_Limit == 3) {
			cout << "\nenter RHS when s3 : ";
			cin >> grid[2][3];
		}
		cout << "\n\t";
	}
	void display() {
		system("cls");
		j = 0;
		int bet = 6;
		for (i = 0; i < 4; i++) {
			if (_Limit == 2 && i == 2)continue;
			gotoxy(20, i + 1);
			cout << "#S_" << i + 1;
			if(i==3){ gotoxy(20, i + 1);cout << "#Z_";}
			gotoxy(20, i + 1);
			for (j = 0; j < 4; j++) {
				if (Variable == 2 && j == 2)continue;
				if (j != 3) { gotoxy((j + 1) * bet + 20, 0); cout << "X_" << j + 1; }
				if (j == 3) { gotoxy((j + 1) * bet + 43, 0); cout << "RHS"; }
				gotoxy((j + 1) * bet + 20, i + 1);
				if (j != 3) { cout << "|"; printf("%1.2f", grid[i][j]); }
				if (j == 3) { gotoxy((j + 1) * bet + 43, i + 1); cout << "|";printf("%1.2f", grid[i][j]); }
				if (i < 4 && j < 3) {
					gotoxy((j + 1) * bet + 39, 0); cout << "S_" << j + 1;
					gotoxy((j + 1) * bet + 39, i + 1);
					cout << "|";
					printf("%1.2f", limit[i][j]);
				}
			}
		}
	}
	bool check() {
		if (MAX) {
			cout << grid[3][1];
			if (Variable == 2) {
				if (grid[3][0] >= 0 && grid[3][1] >= 0)return true;
				else return false;
			}
			else if (Variable == 3) {
				if (grid[3][0] >= 0 && grid[3][1] >= 0 && grid[3][2] >= 0)return true;
				else return false;
			}
		}
		else if (min) {
			if (Variable == 2) {
				if (grid[3][0] < 0 && grid[3][1] < 0)return true;
				else return false;
			}
			else if (Variable == 3) {
				if (grid[3][0] < 0 && grid[3][1] < 0 && grid[3][2] < 0)return true;
				else return false;
			}
		}
	}
	bool Menu() {//get_func was called before this
	Agian:	if (!find_lola())return false;
		set_address();
		eval_simplex();
		display();
		gotoxy(0, 6);
		cout << "For See Next Solution Grid Press Enter\nPress \"ESC\" For Exit";
		if (_getch() == 27)return true;
		else {
			if (check()) {
				display(); return true;
			}
			else goto Agian;
		}
	}
};



int main()
{
	int H;
	Simplex simplex;
	cout << "\nSet THE MENU\nFor MAX press 1 For min press 2 : ";
	cin >> H;
	if (H == 1) { MAX = 1; min = 0; }
	else if (H == 2) { MAX = 0; min = 1; }
	cout << "\nHow many variables does the function have? (#2 OR #3) : ";
	cin >> H;
	if (H == 2)Variable = 2;
	if (H == 3)Variable = 3;
	cout << "\nHow many limitions does the function have? (#2 OR #3) : ";
	cin >> H;
	if (H == 2)_Limit = 2;
	if (H == 3)_Limit = 3;
	simplex.get_func();
	if (simplex.Menu())cout << "\nSuccessfully Done!" << endl;
	



	return 0;
}