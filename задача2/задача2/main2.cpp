#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

enum buildings { garage = 1, shed = 2, bathhouse = 4, house = 8 };

enum rooms{ bedroom = 1, kitchen = 2, bathroom = 4, children_room = 8, living_room = 16 };

enum bake{ yes = 1, no = 2};


struct village
{
	int count_plot = 0;
	struct plot {
		int number = 0;
		int bulds = 0;
		
		struct House_s
		{
			int Square = 0;
			int count_floar = 0;
			int bakes = 0;
			
			struct Floor
			{
				int ceiling_height = 0;
				int count_room = 0;
				
				struct Room
				{
					int Square = 0;
					int what_room = 0;
				};
				vector<Room> rooms;
			};
			vector<Floor> floors;
		};
		vector<House_s> House_ss;

		struct garage_s
		{
			int Square = 0;
		};
		vector<garage_s> garage_ss;
		struct shed_s
		{
			int Square = 0;
		};
		vector<shed_s> shed_ss;
		struct bathhouse_s
		{
			int Square = 0;
			int backs = 0;
		};
		vector<bathhouse_s> bathhouse_ss;
	};
	vector<plot> plots;
};

int main() {
	village toun;
	cout << "Input count all plots";
	cin >> toun.count_plot;
	int count = 0;
	while (count < toun.count_plot) {
		village::plot plot_1;
		cout << "Input plot number: ";
		cin >> plot_1.number;
		
		cout << "You have house in plot 1.Yes or 2.No? ";
		int answer;
		cin >> answer;
		if (answer == 1) {
			plot_1.bulds |= house;
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

		if (plot_1.bulds & house) {
			village::plot::House_s house_1;
			cout << "What is the area of ​​your house? ";
			cin >> house_1.Square;
			string answer_3;
			cout << "You have bakes in house: Yes or No? ";
			cin >> answer_3;
			if (answer_3 == "Yes") {
				house_1.bakes *= yes;
			}
			cout << "How many floors does your house have? ";
			cin >> house_1.count_floar;
			
			int count_1 = 0;
			while (count_1 < house_1.count_floar) {
				village::plot::House_s::Floor flor_1;
				cout << "Input ceiling height of " << count_1 + 1 << " flor: ";
				cin >> flor_1.ceiling_height;
				cout << "Input count room of " << count_1 + 1 << " flor: ";
				cin >> flor_1.count_room;
				int count_2 = 0;
				while (count_2 < flor_1.count_room) {
					village::plot::House_s::Floor::Room room_1;
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
					flor_1.rooms.push_back(room_1);
					count_2++;
				}
				house_1.floors.push_back(flor_1);
				count_1++;
			}
			plot_1.House_ss.push_back(house_1);
		}
		if (plot_1.bulds & garage) {
			village::plot::garage_s garage_1;
			cout << "Input squar of garage: ";
			cin >> garage_1.Square;
			plot_1.garage_ss.push_back(garage_1);
		}
		if (plot_1.bulds & shed) {
			village::plot::shed_s shed_1;
			cout << "Input squar of shed: ";
			cin >> shed_1.Square;
			plot_1.shed_ss.push_back(shed_1);
		}
		if (plot_1.bulds & bathhouse) {
			village::plot::bathhouse_s bathhouse_1;
			cout << "Input squar of bathhouse: ";
			cin >> bathhouse_1.Square;
			string answer_4;
			cout << "You have bakes in house: Yes or No? ";
			cin >> answer_4;
			if (answer_4 == "Yes") {
				bathhouse_1.backs* yes;
			}
			plot_1.bathhouse_ss.push_back(bathhouse_1);
		}
		count++;
		toun.plots.push_back(plot_1);
	}
}