#include <fstream>
#include <iostream>
#include <list>
#include<sstream>  
using namespace std;

class gcodeclass
{
public:

	gcodeclass();
	~gcodeclass();
	list<string> letter;
	int pointer = 0;
	double size = 20;
	int xn = 0;
	int yn = 0;
	string getgcode(string s, int x, int y) {
		string ans;
		ans = "";
		xn = x;
		yn = y;
		for (int ii = 0; ii < s.length(); ii++) {
			string k = s.substr(ii, 1);
			for (int i = 0; i < letter.size(); i++)
			{
				if (get(letter, i) == k) {
					ans += getwithindex(i, xn, yn);
					//break;
				}
			}
		}
		return ans;
	}
	string get(list<string> _list, int _i) {
		list<string>::iterator it = _list.begin();
		for (int i = 0; i < _i; i++) {
			++it;
		}
		return *it;
	}
	string getfirst(int x, int y) {
		string sk = "G28\nM280 P0 S0\n";
		sk += "G1 X" + to_string(x) + " Y" + to_string(y) + "\n";
		return sk;
	}
	string getwithindex(int i, int x, int y) {
		// setting position
		string ans = "M280 P0 S0\n";
		ans += "G1 X" + to_string(x) + " Y" + to_string(y) + "\n";
		ans += "M280 P0 S50\n";
		//file << "G1 X" << x + 5 << " Y" << y + 20 << "\n";
		//file << "G1 X" << x + 10 << " Y" << y << "\n";
		if (i == 0) {
			//A
			// drawing two lines like this /\
			//"\nM280 P0 S50
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y) + "\n";
			//moving pointer back
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 6) + " Y" + to_string(y + size / 3) + "\n";
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size * 5 / 6) + " Y" + to_string(y + size / 3) + "\n";

		}
		else if (i == 1)
		{
			//B
			//drawline from y to y+size
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//draw line 1 -
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			// draw arc like ) to point in y+size/2
			int idsty = y + size / 2 - (y + size);
			ans += "G2 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + " I" + to_string(size * 3 / 24) + " J" + to_string(idsty / 2) + "\n";
			//
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size / 2) + "\n";
			//

			//
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + "\n";
			//draw second arc
			idsty = y - (y + size / 2);
			ans += "G2 X" + to_string(x + size / 2) + " Y" + to_string(y) + " I" + to_string(size * 3 / 24) + " J" + to_string(idsty / 2) + "\n";
			//
			ans += "G1 X" + to_string(x) + " Y" + to_string(y) + "\n";
		}
		else if (i == 2) {
			//C
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			//ans += "G1 X" + to_string(x+size) + " Y" + to_string(y + size) + "\n";
			// draw arc like ) to point in y+size/2
			int idsty = y - (y + size);
			//int idstx = x   - (x + size);
			ans += "G3 X" + to_string(x + size) + " Y" + to_string(y) + " I" + to_string(-size * 3 / 12) + " J" + to_string(idsty / 2) + "\n";


		}
		else if (i == 3) {
			//D
			//drawline from y to y+size
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//draw line 2
			int idsty = y - (y + size);
			//int idstx = x   - (x + size);
			ans += "G2 X" + to_string(x) + " Y" + to_string(y) + " I" + to_string(size * 3 / 12) + " J" + to_string(idsty / 2) + "\n";

		}
		else if (i == 4) {
			//E
			//Draw line |
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//line 2 -
			ans += "G1 X" + to_string(x + size * 3 / 4) + " Y" + to_string(y + size) + "\n";
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size / 2) + "\n";
			//
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size * 3 / 4) + " Y" + to_string(y + size / 2) + "\n";
			//
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y) + "\n";
			//
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size * 3 / 4) + " Y" + to_string(y) + "\n";
		}
		else if (i == 5) {
			//F
			//same E without last line
			//Draw line |
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//line 2 -
			ans += "G1 X" + to_string(x + size * 3 / 4) + " Y" + to_string(y + size) + "\n";
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size / 2) + "\n";
			//
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size * 3 / 4) + " Y" + to_string(y + size / 2) + "\n";
			//
		}
		else if (i == 6) {
			//G
			// same C + two lines
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			//ans += "G1 X" + to_string(x+size) + " Y" + to_string(y + size) + "\n";
			// draw arc like ) to point in y+size/2
			int idsty = y - (y + size);
			//int idstx = x   - (x + size);
			ans += "G3 X" + to_string(x + size) + " Y" + to_string(y) + " I" + to_string(-size * 3 / 12) + " J" + to_string(idsty / 2) + "\n";
			// line two
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size / 2) + "\n";
			//line three
			ans += "G1 X" + to_string(x + size * 2 / 3) + " Y" + to_string(y + size / 2) + "\n";
		}
		else if (i == 7) {
			//H
			//Draw line |
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size / 2) + "\n";
			//line 2
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size / 2) + "\n";
			//change position again :(
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
			//draw last line
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y) + "\n";
		}
		else if (i == 8) {
			//I
			//one line in the middle
			//change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y) + "\n";

		}
		else if (i == 9) {
			//J
			//change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size * 1 / 3) + "\n";
			// circle
			int idstx = x + size / 2 - (x);
			//int idstx = x   - (x + size);
			ans += "G2 X" + to_string(x) + " Y" + to_string(y + size * 1 / 3) + " I" + to_string(-idstx / 2) + " J" + to_string(0) + "\n";
		}
		else if (i == 10)
		{
			//K
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size / 2) + "\n";
			//line 2
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size / 2) + "\n";
			//line 3
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y) + "\n";

		}
		else if (i == 11)
		{
			//L
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y) + "\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y) + "\n";
		}
		else if (i == 12) {
			//M
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y) + "\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size / 2) + "\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y) + "\n";
		}
		else if (i == 13) {
			//N like M without last line
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y) + "\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
		}
		else if (i == 14) {
			//O
			// C and D together
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			//ans += "G1 X" + to_string(x+size) + " Y" + to_string(y + size) + "\n";
			// draw arc like ) to point in y+size/2
			int idsty = y - (y + size);
			//int idstx = x   - (x + size);
			ans += "G3 X" + to_string(x + size / 2) + " Y" + to_string(y) + " I" + to_string(-size * 1 / 24) + " J" + to_string(idsty / 2) + "\n";
			//D
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			//draw arc
			idsty = y - (y + size);
			ans += "M280 P0 S50\n";
			//int idstx = x   - (x + size);
			ans += "G2 X" + to_string(x + size / 2) + " Y" + to_string(y) + " I" + to_string(size * 1 / 24) + " J" + to_string(idsty / 2) + "\n";

		}
		else if (i == 15) {
			//p =B without last arc
				 //drawline from y to y+size
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//draw line 1 -
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			// draw arc like ) to point in y+size/2
			int idsty = y + size / 2 - (y + size);
			ans += "G2 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + " I" + to_string(size * 3 / 24) + " J" + to_string(idsty / 2) + "\n";
			//
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size / 2) + "\n";
			//

		}
		else if (i == 16) {
			// Q
			// same O but with a line
					//O
			// C and D together
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			//ans += "G1 X" + to_string(x+size) + " Y" + to_string(y + size) + "\n";
			// draw arc like ) to point in y+size/2
			int idsty = y - (y + size);
			//int idstx = x   - (x + size);
			ans += "G3 X" + to_string(x + size / 2) + " Y" + to_string(y) + " I" + to_string(-size * 1 / 24) + " J" + to_string(idsty / 2) + "\n";
			//D
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			//draw arc
			idsty = y - (y + size);
			ans += "M280 P0 S50\n";
			//int idstx = x   - (x + size);
			ans += "G2 X" + to_string(x + size / 2) + " Y" + to_string(y) + " I" + to_string(size * 1 / 24) + " J" + to_string(idsty / 2) + "\n";
			//change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + "\n";
			//line
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y) + "\n";
		}
		else  if (i == 17) {
			//R
			//P with a line \ so R
					//p =B without last arc
			 //drawline from y to y+size
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//draw line 1 -
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			// draw arc like ) to point in y+size/2
			int idsty = y + size / 2 - (y + size);
			ans += "G2 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + " I" + to_string(size * 3 / 24) + " J" + to_string(idsty / 2) + "\n";
			//
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size / 2) + "\n";
			//
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y) + "\n";
		}
		else if (i == 18) {
			//S how? :)
			// draw C then change position and draw D without |
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			//ans += "G1 X" + to_string(x+size) + " Y" + to_string(y + size) + "\n";
			// draw arc like ) to point in y+size/2
			int idsty = y + size / 2 - (y + size);
			//int idstx = x   - (x + size);
			ans += "G3 X" + to_string(x + size) + " Y" + to_string(y + size / 2) + " I" + to_string(-size * 3 / 12) + " J" + to_string(idsty / 2) + "\n";
			//CHANGE POSITION
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + "\n";
			ans += "M280 P0 S50\n";
			idsty = y - (y + size / 2);
			//int idstx = x   - (x + size);
			ans += "G2 X" + to_string(x + size / 2) + " Y" + to_string(y) + " I" + to_string(size * 3 / 12) + " J" + to_string(idsty / 2) + "\n";

		}
		else if (i == 19) {
			//T
			//one line in the middle
			//change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y) + "\n";
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			//one horizontal line
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
		}
		else if (i == 20) {
			//U
			//J WITH ONE MORE LINE
			//change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size * 1 / 3) + "\n";
			// circle
			int idstx = x + size / 2 - (x);
			//int idstx = x   - (x + size);
			ans += "G2 X" + to_string(x) + " Y" + to_string(y + size * 1 / 3) + " I" + to_string(-idstx / 2) + " J" + to_string(0) + "\n";
			//line 2
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
		}
		else if (i == 21) {
			//V TWO SIMPLE LINES \/
			// change positon
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y) + "\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
		}
		else if (i == 22) {
			//W 
			// change positon
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			//LINES
			ans += "G1 X" + to_string(x) + " Y" + to_string(y) + "\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + "\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y) + "\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
		}
		else if (i == 23) {
			//X
			//LINE 1
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
			//Change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
		}
		else if (i == 24)
		{
			//Y
			//change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			//LINE 1
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + "\n";
			//LINE 2
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
			//CHANGE POSITION
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y + size / 2) + "\n";
			ans += "M280 P0 S50\n";
			//
			//DRAW LAST LINE
			ans += "G1 X" + to_string(x + size / 2) + " Y" + to_string(y) + "\n";
		}
		else if (i == 25) {
			//Z
			//change position
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y + size) + "\n";
			ans += "M280 P0 S50\n";
			//Simple lines
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y + size) + "\n";
			ans += "G1 X" + to_string(x) + " Y" + to_string(y) + "\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y) + "\n";
		}
		else if (i == 26) {
			ans += "M280 P0 S0\n";
			ans += "G1 X" + to_string(x + size) + " Y" + to_string(y) + "\n";
		}

		xn += size;
		return ans;
	}
