// ConsolBankSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <bits\stdc++.h>
#include"bankDataOperations.h"

using namespace std;
using namespace dataOperations;

const string CLINTS_FILE = "C:\\C++-projects\\ConsolBankSystem\\clints.txt";
const string USERS_FILE = "C:\\C++-projects\\ConsolBankSystem\\users.txt";

enum enOperations {
	ClintsList=1,
	AddNewClint=2,
	DeleteClint=3,
	UpdateClintInfo=4,
	FindClint=5,
	Transactions=6,
	ManageUsers=7,
	Logout=8
};

enum enTransactions {
	DepositeTransation=1,
	WithdrawTransaction=2,
	TotalBalancesTransaction=3,
	MainMenueTransaction=4
};

enum enUsersOperations {
	ListUsers=1,
	AddNewUser=2,
	DeleteUser=3,
	UpdateUser=4,
	FindUser=5,
	MainMenue=6
};

void startSystem();
void doOperation(short operation, vector<dataOperations::stClint>& clints,int permission);
void transactionsMenue(vector<dataOperations::stClint>& clints,int per);
void goBackToMainMenue(vector<dataOperations::stClint>& clints,int);
void manageUsersMenue();


short MainScreen() {
	short operationType;

	tab();
	cout << right << setw(35) << "Main Screen" << endl;
	tab();

	cout << left << setw(30) << "\t\t[1] Show Clints List" << endl;
	cout << left << setw(30) << "\t\t[2] Add new Clint" << endl;
	cout << left << setw(30) << "\t\t[3] Delete Clint" << endl;
	cout << left << setw(30) << "\t\t[4] Update Clint Information" << endl;
	cout << left << setw(30) << "\t\t[5] Find Clint" << endl;
	cout << left << setw(30) << "\t\t[6] Transactions" << endl;
	cout << left << setw(30) << "\t\t[7] Manage Users" << endl;
	cout << left << setw(30) << "\t\t[8] Logout" << endl;

	tab();

	cout << "Choose What Do You Want To Do : "; operationType = readShortNumber();
	cout << endl;
	cout << "ddd" << operationType << endl;
	return operationType;
}

