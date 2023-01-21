#include <iostream>
#include <float.h>

/* ADT and String Manipulation */
#include <sstream>
#include <string>
#include <vector>
#include <set>

/* Files */
#include <fstream>

/* UI and Time */
#include <ctime>
#include <windows.h>
#include <chrono>

using namespace std;
#define RESET   "\033[0m"
#define BLACK   "\033[1m\033[30m"      /* Black */
#define RED     "\033[1m\033[31m"      /* Red */
#define GREEN   "\033[1m\033[32m"      /* Green */
#define WHITE   "\033[1m\033[37m"      /* White */

int countWords(string str) {
	/* Menghitung banyaknya kata dalam 1 line of string (input user) */
	
	bool space = true;
	int count = 0;

	for (auto c:str) {
		if (isspace(c)) {
			space = true;
		} else {
			if (space) {
				++count;
				space = false;
			}
		}
	}
	return count;
}

bool isValid(string str) {
	/* Mengecek input user agar masukan harus [A, 2, ..., Q, K] */

	if (str.length() == 1) {
		/* Handle 1 char */
		if (!isdigit(str[0])) {
			if (str[0] != 'A' && str[0] != 'J' && str[0] != 'Q' && str[0] != 'K') {
				return false;
			}
		} else {
			if (str[0] == '0' or str[0] == '1') {
				return false;
			}
		}
	} else if (str.length() == 2) {
		/* Handle 2 char (10) */
		if (str[0] != '1' || str[1] != '0') {
			return false;
		}
	} else {
		return false;
	}

	return true;
}

bool isValid2(string s) {
	/* Mengecek input user agar masukan terdiri dari 4 masukan */
	
	if (countWords(s) != 4) {
		return false;
	}

	vector <string> input_splitted;
	string input2;
	stringstream ss(s);

	while (getline(ss, input2, ' ')) {
		input_splitted.push_back(input2);
	}

	if (isValid(input_splitted[0]) && isValid(input_splitted[1]) && isValid(input_splitted[2]) && isValid(input_splitted[3])) {
		return true;
	} else {
		return false;
	}
}

int strToNum(string str) {
	/* Mengubah string (masukan user) menjadi number */
	/* str pasti A, J, Q, K, atau angka 2 - 10 (sudah divalidasi) */

	if (str[0] == 'A') {
		return 1;
	} else if (str[0] == 'J') {
		return 11;
	} else if (str[0] == 'Q') {
		return 12;
	} else if (str[0] == 'K') {
		return 13;
	} else {
		if (str.length() == 2 && str[0] == '1' && str[1] == '0') {
			return 10;
		}
		return str[0] - '0';
	}
}

string numToString(int c) {
	/* Mengubah integer to string */
	
	switch(c) {
		case 1:
			return "A";
		case 11:
			return "J";
		case 12:
			return "Q";
		case 13:
			return "K";
		default:
			return to_string(c);
	}
}

double func(double a, char op, double b) {
	/* Menghitung operasi 2 angka dengan menggunakan 4 macam operator */
	
	switch(op) {
		case '+': 
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		default:
			if (b != 0) {
				return a / b;
			} else {
				return -9999;
			}
	}
}

vector <vector<int>> permute(vector<int>& nums) {
	/* Menghasilkan vector of vector yang berisi hasil permutasi */

	if (nums.size() <= 1) { // basis
		return {nums};
	}

	vector <vector<int>> result;
	for (int i = 0; i < nums.size(); i ++) {
		vector<int> v(nums.begin(), nums.end());
		v.erase(v.begin() + i);
		auto res = permute(v); // rekurens

		for (int j = 0; j < res.size(); j ++) {
			vector<int> _v = res[j];
			_v.insert(_v.begin(), nums[i]);

			result.push_back(_v);
		}
	}

	return result;
}

int opToInt(char op) {
	/* Mengubah operator menjadi integer */

	switch(op) {
		case '+': 
			return 0;
		case '-':
			return 1;
		case '*':
			return 2;
		default:
			return 3;
	}
}

double absolute(double x) {
	/* Menghitung absolute suatu angka */
	/* Handle error */

	if (x < 0) {
		return -x;
	} else {
		return x;
	}
}

