#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std;


struct pipe {
	int id = -1;
	float lenght, diameter;
	bool work;
};
struct station {
	string name;
	int id = -1;
	int number, work_station;
	float percent;
};

int GetCorrectNumber(int min, int max)
{
	int a;
	cin >> a;
	while (a < min || cin.peek() != '\n' || a > max)
	{
		cout << "Invalid Input!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please a number from (" << min  << " - " << max << ") : ";
		cin >> a;
	}
	return a;
}


void getfloat(float& a, float min, float max) {
	cin >> a;
	while (a < min || cin.peek() != '\n' || a > max)
	{
		cout << "Invalid Input!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please add number from " << min << " to " << max << ": ";
		cin >> a;
	}
}

void getint(int& a, int min , int max) {
	cin >> a;
	while (a < min || cin.peek() != '\n' || a > max)
	{
		cout << "Invalid Input!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please add number from " << min << " to " << max << ": ";
		cin >> a;
	}
}

bool getbool() {
	char repair;
	while (true)
	{
		repair = _getch();
		if (repair == '0')
			return false;
		else if (repair == '1')
			return true;
		else
			cout << "Error! Input correct value!!!" << endl;
	}
}

void getstring(string& k) {
	string a;
	cin.ignore(2000, '\n');
	getline(cin >> ws, a);
	k = a;
	a.erase(remove(a.begin(), a.end(), ' '), a.end());
	while (a.empty()) {
		cout << "Try again.\n";
		getline(cin, a);
		k = a;
		a.erase(remove(a.begin(), a.end(), ' '), a.end());
	}
	k = k.substr(k.find_first_not_of(" \t"));
}

void compare(int& a, int max) {
	cin >> a;
	while (a < 0 || cin.peek() != '\n' || a > max)
	{
		cout << "Invalid Input!\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please select a number from 1 to " << max << ": ";
		cin >> a;
	}
}

void inputpipe(pipe& Pipe)
{
	Pipe.id = 0;
	cout << "Pipe lenght" << endl;
	getfloat(Pipe.lenght, 0, 10000);
	cout << "Pipe diameter" << endl;
	getfloat(Pipe.diameter, 0 , 1000);
	cout << "Is it work? 0 - No; 1 - Yes" << endl;
	Pipe.work = getbool();
	cout << endl;
}
void inputstation(station& Station)
{
	Station.id = 0;
	cout << "Name of station:" << endl;
	getstring(Station.name);
	cout << "How many workshop?" << endl;
	getint(Station.number, 0 , 100);
	cout << "How many working? " << endl;
	compare(Station.work_station, Station.number);
	cout << "Percent of station" << endl;
	getfloat(Station.percent, 0, 100);
}
void changepipe(pipe& Pipe)
{
	if (Pipe.id != -1)
	{
		cout << "Now pipe has status " << Pipe.work << endl << "Add a new status: ";
			Pipe.work = getbool();
			cout << endl;
	}

	else
	{
		cout << "At first add a pipe " << endl;
		inputpipe(Pipe);
	}
}

void outputpipe(const pipe P)
{
	if (P.id != -1) {
		cout << "id:" << P.id << endl;
		cout << "length:" << P.lenght << endl;
		cout << "diameter:" << P.diameter << endl;
		if (P.work == 1)
			cout << "Pipe is work" << endl;
		else
			cout << "Pipe isnt work" << endl;
	}
	else {
		cout << "At first add a pipe" << endl;
		cout << endl;
	}
}

void changestation(station& Station)
{
	if (Station.id != -1)
	{
		cout << "Now number of working workshop is " << Station.work_station << endl << "Add a new number: ";
		compare(Station.work_station, Station.number);
		cout << endl;
	}
	else {
		cout << "At first add a station" << endl;
		inputstation(Station);
	}
}


void outputstation(const station& S)
{
	if (S.id != -1) {
		cout << "Station id:" << " " << S.id << endl;
		cout << "Station name:" << " " << S.name << endl;
		cout << "Number of workshop: " << " " << S.number << endl;
		cout << "Number of working workshop:" << " " << S.work_station << endl;
		cout << "Percent of station: " << " " << S.percent << endl;
	}
	if (S.id == -1) {
		cout << "At first add a station!!!" << endl;
		cout << endl;
	}
}

void printall(const pipe Pipe, const station Station) {
	ofstream fout;
	fout.open("File.txt");
	if (Pipe.id != -1)
		fout << Pipe.id << endl << Pipe.lenght << endl << Pipe.diameter << endl <<
		Pipe.work << endl;
	else fout << -1 << endl;
	if (Station.id != -1)
		fout << Station.id << endl << Station.name << endl << Station.number << endl << Station.work_station << endl << Station.percent;
	else fout << -1 << endl;
	fout.close();
}


void write(pipe& Pipe,station& Station) {
	ifstream fin;
	fin.open("File.txt", ios::in);
	if (!fin.is_open()) 
		cout << "File not open.\n";
	else if (fin.peek() == EOF) 
		cout << "File is empty.";
	else
	{
		fin >> Pipe.id;
		if (Pipe.id != -1)
		fin >> Pipe.lenght >> Pipe.diameter >> Pipe.work;
		fin >> Station.id;
		if (Station.id != -1)
		{
			fin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			getline(fin, Station.name);
			fin >> Station.number >> Station.work_station >> Station.percent;
		}
		fin.close();
	}
}


int main()
{
	int a = 1;
	pipe Pipe;
	station Station;
	while (a > 0)
	{
		cout << "Main Menu" << endl;
		cout << "Choose number" << endl;
		cout << "1.Add pipe" << endl;
		cout << "2.Add station" << endl;
		cout << "3.Show pipe number" << endl;
		cout << "4.Show station number" << endl;
		cout << "5.Change pipe" << endl;
		cout << "6.Change station" << endl;
		cout << "7.Save" << endl;
		cout << "8.Load" << endl;
		cout << "9.Exit" << endl;
		cout << "Choose" << endl;
		switch (GetCorrectNumber(0, 10)) {
		case 1:
			inputpipe(Pipe);
			break;

		case 2:
			inputstation(Station);
			break;

		case 3:
			outputpipe(Pipe);
			break;

		case 4:
			outputstation(Station);
			break;

		case 5:
			changepipe(Pipe);
			break;

		case 6:
			changestation(Station);
			break;

		case 7:
			printall(Pipe, Station);
			break;
		case 8:
			write(Pipe, Station);
			break;
		case 9:
			return 0;
		}
	}

}