void showClintsList(vector<dataOperations::stClint> clints) {

	cout << right << setw(40) << "Clints List(" << clints.size() << ") Clints(s)" << endl;

	cout << "---------------------------------------------------------------------------------" << endl;

	cout << left << setw(20) << "| Account Number";
	cout << left << setw(10) << "| Pin Code";
	cout << left << setw(20) << "| Clint Name";
	cout << left << setw(15) << "| Phone";
	cout << left << setw(15) << "| Balance" << endl;

	cout << "---------------------------------------------------------------------------------" << endl;

	for (dataOperations::stClint temp : clints) {
		cout << left << setw(20) << "| " + temp.AccountNumber;
		cout << left << setw(10) << "| " + temp.pinCode;
		cout << left << setw(20) << "| " + temp.Name;
		cout << left << setw(15) << "| " + temp.phone;
		cout << left << setw(15) << "| " + to_string(temp.balance);
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------" << endl;

}

void copyTwoClints(stClint& c1, stClint& c2) {
	c1.AccountNumber = c2.AccountNumber;
	c1.balance = c2.balance;
	c1.Name = c2.Name;
	c1.phone = c2.phone;
	c1.pinCode = c2.pinCode;
}

bool findClintByAccountNumber(string targetClint, vector<stClint>& clints, stClint& clint) {

	for (stClint& temp : clints) {
		if (targetClint == temp.AccountNumber) {
			copyTwoClints(clint, temp);
			return true;
		}
	}
	return false;
}
//
stClint enterClintData(vector<stClint> clints) {
	stClint temp;

	cout << "Enter Clint Account Number : "; getline(cin >> ws, temp.AccountNumber); cout << endl;

	while (findClintByAccountNumber(temp.AccountNumber, clints,temp)) {
		cout << "Clint With Account Number (" << temp.AccountNumber << ") Is Already Exist !,Enter Another One :";
		getline(cin >> ws, temp.AccountNumber); cout << endl;
	}

	cout << "Enter Clint Price Code : "; getline(cin >> ws, temp.pinCode); cout << endl;
	cout << "Enter Clint Name : "; getline(cin >> ws, temp.Name); cout << endl;
	cout << "Enter Clint Phone Number : "; getline(cin >> ws, temp.phone); cout << endl;
	cout << "Enter Clint Balance : "; cin >> temp.balance; cout << endl;
	return temp;
}

//
void addNewClintToVector(vector<stClint>& clints) {

	tab();
	cout << "\n" << right << setw(40) << "Add New Clint Screen\n" << endl;
	tab();

	char addMore = 'n';
	do {
		stClint clint = enterClintData(clints);
		clints.push_back(clint);
		cout << "Clint Added Successfully , Are You Want To Add More Clints[y,n] ?"; cin >> addMore; cout << endl;
	} while (tolower(addMore) == 'y');

}

void PrintClintData(stClint temp) {
	cout << "The Following Are The Clint Details : " << endl;
	tab();
	cout << "Account Number  : " << temp.AccountNumber << endl;
	cout << "Pin Code        : " << temp.pinCode << endl;
	cout << "Name            : " << temp.Name << endl;
	cout << "Phone           : " << temp.phone << endl;
	cout << "Account Balance : " << temp.balance << endl;
	tab();
}

string readClintAccountNumber() {
	string accountNumber;
	cout << "Enter Clint Account Number : ";
	getline(cin >> ws, accountNumber);
	cout << endl;
	return accountNumber;
}
//
void deleteClintFromVector(vector<stClint>& clints) {

	tab();
	cout << "\n" << right << setw(40) << "Delete Clint Screen\n" << endl;
	tab();

	string targetClintAccountNumber = readClintAccountNumber();
	stClint targetClint;

	if (findClintByAccountNumber(targetClintAccountNumber, clints,targetClint)) {

		char del = false;
		PrintClintData(targetClint);

		cout << "\nAre You Sure You Want To Delete This Clint [y,n] ? "; cin >> del; cout << endl;

		if (tolower(del) == 'y') {
			vector<stClint>::iterator it;
			for (it = clints.begin(); it != clints.end(); it++) {
				if ((*it).AccountNumber == targetClintAccountNumber) {
					clints.erase(it);
					break;
				}
			}
			cout << "\nClint Deleted Successfully\n" << endl;
		}
		else {
			return;
		}
	}
	else {
		cout << "Clint With Account Number (" << targetClintAccountNumber << ") Is Not Found !" << endl;
	}
}

//
void changeClintData(stClint& clint) {
	cout << "\nEnter Pin Code : "; getline(cin >> ws, clint.pinCode); cout << endl;
	cout << "\nEnter Name : "; getline(cin >> ws, clint.Name); cout << endl;
	cout << "\nEnter Phone : "; getline(cin >> ws, clint.phone); cout << endl;
	cout << "\nEnter Balance : "; cin >> clint.balance; cout << endl;
}
//
void updateClintInformation(vector<stClint>& clints) {

	tab();
	cout << "\n" << right << setw(40) << "Update Clint Information\n" << endl;
	tab();

	 stClint targetClint;
	 targetClint.AccountNumber = readClintAccountNumber();

	if (findClintByAccountNumber(targetClint.AccountNumber, clints, targetClint)) {
		PrintClintData(targetClint);

		char update;
		cout << "Are You Sure You Want To Update The Clint Information [y,n] ? "; cin >> update; cout << endl;
		if (tolower(update) == 'y') {
			for (stClint& clint : clints) {
				if (clint.AccountNumber == targetClint.AccountNumber) {
					changeClintData(clint);
					break;
				}
			}
			cout << "\nClint Updated Successfully " << endl;
			return;
		}
	}
	else {
		cout << "\nClint With Account Number (" << targetClint.AccountNumber << ") Is Not Found ! " << endl;
	}
}

//
void findClintOperation(vector<stClint>& clints) {

	tab();
	cout << "\n" << right << setw(40) << "Find Clint Screen\n" << endl;
	tab();

	stClint targetClint;
	targetClint.AccountNumber = readClintAccountNumber();

	if (findClintByAccountNumber(targetClint.AccountNumber, clints, targetClint)) {
		PrintClintData(targetClint);
	}
	else {
		cout << "The Clint With Account Number (" << targetClint.AccountNumber << ") Is Not Found !" << endl;
	}
}

//
bool performTransaction() {
	char doOp;
	cout << "Are You Sure You Want To Perform This Transaction [y/n] ?"; cin >> doOp; cout << endl;
	if (tolower(doOp) == 'y') {
		return true;
	}
	else {
		return false;
	}
}

void deposite(stClint& clint,vector<stClint>& clints) {
	double amount;
	cout << "Please Enter Deposite Amount : "; cin >> amount; cout << endl;

	if (amount <= 0) {
		cout << "invalid amount !" << endl;
		return;
	}

	if(performTransaction()){
		for (stClint& temp : clints) {
			if (temp.AccountNumber == clint.AccountNumber) {
				temp.balance += amount;
				cout << "The Amount Added Succefully !" << endl;
				return;
			}
		}
	}
	else {
		return;
	}
}
//
void depositeOperation(vector<dataOperations::stClint>& clints) {
	
	tab();
	cout << right << setw(30) << "Deposite Screen" << endl;
	tab();

	stClint clint;
	clint.AccountNumber = readClintAccountNumber();
	if (findClintByAccountNumber(clint.AccountNumber, clints, clint)) {
		PrintClintData(clint);
		deposite(clint,clints);
	}
	else {
		cout << "The Clint With Account Number (" << clint.AccountNumber << ") Not Found !" << endl;
	}
}

//
void goBackToTransactionsMenue(vector<stClint>& clints,int per) {
	cout << "Enter Any Key To Go Back To Transactions Menue ... " << endl;
	system("pause");
	system("cls");
	transactionsMenue(clints,per);
}

bool checkBalanceForWithdraw(double balance, double amount) {
	bool ch;
	(balance >= amount) ? ch = true : ch = false;
	return ch;
}
//
void withdraw(vector<stClint>& clints, stClint clint) {
	double amount;
	cout << "\nPlease Enter Withdraw Amount : "; cin >> amount; cout << endl;

	if (checkBalanceForWithdraw(clint.balance, amount)) {
		if (performTransaction()) {
			for (stClint& temp : clints) {
				if (temp.AccountNumber == clint.AccountNumber) {
					temp.balance -= amount;
					cout << "Done Successfully , Your Balance is " << temp.balance << endl;
					return;
				}
			}
		}
	}
	else {
		cout << "Amount Exceeds The Balance , You Withdraw Up To " << clint.balance << endl;
	}
}
//

void withdrawOperation(vector<stClint>& clints) {

	tab();
	cout << "\n" << right << setw(40) << "Withdraw Screen\n" << endl;
	tab();

	stClint clint;
	clint.AccountNumber = readClintAccountNumber();

	if (findClintByAccountNumber(clint.AccountNumber, clints, clint)) {
		PrintClintData(clint);
		withdraw(clints, clint);
	}
	else {
		cout << "The Clint With Account Number (" << clint.AccountNumber << ") Is Not Found !" << endl;
	}
}

//
double totalBalancesContent(vector<stClint> clints) {
	double totalBalance = 0;

	for (stClint temp : clints)
	{
		cout << left << setw(20) << "| " + temp.AccountNumber;
		cout << left << setw(30) << "| " + temp.Name;
		cout << left << setw(10) << "| " + to_string(temp.balance) << "\n";
		totalBalance += temp.balance;
	}
	cout << "\n";
	return totalBalance;
}
//
void printTotalBalances(vector<stClint> clints) {

	double totalBalance = 0;

	cout << right << setw(40) << "Clints(" << clints.size() << ") Clints(s)" << endl;

	cout << "---------------------------------------------------------------------------------" << endl;

	cout << left << setw(20) << "| Acount Number";
	cout << left << setw(30) << "| Clint Name";
	cout << left << setw(10) << "| Balance\n";

	cout << "---------------------------------------------------------------------------------" << endl;

	for (stClint temp : clints)
	{
		cout << left << setw(20) << "| " + temp.AccountNumber;
		cout << left << setw(30) << "| " + temp.Name;
		cout << left << setw(10) << "| " + to_string(temp.balance) << "\n";
		totalBalance += temp.balance;
	}

	cout << "---------------------------------------------------------------------------------" << endl;

	cout << right << setw(45) << "Total Balances : " << totalBalance << "\n\n" << endl;
}

void doTransaction(short t,vector<dataOperations::stClint>& clints,int per) {

	switch (t) {
	case enTransactions::DepositeTransation:
		system("cls");
		depositeOperation(clints);
		break;
	case enTransactions::WithdrawTransaction:
	    system("cls");
		withdrawOperation(clints);
		break;

	case enTransactions::TotalBalancesTransaction:
	    system("cls");
		printTotalBalances(clints);
		break;

	case enTransactions::MainMenueTransaction:
		goBackToMainMenue(clints,per);
		return;
		break;
	}
	goBackToTransactionsMenue(clints,per);
}

void transactionsMenue(vector<dataOperations::stClint>& clints,int per) {
	tab();
	cout << right << setw(40) << "Transaction Menue Screen" << endl;
	tab();

	cout << left << setw(30) << "\t\t[1] Deposite " << endl;
	cout << left << setw(30) << "\t\t[2] Withdraw " << endl;
	cout << left << setw(30) << "\t\t[3] Total Balances " << endl;
	cout << left << setw(30) << "\t\t[4] Main Menue " << endl;

	tab();

	short transaction;
	cout << "Choose What Do You Want To Do [1-4] : "; transaction = readShortNumber();


	doTransaction(transaction,clints,per);
}
//
void goBackToMainMenue(vector<dataOperations::stClint>& clints,int per) {
	cout << "Press Any Key To Go Back To Main Menue ... " << endl;
	system("pause");
	system("cls");

	short op = MainScreen();
	doOperation(op, clints,per);
}

void showUsersList(vector<stUser> users) {

	cout << "\n" << right << setw(30) << "Users List(" << users.size() << ") Users(s)\n" << endl;

	tab();
	cout << left << setw(20) << "|Username";
	cout << left << setw(20) << "|Password";
	cout << left << setw(20) << "|Permissions";
	cout << endl;

	tab();

	for (stUser temp : users) {

		cout << left << setw(20) << "|" + temp.userName;
		cout << left << setw(20) << "|" + temp.password;
		cout << left << setw(20) << "|" + to_string(temp.permissions);
		cout << endl;
	}
	
	tab();
	
	return;
}

stUserPermissions readUserPermissions() {

	stUserPermissions permissions;
	cout << "\nDo You Want To Give Access To : \n" << endl;
	cout << "Show Clints List ? [y,n] "; permissions.showClintsList = readDecision();
	cout << "Add New Clint ? [y,n] "; permissions.addNewClint = readDecision();
	cout << "Delete Clint ? [y,n] "; permissions.deleteClint = readDecision();
	cout << "Update Clint ? [y,n] "; permissions.updateClint = readDecision();
	cout << "Find Clint ? [y,n] "; permissions.findClint = readDecision();
	cout << "Transactions ? [y,n] "; permissions.makeTransaction = readDecision();
	cout << "Manage Users ? [y,n] "; permissions.manageUsers = readDecision();

	return permissions;
}

int calculateUserPermissionsNumber(stUserPermissions permissions) {
	int permissionsSum = 0;

	if (permissions.showClintsList)
		permissionsSum |= 1;
	if (permissions.addNewClint)
		permissionsSum |= 2;
	if (permissions.deleteClint)
		permissionsSum |= 4;
	if (permissions.updateClint)
		permissionsSum |= 8;
	if (permissions.findClint)
		permissionsSum |= 16;
	if (permissions.makeTransaction)
		permissionsSum |= 32;
	if (permissions.manageUsers)
		permissionsSum |= 64;

	return permissionsSum;
}

stUserPermissions convertNumberToUserPermissions(int num) {
	stUserPermissions temp;

	if (num == -1) {
		temp.addNewClint = temp.deleteClint = temp.findClint = temp.makeTransaction = temp.manageUsers = temp.manageUsers = temp.showClintsList
			= temp.updateClint = true;
		return temp;
	}

	if (num >= 64) {
		temp.manageUsers = true;
		num -= 64;
	}
	if (num >= 32) {
		temp.makeTransaction = true;
		num -= 32;
	}
	if (num >= 16) {
		temp.findClint = true;
		num -= 16;
	}
	if (num >= 8) {
		temp.updateClint = true;
		num -= 8;
	}
	if (num >= 4) {
		temp.deleteClint = true;
		num -= 4;
	}
	if (num >= 2) {
		temp.addNewClint = true;
		num -= 2;
	}
	if (num >= 1) {
		temp.showClintsList = true;
		num -= 1;
	}

	return temp;
}

void addNewUserToVector(vector<stUser>& users) {

	tab();
	cout << right << setw(40) << "Add New User Screen" << endl;
	tab(); cout << endl;

	bool addUserFlag = false;
	do {

		stUser newUser;
		newUser.userName = readDistinctUserName(users);
		newUser.password = readPassword(); cout << endl;

		cout << "\nDo You To Give Full Access ?[y,n] ";
		if (readDecision()) {
			newUser.permissions = -1;
			users.push_back(newUser);
			cout << "User Added Succesfully , Do You Want To Add More Users ?[y,n]";
			addUserFlag = readDecision();
		}
		else {
			newUser.permissions = calculateUserPermissionsNumber(readUserPermissions());

			users.push_back(newUser);
			cout << "User Added Succesfully , Do You Want To Add More Users ?[y,n]";
			addUserFlag = readDecision();
		}

	} while (addUserFlag);

}

void accessDeniedMessage() {
	cout << "\n";tab();
	cout << "You Dont Have Permission To Do This ,\nPlease Cntact Your Admin !" << endl;
	tab();
}

void goBackToManageUsersMenue() {
	system("pause");
	system("cls");
	manageUsersMenue();
}

void deleteUserFromVector(vector<stUser>& users) {

	tab();
	cout << "\n" << right << setw(35) << "Delete User Screen\n" << endl;
	tab();

	string name = readUserName();

	if (name == "Admin") {
		cout << "\nYou Can Not Delete This User !\n" << endl;
		return;
	}

	if (findUserByUserName(name, users)) {
		vector<stUser>::iterator it;
		for (it = users.begin(); it != users.end(); it++) {
			if ((*it).userName == name) {
				printUserInfo(*it);

				cout << "Are You Sure You Want To Delete This User ? [y,n]";
				bool delUser = readDecision();
				if (delUser) {
					users.erase(it);
					cout << "User Deleted Successfully " << endl;
					return;
				}
				else
				return;
			}
		}
	}
	else {
		cout << "User With Name \"" << name << "\" Not Found !" << endl;
	}

}

void changePassAndPermissionsForUser(stUser& user) {

	user.password = readPassword();
	cout << "Do You Want To Give Full Access ?[y,n]";
	bool fullAccess = readDecision();

	if (fullAccess)
		user.permissions = -1;
	else
		user.permissions = calculateUserPermissionsNumber(readUserPermissions());

}

void updateUserInfo(vector<stUser>& users) {
	tab();
	cout << "\n" << right << setw(40) << "Update User Info Screen" << endl;
	tab();

	string name = readUserName();

	if (name == "Admin") {
		cout << "\nYou Can Not Update This User !\n" << endl;
		return;
	}

	if (findUserByUserName(name, users)) {
		for (stUser& temp : users) {
			if (temp.userName == name) {
				printUserInfo(temp);
				cout << "Are You Sure You Want To Update User Info ?[y,n] ";
				int update = readDecision();
				if (update) {
					changePassAndPermissionsForUser(temp);
					cout << "User Info Updated Successfully " << endl;
					return;
				}
				else {
					return;
				}
			}
		}
	}
	else {
		cout << "User With Name \"" << name << "\" Not Found !" << endl;
	}

}

void findUserOperation(vector<stUser> users) {
	tab();
	cout << "\n" << right << setw(40) << "Find User Screen\n" << endl;
	tab();

	cout << "Enter The Name Of The User That You Want To Find : ";
	string name = readUserName(); cout << endl;

	if (findUserByUserName(name, users)) {
		for (stUser temp : users) {
			if (temp.userName == name) {
				printUserInfo(temp);
				return;
			}
		}
	}
	else {
		cout << "We Can Not Find The User With Name \"" << name << "\" In The System !" << endl;
	}
	
}

void manageUsersOperations(short operation , vector<stUser>& users) {

	switch (operation) {
	case enUsersOperations::ListUsers:
		system("cls");
		showUsersList(users);
		break;
	case enUsersOperations::AddNewUser:
		system("cls");
		addNewUserToVector(users);
		break;

	case enUsersOperations::DeleteUser:
		system("cls");
		deleteUserFromVector(users);
		break;
	case enUsersOperations::UpdateUser:
		system("cls");
		updateUserInfo(users);
		break;
	case enUsersOperations::FindUser:
		system("cls");
		findUserOperation(users);
		break;
	case enUsersOperations::MainMenue:
		uploadDataToUsersFile(users, USERS_FILE);
		system("cls");
		startSystem();
		return;
	}
	//upload users to the file 
	uploadDataToUsersFile(users, USERS_FILE);

	goBackToManageUsersMenue();
}

void manageUsersMenue() {

	//load users file here : 
	vector<stUser> users;
	loadDateFromFileToVectorOfUsers(users,USERS_FILE);

	tab();
	cout << "\n" << right << setw(40) << "Manage Users Menue\n" << endl;
	tab();

	cout << "\t\t[1] List Users" << endl;
	cout << "\t\t[2] Add New User" << endl;
	cout << "\t\t[3] Delete User" << endl;
	cout << "\t\t[4] Update User" << endl;
	cout << "\t\t[5] Find User" << endl;
	cout << "\t\t[6] Main Menue" << endl;

	tab();
	cout << "Choose What Do You Want To Do ? [1 to 6] ";
	short operation = readShortNumber(); cout << endl;

	manageUsersOperations(operation,users);
	return;
}

void doOperation(short operation, vector<stClint>& clints,int permmitions = 0) {

	stUserPermissions per = convertNumberToUserPermissions(permmitions);

	switch (operation) {
	case enOperations::ClintsList:
		system("cls");


		if (per.showClintsList)
			showClintsList(clints);
		else {
			cout << permmitions << endl;
			accessDeniedMessage();
		}
		break;

	case enOperations::AddNewClint:
		system("cls");
		if (per.addNewClint)
			addNewClintToVector(clints);
		else
			accessDeniedMessage();

		break;

	case enOperations::DeleteClint:
		system("cls");
		if (per.deleteClint)
			deleteClintFromVector(clints);
		else
			accessDeniedMessage();

		break;

	case enOperations::UpdateClintInfo:
		system("cls");
		if (per.updateClint)
			updateClintInformation(clints);
		else
			accessDeniedMessage();

		break;

	case enOperations::FindClint:
		system("cls");
		if (per.findClint)
			findClintOperation(clints);
		else
			accessDeniedMessage();

		break;

	case enOperations::Transactions:
	    system("cls");
		if (per.makeTransaction)
			transactionsMenue(clints, permmitions);
		else
			accessDeniedMessage();

	    break;

	case enOperations::ManageUsers:
		system("cls");
		if (per.manageUsers)
			manageUsersMenue();
		else
			accessDeniedMessage();

		break;
	case enOperations::Logout:
		system("cls");
		startSystem();
		return;
	}
	goBackToMainMenue(clints,permmitions);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//extention 2

bool searchAboutUserName(string name,vector<stUser >users) {

	for (stUser& tempUser : users) {
		if (name == tempUser.userName) {
			return true;
		}
	}
	return false;
}

bool searchAboutUserPassword(string pass, vector<stUser> users) {

	for (stUser& tempUser : users) {
		if (pass == tempUser.password) {
			return true;
		}
	}
	return false;
}

bool loginToTheSystem(stUser& user) {

	tab();
	cout << "\n" << right << setw(30) << "Login Screen\n" << endl;
	tab();

	//load Users Here :
	vector<stUser>users;
	loadDateFromFileToVectorOfUsers(users, USERS_FILE);

	do {
		if (user.userName != "")
			cout << "Invalid User Name , Try Again !" << endl;
		
		user.userName = readUserName();
	} while (!searchAboutUserName(user.userName, users));

	do {
		if (user.password != "")
			cout << "Invalid Password , Try Again !" << endl;

		user.password = readPassword();
	} while (searchAboutUserPassword(user.password, users));

	user = findUserInfo(user.userName, users);

	return true;
}

void startSystem() {

	//load clints Data from file here :
	vector<stClint> clints;
	loadClintsDataFromFileToVectorOfClints(CLINTS_FILE, clints);

	stUser user;
	if (loginToTheSystem(user)) {
		system("cls");
		doOperation(MainScreen(), clints,user.permissions);
	}

}

int main() {


	startSystem();
	
	system("pause");
	return 0;
}

