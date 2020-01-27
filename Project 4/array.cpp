#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

int main() {

	//string a[7] = { "mick", "jack", "fiona", "marie", "mick", "gordon", "lindsey" };
	//string b[7] = { "bill", "gordon", "fiona", "rudy", "", "jack", "rudy" };
	//string num[6] = { "1", "4", "2", "64", "4", "7"};
	//cerr << separate(num, 6, "4")  << endl;
	//for (int test = 0; test < 6; test++) {
	//		cerr << num[test] << " ";
	//	}
	//	cerr << endl;
	//return 0;


	//////string h[7] = { "john", "nancy", "nancy", "marie", "", "gordon", "john" };
	//////string g[4] = { "nancy", "nancy", "boo", "nancy" };
	//////cerr << appendToAll(h, 7, "bye"); //works with 0 and between and max
	//////cerr << lookup(h, 7, "fiona"); //works with 0 and between and max
	//////cerr << positionOfMax(h, 7); //works with and between and max
	//////cerr << rotateLeft(h, 6, 3); //works with 0 and between and max
	//////cerr << countRuns(h, 4); //works with 0 and between and max
	//////cerr << flip(h, 1); //works with 0 and between and max
	//////cerr << differ(g, 4, g, 1); //works with 0 and between and max
	//////cerr << subsequence(h, 3, g, 2); //works with 0 and between and max
	//////cerr << lookupAny(h, 7, g, 4); //works with 0 and between and max
	//////string test[10] = { "1", "1", "1", "5", "2", "6", "9", "8", "2", "3" };
	//////string test2[4] = { "3", "7", "2", "1" };
	//////cerr << separate(test, 3, "3"); //works with 0 and between and max

	//return 0;
}

int appendToAll(string a[], int n, string value) {
	if (n < 0)
		return -1;
	for (int i = 0; i <= n - 1; i++) { //add value up to n - 1 interesting elements
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target) {
	if (n < 0)
		return -1;
	for (int i = 0; i <= n - 1; i++) { //returns first index for a string the same as target
		if (target == a[i])
			return i;
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	if (n < 0)
		return -1;
	if (n == 0)
		return -1;

	int current_max = 0;

	for (int i = 0; i <= n - 1; i++) {  //nested for loop to check for postion of largest string
		for (int j = 0; j <= n - 1; j++) { 
			if (a[i] < a[j])
				break;
			if (j + 1 > n - 1) {
				if (a[i] != a[current_max]) //!= ensures that the first of duplicates is returned
					current_max = i;
			}
		}
	}
	return current_max;
}

int rotateLeft(string a[], int n, int pos) { //return -1?
	if (n < 0)
		return -1;
	if (n == 0)
		return -1;
	if (pos > n - 1)
		return -1;

	string temp;
	temp = a[pos];
	for (int i = pos; i < n - 1; i++) { //temp variable holds string, shift everything left, put temp into last interesting element
		a[i] = a[i + 1];
	}
	a[n - 1] = temp;
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0)
		return -1;
	int checker[1000];
	for (int i = 0; i < 1000; i++) { //make an array to test for duplicates
		checker[i] = 0;
	}
	int sequences = 0;

	for (int i = 0; i <= n - 1; i++) {
		if (checker[i] == 1) //marking as one sets the number as checked
			continue;
		checker[i] = 1;
		for (int j = 0; j <= n - 1; j++) {
			if (a[i] == a[j]) //if same as the current number being checked, mark the number as checked in the array, this marks the sequence as checked
				checker[j] = 1;
		}
		sequences++;
	}
	return sequences;
}

int flip(string a[], int n) {
	if (n < 0)
		return -1;
	if (n == 0)
		return 0;
	string temp;
	for (int i = 0; i < n / 2; i++) { //the number of flips needed is equal to n/2, truncated 
		temp = a[i];
		a[i] = a[n - 1 - i];
		a[n - 1 - i] = temp;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return -1;
	if (n1 == 0 || n2 == 0) //since you can't compare to something that has NO VALUE at all, 0 will be a parameter error
		return -1;

	for (int i = 0; i < n1 && i < n2; i++) { //repeat until one interesting element list is at the end
		if (a1[i] != a2[i])
			return i;
	}
	if (n1 <= n2)
		return n1;
	else
		return n2;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return -1;
	if (n2 == 0)
		return 0;
	if (n1 < n2)
		return -1;

	for (int i = 0; i <= n1 - 1; i++) {
		if (a1[i] != a2[0]) //initial check to see if item is the same as the start of a2
			continue;
		for (int j = 0; ; j++) {
			if (a1[i + j] != a2[j]) 
				break;
			if (j == n2 - 1) //continue iterating to see if it is a subsequence, if it is then return i which is the index where it started checking
				return i;
		}
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return -1;
	if (n1 == 0 || n2 == 0)
		return -1;
	for (int i = 0; i < n1; i++) { //nested for loop, outer loop goes through a1, inner loop goes through a2
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) //returns i for first match found
				return i;
		}
	}
	return -1;
}

int separate(string a[], int n, string separator) { 
	if (n < 0)
		return -1;
	bool stop = 0;
	if (n == 0) 
		return 0; 

	int low_count = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] < separator)
			low_count++; //low_count will be the first value in which not < separator
	}

	if (low_count == n) //means that all values are < separator and it needs to return n
		return n;

	int mid = low_count;

	for (int i = 0; i <= n - 1;) {

		for (int j = i; j <= n - 1; j++) { //check to see if remaining all > separator
			if (a[j] <= separator)
				break;
			else if (j == n - 1) {
				stop = 1;
				break;
			}
		}

		if (stop == 1) //everything is in place as all values after middle are > separator
			break;

		if (a[i] > separator) { //keeps on rotating to move higher values to the right, does not rotate if values are less than or equal to separator
			rotateLeft(a, n, i);
		}
		else if (a[i] == separator) {
			if (mid != i) {
				rotateLeft(a, n, i);
			}
			else {
				mid++; //checking middle position
				i++;
			}
		}
		else if (a[i] < separator)
			i++;
	}

	return low_count;
}
