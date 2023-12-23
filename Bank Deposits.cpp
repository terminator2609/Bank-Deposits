
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const unsigned short MAX_SIZE_CUSTОMERS = 50;
const unsigned short MAX_SIZE_DEPOSITS = 3;
const unsigned short GENERAL_MENU_OPTION = 6;

struct Deposit
{
	char currency[5];
	double minValue;
	char yearCreation[5];

};

struct BankCustomer
{
	char IBAN[13] = "BG24";
	char name[31];
	char yearCreation[5];
	Deposit deposits[MAX_SIZE_DEPOSITS];
	unsigned short counterOfDeposits = 0;

};

void inputDataByCustomer(BankCustomer customers[], const unsigned short index)
{
	char firstName[14], lastName[14], eightDig[9];

	cin.ignore();

	cout << "Enter value of IBAN last 8 numbers[BG24 + 8 numbers]: ";
	cin.getline(eightDig, 9);

	cout << "Enter value of first name: ";
	cin.getline(firstName, 14);

	cout << "Enter value of last name: ";
	cin.getline(lastName, 14);

	cout << "Enter value of year creation on account[YYYY]: ";
	cin.getline(customers[index].yearCreation, 5);

	strcpy_s(customers[index].name, firstName);
	strcat_s(customers[index].name, " ");
	strcat_s(customers[index].name, lastName);


	strcat_s(customers[index].IBAN, eightDig);

	cout << "" << endl;


}

void inputDataByDeposit(BankCustomer customers[], const unsigned short index) {


	unsigned short currencyChoose;

	unsigned short counterOfDeposits = customers[index].counterOfDeposits;

	string selectedCurrency;


	do
	{


		cout << "Choose currency by deposit\n[1] BGN(lev)\n[2] USD(dollars)\n[3] EURO\n";
		cin >> currencyChoose;

		switch (currencyChoose)
		{


		case 1:

			strcpy_s(customers[index].deposits[counterOfDeposits].currency, "BGN");

			selectedCurrency = "BGN";

			break;

		case 2:
			strcpy_s(customers[index].deposits[counterOfDeposits].currency, "USD");

			selectedCurrency = "USD";

			break;
		case 3:

			strcpy_s(customers[index].deposits[counterOfDeposits].currency, "EURO");

			selectedCurrency = "EURO";

			break;
		default:
			break;
		}



	} while (currencyChoose < 1 || currencyChoose > MAX_SIZE_DEPOSITS - counterOfDeposits);


	do
	{
		cout << "Enter value of minimum sum on deposit in currency[" << selectedCurrency << "]: ";
		cin >> customers[index].deposits[counterOfDeposits].minValue;


	} while (customers[index].deposits[counterOfDeposits].minValue < 1);


	do
	{

		cout << "Enter value of year of creation on deposit: ";
		cin >> customers[index].deposits[counterOfDeposits].yearCreation;

	} while (strlen(customers[index].deposits[counterOfDeposits].yearCreation) < 4 || strlen(customers[index].deposits[counterOfDeposits].yearCreation) > 4);

	customers[index].counterOfDeposits++;

	cout << "" << endl;
}

void printCustomerDataTemp(const BankCustomer customers[], const unsigned short index)
{
	cout << setw(15) << setiosflags(ios::left) << customers[index].IBAN << setw(33) << customers[index].name << setw(33) << customers[index].yearCreation
		<< setw(17) << customers[index].counterOfDeposits << resetiosflags(ios::left) << endl;

}

void printDepositDataTemp(const BankCustomer customers[], const unsigned short index)
{
	cout << "################################################################################################" << endl;
	cout << setw(10) << setiosflags(ios::left) << "Currency" << setw(13) << "Minumum Sum" << setw(33) << "Year of creation(deposit)" << endl;

	for (int i = 0; i < customers[index].counterOfDeposits; i++) {

		cout << setw(10) << setiosflags(ios::left) << customers[index].deposits[i].currency << setw(13) << setiosflags(ios::fixed) << setprecision(2) << customers[index].deposits[i].minValue << setw(33) << customers[index].deposits[i].yearCreation << endl;
	}

	cout << "------------------------------------------------------------------------------------------------" << endl;

}

