
#include <iostream>

using namespace std;

const unsigned short MAX_SIZE_CUSTОMERS = 50;
const unsigned short MAX_SIZE_DEPOSITS = 3;
const unsigned short GENERAL_MENU_OPTION = 4;

struct Deposit
{
	char currency[5];
	double minValue;
	char yearCreation[5];

};

struct BankCustomer
{
	char IBAN[13] = "BG24";
	char name[30];
	char yearCreation[5];
	Deposit deposits[MAX_SIZE_DEPOSITS];
	unsigned short counterOfDeposits;

};

void inputDataByCustomer(BankCustomer customers[], unsigned short index)
{
	char firstName[14], lastName[14], spacing[2];

	cin.ignore();

	cout << "Enter value of IBAN last 8 numbers[BG24 + 8 numbers]: ";
	cin.getline(customers[index].IBAN, 13);

	cout << "Enter value of first name: ";
	cin.getline(firstName, 14);

	cout << "Enter value of last name: ";
	cin.getline(lastName, 14);

	cout << "Enter value of year creation on account[YYYY]: ";
	cin.getline(customers[index].yearCreation, 5);


}

void inputDataByDeposit(BankCustomer customers[], unsigned short index) {


	unsigned short currencyChoose;

	unsigned short counterOfDeposits = customers[index].counterOfDeposits;



	do
	{
		cout << "Choose currency by deposit\n[1] BGN(lev)\n[2] USD(dollars)\n[3] EURO";
		cin >> currencyChoose;

		switch (currencyChoose)
		{
		case 1:

			strcpy_s(customers[index].deposits[counterOfDeposits].currency, "BGN");

			break;

		case 2: 
			strcpy_s(customers[index].deposits[counterOfDeposits].currency, "USD");
			break;
		case 3:
			strcpy_s(customers[index].deposits[counterOfDeposits].currency, "EURO");

			break;
		default:
			break;
		}


	} while (currencyChoose < 1 || currencyChoose > MAX_SIZE_DEPOSITS - counterOfDeposits);



}



void addingCustomer(BankCustomer customers[], unsigned short& counterOfCustomers)
{
	unsigned short chooseOption;
	unsigned short counterOfAdding;
	unsigned short counterOfDeposits;

	do
	{

		cout << "Choose option\n[1] Add 1 customer and 1 deposit\n[2] Add more 1 customers and 1 or more 1 deposits\n[0] Exit";
		cin >> chooseOption;

		switch (chooseOption)
		{
		case 1:

			if (1 + counterOfCustomers <= MAX_SIZE_CUSTОMERS) {

				counterOfAdding = 1;
				counterOfDeposits = 1;

				counterOfCustomers += 1;

			}

			break;

		default:
			break;
		}

	} while (chooseOption < 0 || chooseOption > 2);
}

int main()
{

	BankCustomer customers[MAX_SIZE_CUSTОMERS];

	unsigned short counterOfCustomers = 0;

	unsigned short chooseFunc;


	do
	{

		cout << "Choose option:\n[1] Add customers";
		cin >> chooseFunc;

		switch (chooseFunc)
		{
		case 1:

			system("CLS");

			addingCustomer(customers, counterOfCustomers);

		default:
			break;
		}

	} while (chooseFunc < 0 || chooseFunc > GENERAL_MENU_OPTION);




}


