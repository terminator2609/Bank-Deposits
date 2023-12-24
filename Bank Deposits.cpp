
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

const unsigned short MAX_SIZE_CUSTОMERS = 50;
const unsigned short MAX_SIZE_DEPOSITS = 3;
const unsigned short GENERAL_MENU_OPTION = 9;

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
	Deposit deposits[MAX_SIZE_DEPOSITS] = { 0 };
	unsigned short counterOfDeposits = 0;

};

// ------------------Помощни функции на основните-------------------------------- //


void manageCurrency(BankCustomer customers[], const unsigned short index, unsigned short& currencyCounter, string currentCurrency[], unsigned short priority)
{

	bool isExist = false;
	string currencies[] = { "BGN", "USD", "EURO" };

	for (int i = 0; i < currencyCounter; i++)
	{
		currentCurrency[i] = "";
	}

	currencyCounter = 0;



	switch (priority)
	{
	case 1:

		cout << "Choose currency\n";

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < customers[index].counterOfDeposits; j++)
			{
				if (strcmp(customers[index].deposits[j].currency, currencies[i].c_str()) == 0) {
					isExist = true;
				}
			}

			if (isExist == false) {

				cout << "[" << currencyCounter + 1 << "] " << currencies[i] << "\n";

				currentCurrency[currencyCounter] = currencies[i];
				currencyCounter++;
			}
			else {
				isExist = false;
			}
		}

		break;

	case 2:

		cout << "Choose currency\n";

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < customers[index].counterOfDeposits; j++)
			{
				if (strcmp(customers[index].deposits[j].currency, currencies[i].c_str()) == 0) {
					isExist = true;
					break;
				}

			}

			if (isExist == true) {

				cout << "[" << currencyCounter + 1 << "] " << currencies[i] << "\n";

				currentCurrency[currencyCounter] = currencies[i];
				currencyCounter++;

				isExist = false;
			}
		}

		break;

	default:
		break;
	}




}

void inputDataByCustomer(BankCustomer customers[], const unsigned short index)
{

	cout << "User data:" << endl;
	cout << "" << endl;

	char firstName[14] = "", lastName[14] = "", eightDig[9] = "";

	cin.ignore();

	do
	{
		cout << "Enter value of IBAN last 8 numbers[BG24 + 8 numbers]: ";
		cin.getline(eightDig, 9);
	} while (eightDig != NULL && eightDig[0] == '\0');


	do
	{
		cout << "Enter value of first name: ";
		cin.getline(firstName, 14);
	} while (firstName != NULL && firstName[0] == '\0');

	do
	{
		cout << "Enter value of last name: ";
		cin.getline(lastName, 14);

	} while (lastName != NULL && lastName[0] == '\0');

	do
	{
		cout << "Enter value of year creation on account[YYYY]: ";
		cin.getline(customers[index].yearCreation, 5);

	} while (customers[index].yearCreation != NULL && customers[index].yearCreation[0] == '\0');


	strcpy_s(customers[index].name, firstName);
	strcat_s(customers[index].name, " ");
	strcat_s(customers[index].name, lastName);


	strcat_s(customers[index].IBAN, eightDig);

	cout << "" << endl;

	fflush(stdin);

}