void sortByDepositValue(BankCustomer customers[], const unsigned short& counterOfCustomers)
{
	int count = -1;
	BankCustomer current;

	for (int i = 0; i < counterOfCustomers; i++)
	{

		for (int j = 0; j < counterOfCustomers; j++)
		{
			if (j > i && i != 0 || i != j && i == 0)
			{
				if (customers[i].deposits[0].minValue > customers[j].deposits[0].minValue)
				{
					count = j;
				}

			}
		}

		if (count > -1) {

			current = customers[count];

			customers[count] = customers[i];

			customers[i] = current;

			count = -1;

			i--;
		}
	}

	cout << "Successfull sorting by deposit value" << endl;
	cout << "" << endl;
}


void addingCustomer(BankCustomer customers[], unsigned short& counterOfCustomers)
{
	unsigned short chooseOption = -1;
	unsigned short counterOfAdding;
	unsigned short counterOfDeposits;

	do
	{

		cout << "Choose option\n[1] Add 1 customer and 1 deposit\n[2] Add more 1 customers and 1 or more 1 deposits\n[0] Exit\n";
		cin >> chooseOption;

		switch (chooseOption)
		{
		case 1:

			if (1 + counterOfCustomers <= MAX_SIZE_CUSTОMERS) {

				counterOfAdding = 1;
				counterOfDeposits = 1;

				inputDataByCustomer(customers, counterOfCustomers);

				inputDataByDeposit(customers, counterOfCustomers);


				counterOfCustomers += 1;

				cout << "Successfull adding customer\n" << "Free space: " << MAX_SIZE_CUSTОMERS - counterOfCustomers << endl;
				cout << "Successfull adding deposit in " << customers[counterOfCustomers - 1].deposits[0].currency << " for this customer" << endl;

				cout << "" << endl;

				chooseOption = -1;


			}
			else {
				cout << "No free space !!!\n" << "All list is full" << endl;
			}

			break;

		case 2:

			do
			{
				cout << "Enter value of customers for adding[1-50]: ";
				cin >> counterOfAdding;

				if (MAX_SIZE_CUSTОMERS < counterOfCustomers + counterOfAdding) {

					cout << "No enougth space" << "Free space: " << MAX_SIZE_CUSTОMERS - counterOfCustomers;
				}

			} while (counterOfAdding < 2 || MAX_SIZE_CUSTОMERS < counterOfCustomers + counterOfAdding);

			do
			{
				cout << "You want add " << counterOfAdding << " customers" << endl;
				cout << "How many of these customers only have one deposit? " << "Enter value: ";
				cin >> counterOfDeposits;

			} while (counterOfDeposits < 0 || counterOfDeposits > counterOfAdding);

			cout << "" << endl;

			if (counterOfDeposits > 0) {

				for (int i = counterOfCustomers; i < counterOfCustomers + counterOfDeposits; i++) {

					inputDataByCustomer(customers, i);

					inputDataByDeposit(customers, i);

				}

				counterOfCustomers += counterOfDeposits;
			}


			if (counterOfDeposits < counterOfAdding) {

				counterOfAdding -= counterOfDeposits;

				unsigned short countOfDepositByCustomer = 0;

				for (int i = counterOfCustomers; i < counterOfCustomers + counterOfAdding; i++) {

					inputDataByCustomer(customers, i);

					do
					{
						cout << "Enter value of count of deposits: ";
						cin >> countOfDepositByCustomer;

					} while (countOfDepositByCustomer < 2 || countOfDepositByCustomer > MAX_SIZE_DEPOSITS);

					cout << "" << endl;

					for (int j = 0; j < countOfDepositByCustomer; j++) {

						inputDataByDeposit(customers, i);
					}


				}

				counterOfCustomers += counterOfAdding;
			}

			chooseOption = -1;

			break;
		default:
			break;
		}

	} while (chooseOption < 0 || chooseOption > 2);

	system("CLS");
}

