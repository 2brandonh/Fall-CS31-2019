#include "grid.h"
#include <cctype>
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0;
const int BG = 1;

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
void plotHorizontalLine(int r, int c, int distance, char ch, int fgbg);
void plotVerticalLine(int r, int c, int distance, char ch, int fgbg);
int performCommands(string commandString, char& plotChar, int& mode, int& badPos);
//bool isCMD(char ch);

int main()
{
	setSize(20, 30);
	clearGrid();
	char currentChar = '*';
	int currentMode = FG;
	for (;;)
	{
		cout << "Enter a command string: ";
		string cmd;
		getline(cin, cmd);
		if (cmd == "")
			break;
		int position;
		int status = performCommands(cmd, currentChar, currentMode, position);
		switch (status)
		{
		case 0:
			draw();
			break;
		case 1:
			cout << "Syntax error at position " << position + 1 << endl;
			break;
		case 2:
			cout << "Cannot perform command at position " << position + 1 << endl;
			break;
		default:
			// It should be impossible to get here.
			cerr << "performCommands returned " << status << "!" << endl;
		}
	}
}

//horizontal line checks if distance is negative or positive, then FG or BG before plotting
void plotHorizontalLine(int r, int c, int distance, char ch, int fgbg) { 
	if (distance > 0) {
		for (int i = 0; i <= distance; i++) {
			if (fgbg == FG || getChar(r, c + i) == ' ')
				setChar(r, c + i, ch);
		}
	}
	else {
		for (int i = 0; i >= distance; i--) {
			if (fgbg == FG || getChar(r, c + i) == ' ')
				setChar(r, c + i, ch);
		}
	}
}

//vertical line checks if distance is negative or positive, then FG or BG before plotting
void plotVerticalLine(int r, int c, int distance, char ch, int fgbg) {
	if (distance > 0) {
		for (int i = 0; i <= distance; i++) {
			if (fgbg == 0)
				setChar(r + i, c, ch);
			else if (getChar(r + i, c) == ' ')
				setChar(r + i, c, ch);
		}
	}
	else {
		for (int i = 0; i >= distance; i--) {
			if (fgbg == 0)
				setChar(r + i, c, ch);
			else if (getChar(r + i, c) == ' ')
				setChar(r + i, c, ch);
		}
	}
}

bool VerticalCheck(int r, int c, int distance) { //will return true if outside vertical boundaries
	if (((c <= 0) || (r + distance > getRows()) || (r + distance <= 0) || (r <= 0) || (r > getRows()) || (c > getCols())))
		return 1;
	else
		return 0;
}

bool HorizontalCheck(int r, int c, int distance) { //will return true if outside horizontal boundaries
	if (((r <= 0) || (c + distance > getCols()) || (c + distance <= 0) || (c <= 0) || (c > getCols()) || (r > getRows())))
		return 1;
	else
		return 0;
}

//checks if character is a command character (eventually not used)

