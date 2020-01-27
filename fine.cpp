#include <iostream>
#include <string>
using namespace std;

/*fine.cpp calculates the suggested fine for a defendant convicted of fraud
in the college admissions scandal. Faking athletic credentials results in a more serious punishment. */

int main() {
	cout << "Defendant: ";
	string Defendant, yn;
	double Amt_Paid, fine = 20;
	getline(cin, Defendant);

	cout.setf(ios::fixed);
	cout.precision(1);

	if (Defendant.empty()) { //checking if empty string input
		cout << "---\n" << "You must enter a defendant name.";
	}
	else {
		cout << "Amount paid (in thousands): ";
		cin >> Amt_Paid;

		if (Amt_Paid < 0) { //checking if amount paid is negative
			cout << "---\n" << "The amount paid must not be negative.";
		}
		else {
			cout << "Fake athelete? (y/n): ";
			cin.ignore(100000, '\n');
			getline(cin, yn);

			if (yn == "y" || yn == "n") { //checking if string input is a "y" or "n"
				fine = 20;

				if (Amt_Paid - 40 > 0) { //checking if amount paid is greater than 40,000
					fine += 40 * .66;

					if (Amt_Paid - 250 > 0) { //checking if amount paid is greater than 250,000 for different fine rate
						if (yn == "y")
							fine += 210 * .22;
						else
							fine += 210 * .1;
						fine += (Amt_Paid - 250) * .14; //fine rate for amounts over 250,000
					}
					else {
						if (yn == "y")
							fine += (Amt_Paid - 40) * .22;
						else
							fine += (Amt_Paid - 40) * .1;
					}
				}
				else
					fine += .66 * Amt_Paid; //fine rate is less than 40,000 and calculation ends here

				cout << "---\n" << "The suggested fine for " << Defendant << " is $" << fine << " thousand.";
			}
			else {
				cout << "---\n" << "You must enter y or n.";
			}
		}
	}
	return 0;
}