vector <int> solver1() {
	/* Solver1 : user memasukkan input */

	string input, input2;
	vector <int> numbers;

	cout << "Enter 4 cards: ";
	getline(cin, input);

	while (!isValid2(input)) {
		cout << endl << RED << "Please enter 4 valid value [A, 2, ..., Q, K] !!!" << RESET << endl;
		cout << "Enter 4 cards: ";
		getline(cin, input);
	}

	stringstream ss(input);
	
	while (getline(ss, input2, ' ')) {
		numbers.push_back(strToNum(input2));
	}

	return numbers;
}

vector<int> solver2() {
	/* Solver2 : random generated number */
	/* Menghasilkan vektor dengan 4 random integer */

	srand(time(0));  // Initialize random number generator
	vector <int> random;

	for (int i = 0; i < 4; i ++) {
		random.push_back((rand() % 13) + 1); // 1 - 13
	}

	return random;
}

int inputOneTwo() {
	int n;

	while (true) {
		cout << "> ";
		if (cin >> n && (n == 1 || n == 2)) {
			break;
		} else {
			cout << RED << "Please enter a valid integer!! [1]/[2]" << RESET << endl;
			cin.clear();
		}
	}
	cin.ignore(80, '\n');

	return n;
}

void splash() {
	/* SPLASH SCREEN */

	cout << WHITE << ".------..------.        .------..------..------..------..------..------." << RESET << endl;
	cout << WHITE << "|" << RED << "2.--." << WHITE << " ||" << BLACK << "4.--. " << WHITE << "| " << RED << ".-.    " << WHITE << "|" << BLACK << "S.--. " << WHITE << "||" << RED << "O.--. " << WHITE << "||" << RED << "L.--. " << WHITE << "||" << BLACK << "V.--. " << WHITE << "||" << BLACK << "E.--. " << WHITE << "||" << RED << "R.--. " << WHITE << "|" << RESET << endl; 
	cout << WHITE << "| " << RED << "(\\/)" << WHITE << " ||" << BLACK << " :/\\: " << WHITE << "|" << RED << "((5))   " << WHITE << "|" << BLACK << " :/\\:" << WHITE << " ||" << RED << " :/\\: " << WHITE << "||" << RED << " :/\\:" << WHITE << " ||" << BLACK << " :(): " << WHITE << "||" << BLACK << " (\\/)" << WHITE << " ||" << RED << " :(): " << WHITE << "|" << RESET << endl;
	cout << WHITE << "| " << RED << ":\\/:" << WHITE << " ||" << BLACK << " :\\/: " << WHITE << "|" << RED << " '-.-.  " << WHITE << "|" << BLACK << " :\\/:" << WHITE << " ||" << RED << " :\\/: " << WHITE << "||" << RED << " (__) " << WHITE << "||" << BLACK << " ()() " << WHITE << "||" << BLACK << " :\\/:" << WHITE << " ||" << RED << " ()() " << WHITE << "|" << RESET << endl;
	cout << WHITE << "| " << RED << "'--'2" << WHITE << "|| " << BLACK << "'--'4" << WHITE << "|  " << RED << "((1)) " << WHITE << "|" << BLACK << " '--'S" << WHITE << "||" << RED << " '--'O" << WHITE << "||" << RED << " '--'L" << WHITE << "||" << BLACK << " '--'V" << WHITE << "||" << BLACK << " '--'E" << WHITE << "||" << RED << " '--'R" << WHITE << "|" << RESET << endl;
	cout << WHITE << "`------'`------'" << RED << "   '-'" << WHITE << "  `------'`------'`------'`------'`------'`------'" << RESET << endl << endl;
}

void command1() {
	/* LIST COMMAND 1 */

	cout << WHITE << "==========================================" << RESET << endl;
    cout << RED <<   "=               START/EXIT               =" << RESET << endl;
    cout << WHITE << "==========================================" << RESET << endl;
    cout << RED << "[1]" << WHITE << " START" << RESET << endl;
    cout << RED << "[2]" << WHITE << " EXIT" << RESET << endl;
}

