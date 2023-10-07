#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<vector>

using namespace std;

// Constants:
int money = 150;
bool closeProgram = false;
bool redraw = true;
string recentError = "";
int cIncomeDelay = 100;
bool incomePause = true;
int page = 0;
int generators = 0;

bool selling = false;

// Tower cost and tower count:
vector<vector<string>> towerNames = { {"Generator (0-2-4 Farm)", "Mine Layer (2-0-0 Spike Factory)", "Radio Transmitter (2-1-0 Monkey Village)", "Carpet Bomb (1-4-0 Spike Factory's ability)", "Ultimate Storm (2-5-0 Glue Gunner's ability)", "Tactical Nuke (0-5-0 Monkey Ace's ability)"}, {"Trooper (0-2-0 Dart Monkey)", "Sprayer (0-1-0 Druid)", "Splatter (0-2-0 Glue Monkey)", "Sniper (1-0-1 Sniper Monkey)", "Eliminator (1-0-0 Ninja Monkey)", "Strafer (0-0-0 Ace Monkey)", "Helicopter (0-2-0 Heli-pilot)", "Mortar (2-0-1 Mortar Monkey)", "Shredder (0-2-0 Super Monkey)"}, {"Submarine (0-0-1 Submarine)", "Defender (2-0-0 Boat)", "Sea Hunter (1-2-0 Submarine)", "Assault Ship (0-3-2 Boat)"} };
vector<vector<int>> towers = { {0, 0, 0, 0, 0, 0}, { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, {0, 0, 0, 0} };
vector<vector<int>> tCost = { {250, 280, 400, 1500, 5000, 8000}, { 70, 120, 140, 160, 180, 450, 600, 1200, 2500 }, {300, 600, 650, 2000} };
float sellPayback = 0.7;

// Income:
int incomeDelay = 100;
int baseIncome = 10;
int generatorIncome = 5;

void draw() {
	redraw = false;
	system("cls");
	cout << "Money: " << money << endl;
	cout << "Control Pannel:" << endl;
	for (int i = 0; i < towers[page].size(); i++) {
		int tPrice = tCost[page][i];
		if (selling) {
			tPrice *= sellPayback;
		}
		cout << i + 1 << ": " << towerNames[page][i] << " (Money = " << tPrice << ") - " << towers[page][i] << " on board." << endl;
	}
	cout << "\nPage " << page + 1 << " (Use O and P to navigate pages)." << endl;
	cout << "Mode: ";
	if (selling) {
		cout << "Sell Mode (Use M to switch to Buy Mode)." << endl;
	}
	else {
		cout << "Buy Mode (Use M to switch to Sell Mode)." << endl;
	}
	
	if (incomePause) {
		cout << "Income paused. Press N to unpause." << endl;
	}
	else {
		cout << "Income unpaused. Press N to pause." << endl;
	}
	cout << "Press L to close the program." << endl;

	if (recentError != "") {
		cout << "\n" << recentError << endl;
	}
}

void logic() {
	if (!incomePause) {
		if (cIncomeDelay <= 0) {
			cIncomeDelay = incomeDelay;
			money += baseIncome + (generatorIncome * generators);
			redraw = true;
		}
		else {
			cIncomeDelay--;
		}
	}
}

void input() {
	int selection = 0;
	char character = 'a';
	if (_kbhit()) {
		redraw = true;
		char key = _getch();
		recentError = "";
		switch (key) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			character = key;
			selection = character - '0';
			selection -= 1;
			if ((selection) < towers[page].size()) {
				if (selling) {
					if (towers[page][selection] > 0) {
						towers[page][selection]--;
						money += tCost[page][selection] * sellPayback;
					}
					else {
						recentError = "None of that tower is on the field!";
					}
				}
				else {
					if (money >= tCost[page][selection]) {
						towers[page][selection]++;
						money -= tCost[page][selection];
						if (towerNames[page][selection] == "Generator (0-2-4 Farm)") {
							generators++;
						}
					}
					else {
						recentError = "Not enough money for that tower!";
					}
				}
			}
			else {
				recentError = "No tower exists in that slot!";
			}
			break;
		case 'n':
			incomePause = !incomePause;
			break;
		case 'm':
			selling = !selling;
			break;
		case 'l':
			closeProgram = true;
			break;
		case 'o':
			if (page > 0) {
				page--;
			}
			break;
		case 'p':
			if (page < (towers.size() - 1)) {
				page++;
			}
			break;
		default:
			break;
		}
	}
}

void control() {
	while (!closeProgram) {
		if (redraw) {
			draw();
		}
		input();
		logic();
		Sleep(10);
	}
}

int main() {
	cIncomeDelay = incomeDelay;
	control();
}