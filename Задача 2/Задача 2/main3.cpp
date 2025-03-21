#include<iostream>

using namespace std;

struct Vectors
{
	double X = 0;
	double Y = 0;
};

void add(Vectors& vector_1, Vectors& vector_2, Vectors& vector_3) {
	vector_3.X = vector_1.X + vector_2.X;
	vector_3.Y = vector_1.Y + vector_2.Y;
}
void subtract(Vectors& vector_1, Vectors& vector_2, Vectors& vector_3) {
	vector_3.X = vector_1.X + (vector_2.X * (-1));
	vector_3.Y = vector_1.Y + (vector_2.Y * (-1));
}
void scale(Vectors& vector_1, Vectors& vector_2, double& number) {
	vector_2.X = vector_1.X * number;
	vector_2.Y = vector_1.Y * number;
}
void length(double& leng, Vectors& vector_1) {
	leng = sqrt(pow(vector_1.X, 2) + pow(vector_1.Y, 2));
}

void normalize(Vectors& vector_1, Vectors& vector_2) {
	double lengo = 0;
	length(lengo, vector_1);
	vector_2.X = vector_1.X / lengo;
	vector_2.Y = vector_1.Y / lengo;
}
void input_vector(Vectors& vector_1) {
	cout << "Input X and Y of your vector: ";
	cin >> vector_1.X >> vector_1.Y;
}

int main() {
	string answer;
	do {
		cout << "Input comand: 1.add 2.subtract 3.scale 4.length 5.normalize 6.exit: ";
		cin >> answer;
		if (answer == "add") {
			Vectors vect_1;
			cout << "Input first vector: \n";
			input_vector(vect_1);
			Vectors vect_2;
			cout << "Input second vector: \n";
			input_vector(vect_2);
			Vectors vect_3;
			add(vect_1, vect_2, vect_3);
			cout << "(" << vect_3.X << " , " << vect_3.Y << ")";
		}
		else if (answer == "subtract") {
			Vectors vect_1;
			cout << "Input first vector: \n";
			input_vector(vect_1);
			Vectors vect_2;
			cout << "Input second vector: \n";
			input_vector(vect_2);
			Vectors vect_3;
			subtract(vect_1, vect_2, vect_3);
			cout << "(" << vect_3.X << " , " << vect_3.Y << ")";
		}
		else if (answer == "scale") {
			Vectors vect_1;
			cout << "Input first vector: \n";
			input_vector(vect_1);
			double num;
			cout << "Input number: ";
			cin >> num;
			Vectors vect_2;
			scale(vect_1, vect_2, num);
			cout << "(" << vect_2.X << " , " << vect_2.Y << ")";
		}
		else if (answer == "length") {
			Vectors vect_1;
			cout << "Input first vector: \n";
			input_vector(vect_1);
			double leng = 0;
			length(leng, vect_1);
			cout << "Length = "<<leng;
		}
		else if (answer == "normalize")
		{
			Vectors vect_1;
			input_vector(vect_1);
			Vectors vect_2;
			normalize(vect_1, vect_2);
			cout << "(" << vect_2.X << " " << vect_2.Y << ")";
		}
		else if (answer == "exit") {
			return 0;
		}
		else {
			cout << "Error comand\n";
		}
	} while (answer != "exit");
}