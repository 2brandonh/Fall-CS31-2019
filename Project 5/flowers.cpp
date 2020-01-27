#pragma warning(disable:6262)
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cctype>
#include "utilities.h"
#include <cstring>

using namespace std;
const int MAXWORDS = 10000;

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum); //words[wordnum] as the mystery word

int main() {
	char WORDLIST[MAXWORDS][MAXWORDLEN + 1];
	const char WORDFILENAME[] = "C:/Users/2bran/Desktop/CS31/Project5/words.txt";
	int nWords = getWords(WORDLIST, MAXWORDS, WORDFILENAME); //set nWords to the number of items put into WORDLIST

	if (nWords < 1) {
		cout << "No words were loaded, so I can't play the game.";
		return -1;
	}

	int minimum, maximum;
	double total;
	int rounds;
	cout << "How many rounds do you want to play? ";
	cin >> rounds;
	cin.ignore(10000, '\n'); //clean buffer

	if (rounds <= 0) {
		cout << "The number of rounds must be positive.";
		return -1;
	}

	for (int i = 1; i <= rounds; i++) {
		int rand = randInt(0, nWords - 1);

		cout << "\nRound " << i << '\n';
		cout << "The mystery word is " << strlen(WORDLIST[rand]) << " letters long.\n"; //get length of random word through strlen
		int score = playOneRound(WORDLIST, nWords, rand); //playOneRound returns score
		if (score == 1) //one try vs multiple
			cout << "You got it in " << score << " try.\n";
		else
			cout << "You got it in " << score << " tries.\n";

		if (i == 1) { //since round is 1, initialize variables to the output of the first round
			minimum = score;
			maximum = score;
			total = score;
		}
		else { //if round is not 1, compare max, min, and compute avg
			if (score > maximum)
				maximum = score;
			if (score < minimum)
				minimum = score;
			total += score;
		}

		cout.setf(ios::fixed);
		cout.precision(2); //set to 2 decimal places fixed
		cout << "Average: " << total / i << ", minimum: " << minimum << ", maximum: " << maximum << endl;
	}
	return 0;
}

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) {
	if (wordnum >= nWords || wordnum < 0 || nWords <= 0)
		return -1;

	int score = 0;
	char trial[1000]; //larger size to accomodate words greater than 6 chars
	char original[1000];
	int temp_trial[6], temp_org[6];
	strcpy(original, words[wordnum]);
	//cerr << original << '\n';

	for (;;) {
		int flowers = 0, bees = 0;
		for (int i = 0; i < 6; i++) { //initializer for my set to check for if an element has already been used or not, 0 is not used, 1 is used
			temp_trial[i] = 0;
			temp_org[i] = 0;
		}
		int checker = 0; //checks to see if it should loop back to trial Word again

		cout << "Trial word: ";
		cin.getline(trial, 10000);
		if (strlen(trial) > 6 || strlen(trial) < 4) {
			cout << "Your trial word must be a word of 4 to 6 lower case letters.\n"; //note 4-6 letters takes priority here
			checker = 1;
		}

		if (checker != 1) {
			for (int i = 0; i < strlen(trial); i++) {
				if (!(islower(trial[i]))) {
					cout << "Your trial word must be a word of 4 to 6 lower case letters.\n";
					checker = 1;
					break;
				}
			}
		}

		if (checker != 1) {
			for (int i = 0; i < nWords; i++) {
				if (strcmp(trial, words[i]) == 0) //need strcmp as cannot directly compare arrays
					break;
				if (i + 1 == nWords) { //just write on outside of for loop!
					cout << "I don't know that word.\n";
					checker = 1;
					break;
				}
			}
		}


		if (checker == 1)
			continue;

		score++;
		if (strcmp(original, trial) == 0)
			return score;

		/*bees and flowers check
		CHECK IF ORIGINAL GREATER THAN TRIAL
		1. check for flowers by same pos
		2. check for bees by incrementing in a nested for loop
		3. if at any time there is a match, change the position of the match in the temp_org and temp_trial arrays to 1, marking them
		*/

		for (int i = 0; i < strlen(original) && i < strlen(trial); i++) { //flower checker, checks corresponding and the && condition is to make sure there is no undefined behavior outside the array
			if (original[i] == trial[i]) {
				flowers++;
				temp_org[i] = 1;
				temp_trial[i] = 1;
			}
		}

		for (int i = 0; i < strlen(original); i++) { //bees checker
			if (temp_org[i] == 1)
				continue;
			for (int j = 0; j < strlen(trial); j++) {
				if (original[i] == trial[j] && temp_trial[j] != 1) { //making sure it is not a duplicate with != 1
					temp_org[i] = 1;
					temp_trial[j] = 1;
					bees++;
					break;
				}
			}
		}
		cout << "Flowers: " << flowers << ", Bees: " << bees << endl;
	}
	return 0;
}