void inputDataByDeposit(BankCustomer customers[], const unsigned short index) {


	cout << "Deposit data:" << endl;
	cout << "" << endl;

	unsigned short currencyCounter = 0;
	string currentCurrency[3] = { "" };

	unsigned short counterOfDeposits = customers[index].counterOfDeposits;

	string selectedCurrency;
	unsigned short currencyChoose;

	do
	{
		manageCurrency(customers, index, currencyCounter, currentCurrency, 1);
		cin >> currencyChoose;

		switch (currencyChoose)
		{


		case 1:

			if (currencyCounter >= 1) {

				selectedCurrency = currentCurrency[0];

			}

			break;
		case 2:

			if (currencyCounter >= 2) {

				selectedCurrency = currentCurrency[1];

			}

			break;

		case 3:

			if (currencyCounter >= 3) {

				selectedCurrency = currentCurrency[2];

			}

			break;


		default:
			break;
		}



	} while (currencyChoose < 1 || currencyChoose > MAX_SIZE_DEPOSITS - counterOfDeposits);


	strcpy_s(customers[index].deposits[counterOfDeposits].currency, selectedCurrency.c_str());

	do
	{
		cout << "Enter value of amount[minimum 500] on deposit in currency[" << selectedCurrency << "]: ";
		cin >> customers[index].deposits[counterOfDeposits].minValue;


	} while (customers[index].deposits[counterOfDeposits].minValue < 500);

	do
	{
		cout << "Enter value of year of creation on deposit: ";
		cin >> customers[index].deposits[counterOfDeposits].yearCreation;

	} while (strcmp(customers[index].yearCreation, customers[index].deposits[counterOfDeposits].yearCreation) > 0);

	customers[index].counterOfDeposits++;

	cout << "" << endl;

	fflush(stdin);
}