//bool isCMD(char ch) { 
//	if (toupper(ch) == 'H' || toupper(ch) == 'V' || toupper(ch) == 'B' || toupper(ch) == 'F' || toupper(ch) == 'C')
//		return 1;
//	else
//		return 0;
//}

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg) {

	//initial checks for direction, printable character, FG/BG
	if (dir != HORIZ && dir != VERT)
		return 0;
	if (!isprint(plotChar))
		return 0;
	if (fgbg != FG && fgbg != BG)
		return 0;

	//check if line will reach out of bounds before actually plotting in HORIZ and VERT
	if (dir == HORIZ) {
		if (HorizontalCheck(r, c, distance))
			return 0;
		else {
			plotHorizontalLine(r, c, distance, plotChar, fgbg);
			return 1;
		}
	}

	if (dir == VERT) {
		if (VerticalCheck(r, c, distance))
			return 0;
		else {
			plotVerticalLine(r, c, distance, plotChar, fgbg);
			return 1;
		}
	}

	return 0;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
	int CUR_ROW = 1;
	int CUR_COL = 1;
	bool CMDErrorlogged = 0; //If set to 1, logs a command error and returns to it if there are no syntax errors
	string s = commandString;
	string temp;
	string substring;

	for (int i = 0; i != s.size();) { //for loop until every character is read
		int counter = 0;
		int numdigits = 0;

		if (toupper(s[i]) == 'H') {
			i++; //shifts onto the number after command H

			if (s[i] == '-') { //checking if negative number first before reading numbers
				if (!isdigit(s[i + 1])) {
					badPos = i + 1;
					return 1;
				}
				counter++;
			}
			else if (!isdigit(s[i])) {
				badPos = i;
				return 1;
			}

			while (isdigit(s[i + counter])) {
				numdigits++;
				counter++;
				if (numdigits == 3) { //3 digits automatically tells you a syntax error
					badPos = i + counter - 1;
					//cerr << "error 1 with H";
					return 1;
				}
				if (i + counter == s.size()) //break out of while loop or s[i + counter] will be out of bounds
					break;
			}

			int length = 0;
			temp = s;
			substring = temp.substr(i, counter); //convert to a substring and convert the numbers following the command to an int
			for (int n = 0; n < counter; n++) { 
				if (substring[n] == '-') {
					continue;
				}
				length *= 10;
				length += substring[n] - '0';
			}
			if (substring[0] == '-') {
				length *= -1;
			}

			if (HorizontalCheck(CUR_ROW, CUR_COL, length)) { //need to check CUR ROW AND COL for out of bounds
				//badPos = i - 1;
				//cerr << "error 2";
				if (CMDErrorlogged == 0) {
					badPos = i - 1;
					CMDErrorlogged = 1;
				}
				//return 2;
			}

			plotLine(CUR_ROW, CUR_COL, length, HORIZ, plotChar, mode);
			CUR_COL += length;
			i += counter; //shifts i to the next command to read

		}
		else if (toupper(s[i]) == 'V') { //I INDICATES THE COMMAND IN STRING INDEX
			i++;

			if (s[i] == '-') {
				if (!isdigit(s[i + 1])) {
					badPos = i + 1;
					return 1;
				}
				counter++;
				//numdigits--; do not need this since counter++ already scales it forwards
			}
			else if (!isdigit(s[i])) {
				badPos = i;
				return 1;
			}

			while (isdigit(s[i + counter])) {
				numdigits++;
				counter++;
				if (numdigits == 3) {
					badPos = i + counter - 1;
					//cerr << "error 1 with H";
					return 1;
				}
				if (i + counter == s.size())
					break;
			}

			int length = 0;
			temp = s;
			substring = temp.substr(i, counter);
			for (int n = 0; n < counter; n++) {
				if (substring[n] == '-') {
					continue;
				}
				length *= 10;
				length += substring[n] - '0';
			}
			if (substring[0] == '-') {
				length *= -1;
			}

			if (VerticalCheck(CUR_ROW, CUR_COL, length)) { //need to check CUR ROW AND COL for out of bounds
				//badPos = i - 1;
				//cerr << "error 2";
				if (CMDErrorlogged == 0) {
					badPos = i - 1;
					CMDErrorlogged = 1;
				}
				//return 2;
			}

			plotLine(CUR_ROW, CUR_COL, length, VERT, plotChar, mode);
			CUR_ROW += length;
			i += counter;

		}
		else if (toupper(s[i]) == 'C') {
			i++;
			clearGrid(); //clears grid and sets to default settings
			CUR_COL = 1, CUR_ROW = 1;
			plotChar = '*';
			mode = FG;
		}
		else if (toupper(s[i]) == 'B') {
			i++;
			if (isprint(s[i])) { //checks if the next character is printable then changes mode
				plotChar = s[i];
				mode = BG;
				i++;
			}
			else {
				badPos = i;
				return 1;
			}
		}
		else if (toupper(s[i]) == 'F') {
			i++;
			if (isprint(s[i])) {
				plotChar = s[i];
				mode = FG;
				i++;
			}
			else {
				badPos = i;
				return 1;
			}
		}
		else { //if the command is not one in the specs, return syntax error
			badPos = i;
			return 1;
		}
	}
	if (CMDErrorlogged == 1) { //prints out first cannot perform command error if this was logged
		return 2;
	}
	return 0; //draw
}








//check for commands then if not possible inputs
//check at the beginning if not a command