private:

};

gcodeclass::gcodeclass()
{
	letter.push_back("A");
	letter.push_back("B");
	letter.push_back("C");
	letter.push_back("D");
	letter.push_back("E");
	letter.push_back("F");
	letter.push_back("G");
	letter.push_back("H");
	letter.push_back("I");
	letter.push_back("J");
	letter.push_back("K");
	letter.push_back("L");
	letter.push_back("M");
	letter.push_back("N");
	letter.push_back("O");
	letter.push_back("P");
	letter.push_back("Q");
	letter.push_back("R");
	letter.push_back("S");
	letter.push_back("T");
	letter.push_back("U");
	letter.push_back("V");
	letter.push_back("W");
	letter.push_back("X");
	letter.push_back("Y");
	letter.push_back("Z");
	letter.push_back(" ");
}

gcodeclass::~gcodeclass()
{
}
/*
Q
R
S
T
U
V
W
X
Y
Z
*/
int main() {

	int x;
	int y;
	cout << "Gruppe 34 Aufgabe 1 \nKhaled Aldukhur(408309) \nMarwa Ashour(411109) \nSebastian Maximilian Bernhard Redemann(456703)\n";
	cout << "Please input X and Y Coordinates:\n";
	cout << "X : ";
	cin >> x;
	cout << "\nY : ";
	cin >> y;
	string data = "A B C D";
	cout << "\nfile name : ";
	//cin >> data;
	gcodeclass gc;
	string k = gc.getfirst(x, y) + gc.getgcode(data, x, y);
	x = gc.xn;
	string path = "";
	cin >> path;
	fstream file(path, ios::out);
	file << k;
}