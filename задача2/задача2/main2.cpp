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
	int count_2 = 0;
	count_2++;
	cout << "Input Squar " << count_2 + 1 << " room: ";
	cin >> room_1.Square;
	char answer_;
	cout << "What is the room: 1.bedroom, 2.kitchen, 3.bathroom, 4.children_room, 5.living_room = 16 ? ";
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

void input_floor(Floor flor_1) {
	cout << "Input ceiling height of "<< " flor: ";
	cin >> flor_1.ceiling_height;
	/*/do {
		/*if (flor_1.count_room < 2 || flor_1.count_room > 4) {
			cout << "Imposible room count\n";
		}
	} while (flor_1.count_room < 2 || flor_1.count_room > 4);*/
}

/*/void input_house(Bulds& bulds_1) {
	Bulds::House_s house_1;
	cout << "What is the area of your house? ";
	cin >> house_1.Square_H;
	string answer_3;
	cout << "You have bakes in house: Yes or No? ";
	cin >> answer_3;
	if (answer_3 == "Yes") {
		house_1.backs *= yes;
	}
	do {
		cout << "How many floors does your house have? ";
		cin >> house_1.count_floar;
		if (house_1.count_floar < 1 || house_1.count_floar > 3) {
			cout << "Imposible floor count\n";
		}
	} while (house_1.count_floar < 1 || house_1.count_floar > 3);
	input_floor(house_1);
	bulds_1.house_ss.push_back(house_1);
}

void input_garage(Bulds& bulds_1) {
	Bulds::Garage garage_1;
	cout << "Input squar of garage: ";
	cin >> garage_1.Square;
	bulds_1.garage_ss.push_back(garage_1);

}

void input_shed(Bulds& bulds_1) {
	Bulds::Shed shed_1;
	cout << "Input squar of shed: ";
	cin >> shed_1.Square;
	bulds_1.shed_ss.push_back(shed_1);
}

void input_bathhouse(Bulds& bulds_1) {
	Bulds::Bathhouse bathhouse_1;
	cout << "Input squar of bathhouse: ";
	cin >> bathhouse_1.Square;
	string answer_4;
	cout << "You have bakes in bathhouse: Yes or No? ";
	cin >> answer_4;
	if (answer_4 == "Yes") {
		bathhouse_1.backs |= yes;
	}
	bulds_1.bathhouse_ss.push_back(bathhouse_1);
}*/

void input_bulds(Bulds& bulds_1) {
	
}

void input_plot(Plot plot_1) {
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
	}
	cout << "You have garage in plot 1.Yes or 2.No? ";
	cin >> answer;
	if (answer == 1) {
		plot_1.bulds |= garage;
	}
	cout << "You have shed in plot 1.Yes or 2.No? ";
	cin >> answer;
	if (answer == 1) {
		plot_1.bulds |= shed;
	}
	cout << "You have bathhouse in plot 1.Yes or 2.No? ";
	cin >> answer;
	if (answer == 1) {
		plot_1.bulds |= bathhouse;
	}
	if ((plot_1.bulds | house) | (plot_1.bulds | garage) | (plot_1.bulds | shed) | (plot_1.bulds | bathhouse)) {
		input_bulds(plot_1);
	}
}

void input_village(Village& village_1) {
	cout << "Input count all plots";
	int count_plot = 0;
	cin >> count_plot;
	cout << "input square of village: ";
	cin >> village_1.Square;
	while (count_plot != 0) {
		Plot plot_1;
		input_plot(plot_1);
		village_1.plot_ss.push_back(plot_1);
		count_plot--;
	}
}

void calculation_percentage_development(Village& village_1,int* part_of_occupied_land) {
	int occupied_land = 0;
	for (int i = 0; i < village_1.count_plot; i++) {
		if (!village_1.plot_ss[i].buld_ss[0].house_ss.empty()) {
			occupied_land += village_1.plot_ss[i].buld_ss[0].house_ss[0].Square_H;
		}
		if (!village_1.plot_ss[i].buld_ss[0].garage_ss.empty()) {
			occupied_land += village_1.plot_ss[i].buld_ss[0].garage_ss[0].Square;
		}
		if (!village_1.plot_ss[i].buld_ss[0].shed_ss.empty()) {
			occupied_land += village_1.plot_ss[i].buld_ss[0].shed_ss[0].Square;
		}
		if (!village_1.plot_ss[i].buld_ss[0].bathhouse_ss.empty()) {
			occupied_land += village_1.plot_ss[i].buld_ss[0].bathhouse_ss[0].Square;
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