void command2() {
	/* LIST COMMAND 2 */

	cout << WHITE << "==========================================" << RESET << endl;
    cout << RED <<   "=              List Command              =" << RESET << endl;
    cout << WHITE << "==========================================" << RESET << endl;
    cout << RED << "[1]" << WHITE << " Input 4 Cards [A, 2, ..., Q, K]" << RESET << endl;
    cout << RED << "[2]" << WHITE << " Generate 4 Random Cards" << RESET << endl;
}

void command3() {
	/* LIST COMMAND 3 */

	cout << endl << WHITE << "==========================================" << endl;
    cout << RED <<   "=  Where do you want to see the result?  =" << endl;
    cout << WHITE << "==========================================" << endl;
    cout << RED << "[1]" << WHITE <<" Console" << endl;
    cout << RED << "[2]" << WHITE <<" File" << endl;
}

void app() {
	/* APP */

	int input;
	vector <int> numbers;

	cout << endl;
	command2();

	input = inputOneTwo();
	if (input == 1) {
		numbers = solver1();
	} else {
		numbers = solver2();
		cout << endl << GREEN << "Your cards are: " << RESET;
		for (auto x:numbers) {
			cout << numToString(x) << " ";
		}
		cout << endl;
	}

	/* Execution Time Init */
	typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::nanoseconds ns;
    typedef std::chrono::duration<float> fsec;
    auto t0 = Time::now();

	vector <vector<int>> permute_numbers = permute(numbers);
	vector <vector<int>> hasil;

	char operators[4] = { '+', '-', '*', '/' };

	for (int i = 0; i < 4; i ++) {
		for (int j = 0; j < 4; j ++) {
			for (int k = 0; k < 4; k ++) {
				for (int x = 0; x < 24; x ++) {
					int a = permute_numbers[x][0];
					int b = permute_numbers[x][1];
					int c = permute_numbers[x][2];
					int d = permute_numbers[x][3];

					// (N OP N) OP (N OP N)
					if (absolute(func(func(a, operators[i], b), operators[j], func(c, operators[k], d)) - 24) < FLT_EPSILON) {
						hasil.push_back({0, a, opToInt(operators[i]), b, opToInt(operators[j]), c, opToInt(operators[k]), d});
					}
					
					// ((N OP N) OP N) OP N
					if (absolute(func(func(func(a, operators[i], b), operators[j], c), operators[k], d) - 24) < FLT_EPSILON) {
						hasil.push_back({1, a, opToInt(operators[i]), b, opToInt(operators[j]), c, opToInt(operators[k]), d});
					}

					// (N OP (N OP N)) OP N
					if (absolute(func(func(a, operators[i], func(b, operators[j], c)), operators[k], d) - 24) < FLT_EPSILON) {
						hasil.push_back({2, a, opToInt(operators[i]), b, opToInt(operators[j]), c, opToInt(operators[k]), d});
					}

					// N OP (N OP (N OP N)) 
					if (absolute(func(a, operators[i], func(b, operators[j], func(c, operators[k], d))) - 24) < FLT_EPSILON) {
						hasil.push_back({3, a, opToInt(operators[i]), b, opToInt(operators[j]), c, opToInt(operators[k]), d});
					} 

					// N OP ((N OP N) OP N)
					if (absolute(func(a, operators[i], func(func(b, operators[j], c), operators[k], d)) - 24) < FLT_EPSILON) {
						hasil.push_back({4, a, opToInt(operators[i]), b, opToInt(operators[j]), c, opToInt(operators[k]), d});
					}
				}
			}
		}
	}

	set <vector<int>> s( hasil.begin(), hasil.end() );
	hasil.assign( s.begin(), s.end() );

	auto t1 = Time::now();
    fsec fs = t1 - t0;
    ns exec = std::chrono::duration_cast<ns>(fs);

	command3();
    int input2;

	input2 = inputOneTwo();

	if (input2 == 1) {
		cout << endl << GREEN << s.size() << " Solutions Found" << RESET << endl;

		std::set< std::vector<int> >::iterator it;
		for (it = s.begin(); it != s.end(); it++) {
			const std::vector<int>& x = (*it);
			switch (x[0]) {
				case 0:
					cout << "(" << numToString(x[1]) << " " << operators[x[2]] << " " << numToString(x[3]) << ") " << operators[x[4]] << " (" << numToString(x[5]) << " " << operators[x[6]] << " " << numToString(x[7]) << ")" << endl;
					break;
				case 1:
					cout << "(("<< numToString(x[1]) << " " << operators[x[2]] << " " << numToString(x[3]) << ") " << operators[x[4]] << " " << numToString(x[5]) << ") " << operators[x[6]] << " " << numToString(x[7]) << endl;
					break;
				case 2:
					cout << "(" << numToString(x[1]) << " " << operators[x[2]] << " (" << numToString(x[3]) << " " << operators[x[4]] << " " << numToString(x[5]) << ")) " << operators[x[6]] << " " << numToString(x[7]) << endl;
					break;
				case 3:
					cout << numToString(x[1]) << " " << operators[x[2]] << " " << "(" << numToString(x[3]) << " " << operators[x[4]] << " (" << numToString(x[5]) << " " << operators[x[6]] << " " << numToString(x[7]) << "))" << endl;
					break;
				case 4:
					cout << numToString(x[1]) << " " << operators[x[2]] << " ((" << numToString(x[3]) << " " << operators[x[4]] << " " << numToString(x[5]) << ") " << operators[x[6]] << " " << numToString(x[7]) << ")" << endl;
					break;
			}
		}
	} else {
		string filename;

		cout << endl << "Input Filename: ";
		cin >> filename;

		ofstream MyFile("../test/" + filename + ".txt");

		// Write ke file
		MyFile << s.size() << " solutions found" << endl;

		std::set< std::vector<int> >::iterator itr;
		for (itr = s.begin(); itr != s.end(); itr++) {
			const std::vector<int>& x = (*itr);
			switch (x[0]) {
				case 0:
					MyFile << "(" << numToString(x[1]) << " " << operators[x[2]] << " " << numToString(x[3]) << ") " << operators[x[4]] << " (" << numToString(x[5]) << " " << operators[x[6]] << " " << numToString(x[7]) << ")" << endl;
					break;
				case 1:
					MyFile << "(("<< numToString(x[1]) << " " << operators[x[2]] << " " << numToString(x[3]) << ") " << operators[x[4]] << " " << numToString(x[5]) << ") " << operators[x[6]] << " " << numToString(x[7]) << endl;
					break;
				case 2:
					MyFile << "(" << numToString(x[1]) << " " << operators[x[2]] << " (" << numToString(x[3]) << " " << operators[x[4]] << " " << numToString(x[5]) << ")) " << operators[x[6]] << " " << numToString(x[7]) << endl;
					break;
				case 3:
					MyFile << numToString(x[1]) << " " << operators[x[2]] << " " << "(" << numToString(x[3]) << " " << operators[x[4]] << " (" << numToString(x[5]) << " " << operators[x[6]] << " " << numToString(x[7]) << "))" << endl;
					break;
				case 4:
					MyFile << numToString(x[1]) << " " << operators[x[2]] << " ((" << numToString(x[3]) << " " << operators[x[4]] << " " << numToString(x[5]) << ") " << operators[x[6]] << " " << numToString(x[7]) << ")" << endl;
					break;
			}
		}

		// Close file
		MyFile.close();

		cout << GREEN << "File saved succesfully" << RESET << endl;
	}

	cout << GREEN << "Execution Time: " << RESET << exec.count() << " nanoseconds" << endl;
	cout << GREEN << "Execution Time: " << RESET << exec.count() / 1000 << " microseconds" << endl;


}

int main () {
	/* Main Program */

	int startInput;

	splash();
	cout << "Welcome to 24 Cards Solver ><" << endl;
	command1();

	startInput = inputOneTwo();

	while (startInput == 1) {
		app();

		cout << endl << GREEN << "Do you want to try again?" << RESET << endl << endl;
		command1();
		startInput = inputOneTwo();
	}

	cout << endl << GREEN << "Thank You ><" << RESET << endl; 
	exit(0);

	return 0;
}