#include "Hospital.h"
#include <stdio.h>
#pragma warning(disable:4290)
// CONSTANTS DECLARATION
const int MAX_CHOISE = 12;
const int MIN_CHOISE = 1;
const int EXIT_CHOISE = 0;
const int CONTINUE_PROGRAM_CHOISE = 1;
//decleration of excepations dunctions
void newTerminate();
void UserChoiseExceptions(int UserChoise) throw(int);
void ToContinueExceptions(int UserChoise) throw(const char*);

void main()
{
	set_terminate(newTerminate);
	Hospital t;
	int toContinue = 0,yourChoise;
	cout << "Welcome to the hospital" << endl << endl;
	do {
		cout << "Please choose an action from the following Menu:" << endl << endl;
			t.show_menu();
			cout << "Your choise: ";
			cin >> yourChoise;
			cout << endl;
			try
			{
				switch (yourChoise)
				{
				case 1: t.add_Depart();
					break;
				case 2: t.add_new_nurse();
					break;
				case 3: t.add_new_doctor();
					break;
				case 4: t.add_new_patient();
					break;
				case 5: t.add_researcher();
					break;
				case 6: t.add_essay();
					break;
				case 7: t.print_patients_depart();
					break;
				case 8: printCollection(t.getAllWoorkers_hospital());
					break;
				case 9: printCollection(t.getInstitute()[0]->getAllResearchers());
					break;
				case 10: t.print__single_patient();
					break;
				case 11: t.print_all_researchers_doctors();
					break;
				case 12: t.comparing_researcher_by_num_essays();
					break;
				}
				UserChoiseExceptions(yourChoise);
				cout << endl<< "Would you like to continue ?\nPress 1 if YES or 0 if NO" << endl;
				cout << "Your choise: ";
				cin >> toContinue;
				ToContinueExceptions(toContinue);
				cout << endl;
			}
			catch (int val)
			{
				cout << val << " isn't a valid choise in this Menu" << endl << endl;
				cout << endl;
			}
			catch (const char* msg) { cout << msg << endl << endl; }
			catch (...) { cout << "Unknown Error" << endl<< endl;}

	} while (toContinue==CONTINUE_PROGRAM_CHOISE);
	cout << "End of The Program" << endl;
}

//  Exceptions functions implementation
void newTerminate()
{
	cout << "An unknown problem occured, please call the support." << endl;
	exit(1);
}
void UserChoiseExceptions(int UserChoise) throw(int)
{
	if (UserChoise< MIN_CHOISE || UserChoise > MAX_CHOISE)
		throw UserChoise;
}
void ToContinueExceptions(int UserChoise) throw(const char*)
{
	if (UserChoise< EXIT_CHOISE || UserChoise > CONTINUE_PROGRAM_CHOISE)
		throw "Invalid input was entered.";

}