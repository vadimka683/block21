#include<iostream>
#include<ctime>
#include<vector>
#include<string>

using namespace std;

struct Vectors
{
	int X = 0, Y = 0;
};

struct character
{
	Vectors position;
	string name;
	int lives, armor, damage;
	bool team;
};

void input_user_character(vector<character>& all_characters) {
	character player;
	player.team = true;
	cout << "Input your name: ";
	cin >> player.name;
	cout << "Input count your lives: ";
	cin >> player.lives;
	cout << "Input count your armor: ";
	cin >> player.armor;
	cout << "Input count your damage: ";
	cin >> player.damage;
	all_characters.push_back(player);
}

void input_enemy(vector<character>& all_charaters, int& count_enemy) {
	srand(time(NULL));
	for (int i = 0; i < count_enemy; i++) {
		character enemy;
		enemy.name = "Enemy";
		enemy.name.append(to_string(i));
		enemy.team = false;
		enemy.lives = rand() % 101 + 50;
		enemy.armor = rand() % 50;
		enemy.damage = rand() % 16 + 15;
		all_charaters.push_back(enemy);
	}
}

void start_position(vector<character>& all_characters) {
	srand(time(NULL));
	vector<vector<int>> chek;
	for (int i = 0; i < all_characters.size(); i++) {
		bool position_found = false;
		while (!position_found) {
			all_characters[i].position.X = rand() % 21;
			all_characters[i].position.Y = rand() % 21;
			position_found = true;
			for (int j = 0; j < chek.size(); j++) {
				if (all_characters[i].position.X == chek[j][0] && all_characters[i].position.Y == chek[j][1]) {
					position_found = false;
					break;
				}
			}
		}
		vector<int> vec;
		vec.push_back(all_characters[i].position.X);
		vec.push_back(all_characters[i].position.Y);
		chek.push_back(vec);
	}
}

void print_table(vector<character>& all_character) {
	int count_character = all_character.size();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			bool flag = false;
			if (count_character != 0) {
				for (int h = 0; h < all_character.size(); h++) {
					if (all_character[h].position.X == j && all_character[h].position.Y == i) {
						cout << (all_character[h].team ? 'P' : 'E');
						flag = true;
						--count_character;
					}
				}
			}
			if (!flag) {
				cout << ".";
			}
		}
		cout << "\n";
	}
}

void player_move(character& player) {
	bool norm_move = false;
	while (!norm_move) {
		char answer;
		cout << "Input comand: 1.L 2.R 3.U 4.D: ";
		cin >> answer;
		if (answer == 'L') {
			if (player.position.X - 1 < 0) {
				cout << "Inposible move\n";
			}
			else {
				player.position.X -= 1;
				norm_move = true;
			}

		}
	}
}

int main() {
	vector<character> all_character;
	int count_enemy = 5;
	input_enemy(all_character, count_enemy);
	input_user_character(all_character);
	start_position(all_character);
	print_table(all_character);
}