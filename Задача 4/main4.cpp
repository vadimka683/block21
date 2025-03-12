#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include<fstream>

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
	bool status_live;
};

void save(vector<character>& all_players) {
	ofstream save_play("play.BIN", ios::binary);
	for (int i = 0; i < all_players.size(); i++) {
		save_play.write(reinterpret_cast<char*>(&all_players[i].position.X), sizeof(all_players[i].position.X));
		save_play.write(reinterpret_cast<char*>(&all_players[i].position.Y), sizeof(all_players[i].position.Y));
	}
}

void input_user_character(vector<character>& all_characters) {
	character player;
	player.team = true;
	player.status_live = true;
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
		enemy.status_live = true;
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
			all_characters[i].position.X = rand() % 20;
			all_characters[i].position.Y = rand() % 20;
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
					if (all_character[h].position.X == j && all_character[h].position.Y == i && all_character[h].status_live == true) {
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

void player_move(vector<character>& player) {
	bool norm_move = false;
	while (!norm_move) {
		char answer;
		cout << "Input comand: 1.L 2.R 3.U 4.D: ";
		cin >> answer;
		if (answer == 'L') {
			if (player[0].position.X - 1 < 0) {
				cout << "Inposible move\n";
			}
			else {
				player[0].position.X -= 1;
				norm_move = true;
			}

		}
		else if (answer == 'R') {
			if (player[0].position.X + 1 > 19) {
				cout << "Inposible move\n";
			}
			else {
				player[0].position.X += 1;
				norm_move = true;
			}
		}
		else if (answer == 'U') {
			if (player[0].position.Y - 1 < 0) {
				cout << "Inposible move\n";
			}
			else {
				player[0].position.Y -= 1;
				norm_move = true;
			}
		}
		else if (answer == 'D') {
			if (player[0].position.Y + 1 > 19) {
				cout << "Inposible move\n";
			}
			else {
				player[0].position.Y += 1;
				norm_move = true;
			}
		}
	}
	for (int i = 1; i < player.size(); i++) {
		if (player[0].position.X == player[i].position.X && player[0].position.Y == player[i].position.Y) {
			int cur_damage;
			if (player[i].armor - player[0].damage <= 0) {
				cur_damage = (-1) * (player[i].armor - player[0].damage);
				player[i].armor = 0;
				player[i].lives -= cur_damage;
				if (player[i].lives <= 0) {
					player[i].status_live = false;
				}
			}
			else {
				player[i].armor -= player[0].damage;
			}
		}
	}
}

bool chek_enemy_stay(vector<character>& player, int& i) {
	for (int h = 1; h < player.size(); h++) {
		if (i == h) {
			continue;
		}
		if (player[i].position.X == player[h].position.X && player[i].position.Y == player[h].position.Y) {
			return false;
		}
	}
	return true;
}

void enemy_move(vector<character>& player) {
	int i = 1;
	srand(time(NULL));
	while (i < player.size()) {
		enum direction { up = 1, down = 2, left = 4, right = 8 };
		vector<int> rand_direction = { 1, 2, 4, 8 };
		int random = 0;
		random |= rand_direction[rand() % 4];
		if (random & up) {
			if (player[i].position.Y - 1 < 0) {
				continue;
			}
			else if (!chek_enemy_stay(player,i)) {
				continue;
			}
			else {
				player[i].position.Y -= 1;
			}
		}
		else if (random & down) {
			if (player[i].position.Y + 1 > 19) {
				continue;
			}
			else if (!chek_enemy_stay(player, i)) {
				continue;
			}
			else {
				player[i].position.Y += 1;
			}
		}
		else if (random & right) {
			if (player[i].position.X + 1 > 19) {
				continue;
			}
			else if (!chek_enemy_stay(player, i)) {
				continue;
			}
			else {
				player[i].position.X += 1;
			}
		}
		else if (random & left) {
			if (player[i].position.X - 1 < 0) {
				continue;
			}
			else if (!chek_enemy_stay(player, i)) {
				continue;
			}
			else {
				player[i].position.X -= 1;
			}
		}
		if (player[i].position.X == player[0].position.X && player[i].position.Y == player[0].position.Y) {
			int cur_damage;
			if (player[0].armor - player[i].damage <= 0) {
				cur_damage = (-1) * (player[0].armor - player[i].damage);
				player[0].armor = 0;
				player[0].lives -= cur_damage;
				if (player[0].lives <= 0) {
					player[0].status_live = false;
				}
			}
			else {
				player[0].armor -= player[i].damage;
			}
		}
		i++;
	}
}

bool chek_win(vector<character>& all_character) {
	if (all_character[0].status_live == false) {
		cout << "Enemy WIN!!!!!";
		return false;
	}
	else {
		for (int i = 1; i < all_character.size(); i++) {
			if (all_character[i].status_live == true) {
				return true;
			}
		}
		cout << "You are winner!!!!";
		return false;
	}
}

int main() {
	vector<character> all_character;
	int count_enemy = 5;
	input_user_character(all_character);
	input_enemy(all_character, count_enemy);
	start_position(all_character);
	print_table(all_character);
	enemy_move(all_character);
	print_table(all_character);
}