void printAllCustomers(const BankCustomer customers[], const unsigned short& counterOfCustomers) {

	cout << "Print all customers...." << endl;
	cout << "" << endl;

	cout << setw(15) << setiosflags(ios::left) << "IBAN" << setw(33) << "Name" << setw(33) << "Year of creation(account)"
		<< setw(17) << "Deposits(count)" << resetiosflags(ios::left) << endl;

	for (int i = 0; i < counterOfCustomers; i++) {

		printCustomerDataTemp(customers, i);
		printDepositDataTemp(customers, i);
	}

	cout << "" << endl;
}

void searchAndPrintByParams(const BankCustomer customers[], const unsigned short& counterOfCustomers) {

	unsigned short chooseFunc = -1;

	double topSum = 0;
	char topCurrency[6] = "";
	char euroCounter = 0;

	do
	{
		cout << "Choose option:\n[1] Print all customers with deposit in BGN\n[2] Print all customers with max deposits + EURO\n[0] Exit\n";
		cin >> chooseFunc;

		switch (chooseFunc)
		{
		case 1:

			cout << "Print all customers...." << endl;
			cout << "" << endl;

			cout << setw(15) << setiosflags(ios::left) << "IBAN" << setw(33) << "Name" << setw(33) << "Year of creation(account)"
				<< setw(17) << "Deposits(count)" << resetiosflags(ios::left) << endl;


			for (int i = 0; i < counterOfCustomers; i++) {

				if (customers[i].counterOfDeposits < MAX_SIZE_DEPOSITS) {

					for (int j = 0; j < customers[i].counterOfDeposits; j++) {

						if (strcmp(customers[i].deposits[j].currency, "BGN") == 0) {


							printCustomerDataTemp(customers, i);
							printDepositDataTemp(customers, i);
							break;
						}


						if (j == customers[i].counterOfDeposits - 1) {

							cout << "No found customers with this param" << endl;
							cout << "" << endl;
						}

					}
				}
				else {

					cout << "Print all customers...." << endl;
					cout << "" << endl;


					printCustomerDataTemp(customers, i);
					printDepositDataTemp(customers, i);
				}

			}

			chooseFunc = -1;

			break;

		case 2:

			cout << "Print all customers...." << endl;
			cout << "" << endl;

			cout << setw(15) << setiosflags(ios::left) << "IBAN" << setw(33) << "Name" << setw(33) << "Year of creation(account)"
				<< setw(17) << "Deposits(count)" << resetiosflags(ios::left) << endl;

			for (int i = 0; i < counterOfCustomers; i++) {


				for (int j = 0; j < customers[i].counterOfDeposits; j++) {

					if (customers[i].deposits[j].minValue > topSum) {

						topSum = customers[i].deposits[j].minValue;

						strcpy_s(topCurrency, customers[i].deposits[j].currency);
					}


				}

				if (strcmp(topCurrency, "EURO") == 0) {


					printCustomerDataTemp(customers, i);
					printDepositDataTemp(customers, i);

					euroCounter++;
				}



			}

			if (euroCounter == 0) {

				cout << "No found customers with this param" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;

			break;

		default:
			break;
		}

	} while (chooseFunc < 0 || chooseFunc > 2);

}

void sortByIBAN(BankCustomer customers[], const unsigned short& counterOfCustomers)
{
	int count = -1;
	BankCustomer current;

	for (int i = 0; i < counterOfCustomers; i++)
	{

		for (int j = 0; j < counterOfCustomers; j++)
		{
			if (j > i && i != 0 || i != j && i == 0)
			{
				if (strcmp(customers[i].IBAN, customers[j].IBAN) > 0)
				{
					count = j;
				}

			}
		}

		if (count > -1) {

			current = customers[count];

			customers[count] = customers[i];

			customers[i] = current;

			count = -1;

			i--;
		}
	}

	cout << "Successfull sorting by IBAN" << endl;
	cout << "" << endl;
}

void references(const BankCustomer customers[], const unsigned short& counterOfCustomers) {

	BankCustomer customersFiltered[MAX_SIZE_CUSTОMERS] = { 0 };
	unsigned short counterCustomerFiltered = 0;

	char selectedYearCreation[5];


	unsigned short chooseOption = -1;


	do
	{

		cout << "Choose option\n[1] Search customers by year of creation on bank account and print sorted by IBAN\n[2] Search customers by with 1 deposit on bank account and print sorted by value on a deposit\n[0] Exit\n";
		cin >> chooseOption;

		switch (chooseOption)
		{
		case 1:

			system("CLS");

			cin.ignore();

			cout << "Enter value of year creation on bank account for searching: ";
			cin.getline(selectedYearCreation, 5);


			if (counterCustomerFiltered > 0) {

				memset(customersFiltered, 0, sizeof(customersFiltered));
				counterCustomerFiltered = 0;
			}


			for (int i = 0; i < counterOfCustomers; i++)
			{
				if (strcmp(customers[i].yearCreation, selectedYearCreation) == 0) {

					customersFiltered[counterCustomerFiltered] = customers[i];

					counterCustomerFiltered++;
				}
			}

			if (counterCustomerFiltered > 1) {

				sortByIBAN(customersFiltered, counterCustomerFiltered);
				printAllCustomers(customersFiltered, counterCustomerFiltered);
			}
			else if (counterCustomerFiltered == 1) {
				printAllCustomers(customersFiltered, counterCustomerFiltered);
			}
			else {
				cout << "No found customer/s with this year of creation " << selectedYearCreation << endl;
				cout << "" << endl;
			}

			chooseOption = -1;

			break;

		case 2:

			if (counterCustomerFiltered > 0) {

				memset(customersFiltered, 0, sizeof(customersFiltered));
				counterCustomerFiltered = 0;
			}

			for (int i = 0; i < counterOfCustomers; i++)
			{
				if (customers[i].counterOfDeposits == 1) {

					customersFiltered[counterCustomerFiltered] = customers[i];

					counterCustomerFiltered++;
				}
			}

			if (counterCustomerFiltered > 1) {

				sortByDepositValue(customersFiltered, counterCustomerFiltered);
				printAllCustomers(customersFiltered, counterCustomerFiltered);
			}
			else if (counterCustomerFiltered == 1) {
				printAllCustomers(customersFiltered, counterCustomerFiltered);
			}
			else {
				cout << "No found customer/s with one deposit" << selectedYearCreation << endl;
				cout << "" << endl;
			}

			chooseOption = -1;

			break;
		default:
			break;
		}

	} while (chooseOption < 0 || chooseOption > 2);

	system("CLS");

}

int main()
{

	BankCustomer customers[MAX_SIZE_CUSTОMERS];

	unsigned short counterOfCustomers = 0;

	unsigned short chooseFunc = -1;


	do
	{

		cout << "Choose option:\n[1] Add customers\n[2] Print all customers\n[3] Search and print by params\n[4] Sort by IBAN\n[5] Save data in file\n[6] Load data on file\n[7] Reference\n[0] Exit\n";
		cin >> chooseFunc;

		switch (chooseFunc)
		{
		case 1:

			system("CLS");

			if (counterOfCustomers < MAX_SIZE_CUSTОMERS) {
				addingCustomer(customers, counterOfCustomers); // Извикване на функция за добавяне на вложители + влог/ове
			}
			else {
				cout << "Full space on list" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;

			break;

		case 2:

			system("CLS");

			if (counterOfCustomers > 0) {

				printAllCustomers(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;
			break;

		case 3:

			system("CLS");

			if (counterOfCustomers > 0) {

				searchAndPrintByParams(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;
			break;

		case 4:

			system("CLS");

			if (counterOfCustomers > 1) {

				sortByIBAN(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers or found 1 customer" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;

			break;
		case 7:

			if (counterOfCustomers > 1) {

				references(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers or found 1 customer" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;

			break;
		case 0:
			system("exit");
			break;
		default:
			break;
		}

	} while (chooseFunc < 0 || chooseFunc > GENERAL_MENU_OPTION);


	return 0;

}


