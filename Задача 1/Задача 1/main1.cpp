#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

struct statement
{
	string name;
	string surname;
	string date;
	int money;
};

void list(vector<statement>& all) {
	for (int i = 0; i < all.size(); i++) {
		cout << all[i].name << " " << all[i].surname << " " << all[i].date << " " << all[i].money << "\n";
	}
}

void file_empty() {
	ifstream file("save.txt");
	if (file.is_open()) {
		file.close();
	}
	else {
		file.close();
		ofstream file("save.txt");
		file.close();
	}
}

void read_file(vector<statement>& all) {
	all.clear();
	file_empty();
	ifstream file("save.txt");
	while (!file.eof())
	{
		statement p;
		file >> p.name;
		file >> p.surname;
		file >> p.date;
		file >> p.money;
		all.push_back(p);
	}
	file.close();
}

void app_end(vector<statement>& all, stringstream& user) {
	statement p;
	user >> p.name >> p.surname >> p.date >> p.money;
	all.push_back(p);
}

void push_vector(vector<statement>& all) {
	ofstream file("save.txt");
	for (int i = 0; i < all.size(); i++) {
		file << all[i].name << " ";
		file << all[i].surname << " ";
		file << all[i].date << " ";
		file << all[i].money;
		if (i < all.size() - 1) {
			file << "\n";
		}
	}
	file.close();
}

int main() {
	vector<statement> all;
	string comand;
	do {
		cout << "Input comand: 1.list 2.add 3.exit: ";
		cin >> comand;
		if (comand == "list") {
			cout << "\tSTATEMENT:\n";
			read_file(all);
			list(all);
		}
		else if (comand == "add") {
			read_file(all);
			cin.ignore();
			string user;
			cout << "Input: name surname date money: ";
			getline(cin, user);
			stringstream new_add(user);
			string chek_valid_date;
			new_add >> chek_valid_date >> chek_valid_date >> chek_valid_date;
			int day, month, year;
			day = stoi(chek_valid_date.substr(0,2));
			month = stoi(chek_valid_date.substr(3,2));
			year = stoi(chek_valid_date.substr(6, 4));
			if (day > 30 || day < 0 || month>12 || month < 0 || year < 1000) {
				cout << "Error date\n";
				continue;
			}
			stringstream new_add_(user);
			app_end(all, new_add_);
			push_vector(all);
		}
		else if (comand == "exit") {
			return 0;
		}
		else {
			cout << "Error comand\n";
		}
	} while (true);
}