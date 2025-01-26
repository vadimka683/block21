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
	ifstream file("save.bin",ios::binary);
	if (file.is_open()) {
		file.close();
	}
	else {
		file.close();
		ofstream file("save.bin", ios::binary);
		file.close();
	}
}

void read_file(vector<statement>& all) {
	all.clear();
	file_empty();
	ifstream file("save.bin", ios::binary);
	while (!file.eof())
	{
		statement p;
		int len = 0;
		file.read(reinterpret_cast<char*>(&len), sizeof(len));
		if (len != 0) {
			p.name.resize(len);
			file.read(reinterpret_cast<char*>(&p.name[0]), len);
		}
		else {
			break;
		}

		file.read(reinterpret_cast<char*>(&len), sizeof(len));
		p.surname.resize(len);
		file.read(reinterpret_cast<char*>(&p.surname[0]), len);

		file.read(reinterpret_cast<char*>(&len), sizeof(len));
		p.date.resize(len);
		file.read(reinterpret_cast<char*>(&p.date[0]), len);

		file.read(reinterpret_cast<char*>(&p.money), sizeof(p.money));

		all.push_back(p);
	}
}

void app_end(vector<statement>& all, stringstream& user) {
	statement p;
	user >> p.name >> p.surname >> p.date >> p.money;
	all.push_back(p);
}

void push_vector(vector<statement>& all) {
	ofstream file("save.bin", ios::binary);
	for (int i = 0; i < all.size(); i++) {
		int len;
		len = all[i].name.length();
		file.write(reinterpret_cast<char*>(&len), sizeof(len));
		file.write(all[i].name.c_str(), len);

		len = all[i].surname.length();
		file.write(reinterpret_cast<char*>(&len), sizeof(len));
		file.write(all[i].surname.c_str(), len);
		
		len = all[i].date.length();
		file.write(reinterpret_cast<char*>(&len), sizeof(len));
		file.write(all[i].date.c_str(), len);
		
		file.write(reinterpret_cast<char*>(&all[i].money), sizeof(all[i].money));
	}
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