void printCustomerDataTemp(const BankCustomer customers[], const unsigned short index)
{
	cout << setw(15) << setiosflags(ios::left) << "IBAN" << setw(33) << "Name" << setw(33) << "Year of creation(account)"
		<< setw(17) << "Deposits(count)" << resetiosflags(ios::left) << endl;

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


void manageDeposit(BankCustomer customers[], const unsigned short counterOfCustomers, const unsigned short index, const unsigned short chooseOption)
{
	string selectedCurrency;
	string currentCurrency[3] = { "" };

	unsigned short currencyCounter = 0;
	unsigned short chooseCurrency;

	unsigned short currentIndex = 0;

	double windrawSum = 0;


	switch (chooseOption)
	{
	case 1:

		do
		{
			manageCurrency(customers, index, currencyCounter, currentCurrency, 2);
			cin >> chooseCurrency;

			switch (chooseCurrency)
			{
			case 1:

				if (currencyCounter >= 1) {

					selectedCurrency = currentCurrency[0];

				}

				break;
			case 2:

				if (currencyCounter >= 2) {

					selectedCurrency = currentCurrency[1];

				}

				break;

			case 3:

				if (currencyCounter >= 3) {

					selectedCurrency = currentCurrency[2];

				}

				break;


			default:
				break;
			}

		} while (chooseCurrency < 1 || chooseCurrency > currencyCounter);

		for (int i = 0; i < customers[index].counterOfDeposits; i++) {

			if (strcmp(customers[index].deposits[i].currency, selectedCurrency.c_str()) == 0)
			{
				cout << "Amount on this deposit is: " << customers[index].deposits[i].minValue
					<< " " << customers[index].deposits[i].currency << endl;
				cout << "" << endl;

				currentIndex = i;

				break;
			}
		}


		do
		{
			cout << "What amount you want to withdraw[1-" << customers[index].deposits[currentIndex].minValue << "]: ";
			cin >> windrawSum;


		} while (windrawSum > customers[index].deposits[currentIndex].minValue || windrawSum < 1);


		if (windrawSum == customers[index].deposits[currentIndex].minValue)
		{
			if (currentIndex == customers[index].counterOfDeposits - 1)
			{
				customers[index].deposits[currentIndex] = { 0 };

			}
			else {
				for (int i = currentIndex; i < customers[index].counterOfDeposits; i++) {

					if (i != customers[index].counterOfDeposits - 1)
					{
						customers[index].deposits[i] = customers[index].deposits[i + 1];
					}


				}

				int lastIndex = customers[index].counterOfDeposits - 1;

				customers[index].deposits[lastIndex] = { 0 };


			}

			customers[index].counterOfDeposits -= 1;

			cout << "Successfull windraw " << windrawSum << " " << selectedCurrency << endl;
			cout << "The deposit is removed" << endl;
		}
		else {

			customers[index].deposits[currentIndex].minValue -= windrawSum;

			cout << "Successfull windraw " << windrawSum << " " << selectedCurrency << endl;
			cout << "The left amount in current deposit is: " << customers[index].deposits[currentIndex].minValue << " " << selectedCurrency;
		}

		break;

	case 2:

		for (int i = 0; i < customers[index].counterOfDeposits; i++)
		{
			windrawSum += customers[index].deposits[i].minValue;
		}

		if (index == counterOfCustomers - 1) {

			customers[index] = { 0 };
		}
		else {
			for (int i = index; i < counterOfCustomers; i++) {

				if (i != counterOfCustomers - 1)
				{
					customers[i] = customers[i + 1];
				}


			}


			customers[counterOfCustomers - 1] = { 0 };
		}

		cout << "You windraw: " << windrawSum << " total" << endl;
		cout << "The bank account removed" << endl;

		break;
	default:
		break;
	}


}





// --------------------------- Основни функции -------------------------------------- //

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

			system("CLS");

			if (1 + counterOfCustomers <= MAX_SIZE_CUSTОMERS) {

				counterOfAdding = 1;
				counterOfDeposits = 1;

				inputDataByCustomer(customers, counterOfCustomers);

				inputDataByDeposit(customers, counterOfCustomers);


				counterOfCustomers += 1;

				cout << "Successfull adding customer\n" << "Free space: " << MAX_SIZE_CUSTОMERS - counterOfCustomers << endl;
				cout << "Successfull adding deposit in " << customers[counterOfCustomers - 1].deposits[0].currency << " for this customer" << endl;

				cout << "" << endl;

			}
			else {
				cout << "No free space !!!\n" << "All list is full" << endl;
			}

			chooseOption = -1;

			break;

		case 2:

			system("CLS");

			do
			{
				cout << "Enter value of customers for adding[2-50]: ";
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


					system("CLS");

					cout << "Successfull adding customer" << endl;
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

					system("CLS");

					cout << "Successfull adding customer\n" << endl;

				}

				counterOfCustomers += counterOfAdding;


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


void printAllCustomers(const BankCustomer customers[], const unsigned short& counterOfCustomers) {

	cout << "Print all customers...." << endl;
	cout << "" << endl;

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

void addNewDeposit(BankCustomer customers[], unsigned short& counterOfCustomers) {

	char selectedIban[13];

	short indexCustomer = -1;

	cin.ignore();

	cout << "Enter value of IBAN on customer for adding on deposit: ";
	cin.getline(selectedIban, 13);

	for (int i = 0; i < counterOfCustomers; i++) {

		if (strcmp(customers[i].IBAN, selectedIban) == 0) {
			indexCustomer = i;
		}
	}

	if (indexCustomer == -1) {
		cout << "No found customer with this IBAN" << endl;
	}
	else if (customers[indexCustomer].counterOfDeposits == 3) {
		cout << "This customer already exist 3 deposits" << endl;
	}
	else {
		inputDataByDeposit(customers, indexCustomer);
	}
}

void windrawDeposit(BankCustomer customers[], unsigned short& counterOfCustomers)
{
	char selectedIban[13];

	short indexCustomer = -1;

	unsigned short chooseOption = -1;


	do
	{


		cout << "Choose option\n[1] Windraw sum by deposit\n[2] Windraw sum by all deposits and remove bank account\n[0] Exit\n";
		cin >> chooseOption;

		cin.ignore();

		switch (chooseOption)
		{
		case 1:

			system("CLS");

			cout << "Enter value of IBAN on customer for adding on deposit: ";
			cin.getline(selectedIban, 13);

			for (int i = 0; i < counterOfCustomers; i++) {

				if (strcmp(customers[i].IBAN, selectedIban) == 0) {
					indexCustomer = i;
				}
			}

			if (indexCustomer == -1) {
				cout << "No found customer with this IBAN" << endl;
			}
			else if (indexCustomer > -1 && customers[indexCustomer].counterOfDeposits == 0) {
				cout << "No found deposits for windraw" << endl;
			}
			else {
				manageDeposit(customers, counterOfCustomers, indexCustomer, 1);
				indexCustomer = -1;
			}


			chooseOption = -1;

			break;

		case 2:

			system("CLS");

			cout << "Enter value of IBAN on customer for adding on deposit: ";
			cin.getline(selectedIban, 13);

			for (int i = 0; i < counterOfCustomers; i++) {

				if (strcmp(customers[i].IBAN, selectedIban) == 0) {
					indexCustomer = i;
				}
			}

			if (indexCustomer == -1) {
				cout << "No found customer with this IBAN" << endl;
			}
			else if (indexCustomer > -1 && customers[indexCustomer].counterOfDeposits == 0) {
				cout << "No found deposits for windraw" << endl;
			}
			else {
				manageDeposit(customers, counterOfCustomers, indexCustomer, 2);
				indexCustomer = -1;
				counterOfCustomers -= 1;
			}

			break;
		default:
			break;
		}

	} while (chooseOption < 0 || chooseOption > 2);

	system("CLS");
}

int saveDataToBinaryFile(const BankCustomer customers[], const unsigned short& counterOfCustomers)
{
	ofstream customerData("customers.dat", ios::out | ios::binary);

	if (!customerData) {
		cout << "Cannot open file!" << endl;
		return 1;
	}


	for (int i = 0; i < counterOfCustomers; i++) {

		customerData.write((char*)&customers[i], sizeof(BankCustomer));

	}

	customerData.close();

	if (!customerData.good()) {
		cout << "Error occurred at writing time!" << endl;
		return 1;
	}
	else {
		cout << "Successfull save data to file" << endl;

		cout << "" << endl;
	}


}

int loadDataFromBinaryFile(BankCustomer customers[], unsigned short& counterOfCustomers)
{
	ifstream customerDataInput("customers.dat", ios::in | ios::binary);

	if (!customerDataInput) {
		cout << "Cannot open file!" << endl;
		return 1;
	}

	while (!customerDataInput.eof())
	{
		customerDataInput.read((char*)&customers[counterOfCustomers], sizeof(BankCustomer));

		counterOfCustomers++;
	}


	customerDataInput.close();

	if (!customerDataInput.good()) {
		cout << "Error occurred at reading time!" << endl;
		return 1;
	}
	else {
		cout << "Successfull load data to file" << endl;

		cout << "" << endl;
	}
}


int main()
{

	BankCustomer customers[MAX_SIZE_CUSTОMERS];

	unsigned short counterOfCustomers = 0;

	unsigned short chooseFunc = -1;


	do
	{

		cout << "Choose option:\n[1] Add customers\n[2] Print all customers\n[3] Search and print by params\n[4] Sort by IBAN\n[5] Save data in file\n[6] Load data on file\n[7] Reference\n[8] Add new deposit\n[9] Windraw deposit\n[0] Exit\n";
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

			if (counterOfCustomers > 1) {

				searchAndPrintByParams(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers or found 1 customer" << endl;
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

		case 5:
			system("CLS");

			if (counterOfCustomers > 0) {

				saveDataToBinaryFile(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;

			break;

		case 6:
			system("CLS");

			loadDataFromBinaryFile(customers, counterOfCustomers);

			chooseFunc = -1;

			break;
		case 7:

			system("CLS");

			if (counterOfCustomers > 1) {

				references(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers or found 1 customer" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;

			break;

		case 8:

			system("CLS");

			if (counterOfCustomers > 0) {

				addNewDeposit(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers" << endl;
				cout << "" << endl;
			}

			chooseFunc = -1;

			break;

		case 9:

			system("CLS");

			if (counterOfCustomers > 0) {

				windrawDeposit(customers, counterOfCustomers);
			}
			else {

				cout << "No found customers" << endl;
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


