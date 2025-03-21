#include<iostream>
#include<vector>

using namespace std;

enum buildings { garage = 1, shed = 2, bathhouse = 4, house = 8 };

enum rooms{ bedroom = 1, kitchen = 2, bathroom = 4, children_room = 8, living_room = 16 };


struct Room
{
	int Square = 0;
	int what_room = 0;
};

struct Floor
{
	int ceiling_height = 0;
	vector<Room> room_ss;
};

struct Bulds 
{
	buildings type;
	int Square = 0;
	bool backs = false;
	vector<Floor> floor_ss;
};

struct Plot
{
	int number = 0;
	double area = 0;
	vector<Bulds> buld_ss;
};

struct Village
{
	int Square = 0;
	vector<Plot> plot_ss;
};

void input_room(Room& room_1) {
	cout << "Input Squar of room: ";
	cin >> room_1.Square;
	char answer_;
	cout << "What is the room: 1.bedroom, 2.kitchen, 3.bathroom, 4.children_room, 5.living_room: ";
	cin >> answer_;
	switch (answer_)
	{
	case '1':room_1.what_room |= bedroom; break;
	case '2':room_1.what_room |= kitchen; break;
	case '3':room_1.what_room |= bathroom; break;
	case '4':room_1.what_room |= children_room; break;
	case '5':room_1.what_room |= living_room; break;
	default:cout << "Input Error";
		break;
	}
}

void input_floor(Floor& flor_1) {
	cout << "Input ceiling height of floor ";
	cin >> flor_1.ceiling_height;
	int count_room;
	do {
		cout << "Input count room at floor ";
		cin >> count_room;
		if (count_room < 2 || count_room > 4) {
			cout << "Imposible room count\n";
		}
	} while (count_room < 2 || count_room > 4);
	while (count_room != 0) {
		Room room_1;
		input_room(room_1);
		flor_1.room_ss.push_back(room_1);
		count_room--;
	}
}

void input_bulds(Bulds& bulds_1) {
	if (bulds_1.type & house) {
		cout << "What is the area of your house? ";
		cin >> bulds_1.Square;
		string answer_3;
		cout << "You have bakes in house: Yes or No? ";
		cin >> answer_3;
		bulds_1.backs = (answer_3 == "Yes") ? true : false;
		int answer;
		do {
			cout << "How many floors does your house have? ";
			cin >> answer;
			if (answer < 1 || answer>3) {
				cout << "Inposible count\n";
			}
		} while (answer < 1 || answer>3);
		while (answer != 0) {
			Floor floor_1;
			input_floor(floor_1);
			bulds_1.floor_ss.push_back(floor_1);
			answer--;
		}
	}
	else if (bulds_1.type & garage) {
		cout << "Input squar of garage: ";
		cin >> bulds_1.Square;
	}
	else if (bulds_1.type & shed) {
		cout << "Input squar of shed: ";
		cin >> bulds_1.Square;
	}
	else if (bulds_1.type & bathhouse) {
		cout << "Input squar of bathhouse: ";
		cin >> bulds_1.Square;
		string answer_2;
		cout << "You have bakes in bathhouse: Yes or No? ";
		cin >> answer_2;
		bulds_1.backs = (answer_2 == "Yes") ? true : false;
	}
}

void input_plot(Plot& plot_1) {
	cout << "Input plot number: ";
	cin >> plot_1.number;
	int answer;
	do {
		cout << "How many houses do you have? ";
		cin >> answer;
		if (answer < 1) {
			cout << "Imposible count home\n";
		}
	} while (answer < 1);
	while (answer != 0) {
		Bulds bulds_1;
		bulds_1.type = house;
		input_bulds(bulds_1);
		plot_1.buld_ss.push_back(bulds_1);
		answer--;
	}
	cout << "You have garage in plot 1.Yes or 2.No? ";
	cin >> answer;
	if (answer == 1) {
		Bulds bulds_1;
		bulds_1.type = garage;
		input_bulds(bulds_1);
		plot_1.buld_ss.push_back(bulds_1);
	}
	cout << "You have shed in plot 1.Yes or 2.No? ";
	cin >> answer;
	if (answer == 1) {
		Bulds bulds_1;
		bulds_1.type = shed;
		input_bulds(bulds_1);
		plot_1.buld_ss.push_back(bulds_1);
	}
	cout << "You have bathhouse in plot 1.Yes or 2.No? ";
	cin >> answer;
	if (answer == 1) {
		Bulds bulds_1;
		bulds_1.type = bathhouse;
		input_bulds(bulds_1);
		plot_1.buld_ss.push_back(bulds_1);
	}
	
}

void input_village(Village& village_1) {
	cout << "input square of village: ";
	cin >> village_1.Square;
	cout << "Input count all plots";
	int count_plot = 0;
	cin >> count_plot;
	while (count_plot != 0) {
		Plot plot_1;
		input_plot(plot_1);
		village_1.plot_ss.push_back(plot_1);
		count_plot--;
	}
}

void calculation_percentage_development(Village& village_1,int* part_of_occupied_land) {
	int occupied_land = 0;
	for (int i = 0; i < village_1.plot_ss.size(); i++) {
		for (int j = 0; j < village_1.plot_ss[i].buld_ss.size(); j++) {
			occupied_land += village_1.plot_ss[i].buld_ss[j].Square;
		}
	}
	*part_of_occupied_land = ((double)occupied_land / (double)village_1.Square) * 100;
}

int main() {
	Village village_1;
	input_village(village_1);
	int part_of_occupied_land;
	calculation_percentage_development(village_1, &part_of_occupied_land);
	cout << "Part of occupied land = " << part_of_occupied_land << " %";
}