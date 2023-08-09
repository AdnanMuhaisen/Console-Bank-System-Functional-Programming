#pragma once

#include <bits\stdc++.h>
using namespace std;

namespace dataOperations {

	struct stClint {
		string AccountNumber;
		string pinCode;
		string Name;
		string phone;
		double balance;
	};

	enum enPermissions {
		ListUsers=1,
		AddUser=2,
		DeleteUser=3,
		UpdateUser=4,
		FindUser=5
	};

	struct stUser {
		string userName = "";
		string password = "";
		int permissions;
	};

	struct stUserPermissions {
		//show clint lists represented by 1
		//add new clint represented by 2 ... and so on

		bool showClintsList = false, addNewClint = false, deleteClint = false, updateClint = false
			, findClint = false, makeTransaction = false, manageUsers = false;
	};

	void tab() {
		cout << "--------------------------------------------------------" << endl;
	}

	vector<string> splitString(string str,string delimiter="#\\\\#") {

		vector<string>stringWords; short pos = 0;
		string temp;

		while ((pos = str.find(delimiter)) != string::npos) {
			temp = str.substr(0, pos);
			if (temp != "") {
				stringWords.push_back(temp);
			}
			str.erase(0,pos+delimiter.length());
		}

		if (temp != "") {
			stringWords.push_back(str);
		}

		return stringWords;
	}

	stClint convertLineToClint(string line,string delimiter="#\\\\#") {
		stClint temp;
		vector<string>clintWords = splitString(line);
		temp.AccountNumber = clintWords[0];
		temp.pinCode = clintWords[1];
		temp.Name = clintWords[2];
		temp.phone = clintWords[3];
		temp.balance = stod(clintWords[4]);
		return temp;
	}

	void loadClintsDataFromFileToVectorOfClints(string fileName,vector<stClint>& clints) {
		fstream file; file.open(fileName, ios::in);

		string tempLine;
		while (getline(file, tempLine)) {
			clints.push_back(convertLineToClint(tempLine));
		}
		file.close();
	}

	string createLineFromClint(stClint clint, string delimiter="#\\\\#") {
		string line = "";
		line += clint.AccountNumber + delimiter + clint.pinCode + delimiter +
			clint.Name + delimiter + clint.phone + delimiter + to_string(clint.balance);
		return line;
	}

	string createLineFromUser(stUser user, string delimiter = "#\\\\#") {
		return user.userName + delimiter + user.password + delimiter + to_string(user.permissions);
	}

	stUser convertLineToUser(string line, string delimiter = "#\\\\#") {
		vector<string>user = splitString(line);

		stUser temp;
		temp.userName = user[0];
		temp.password = user[1];
		temp.permissions = stoi(user[2]);

		return temp;
	}

	void loadDateFromFileToVectorOfUsers(vector<stUser>& users, string fileName) {
		fstream file;
		file.open(fileName, ios::in);
		
		string tempLine;
		while (getline(file, tempLine)) {
			users.push_back(convertLineToUser(tempLine));
		}
		file.close();
	}

	void uploadDataToClintsFile(vector<stClint>clints, string fileName) {
		fstream clintsFile; clintsFile.open(fileName, ios::out);

		vector<stClint>::iterator it;
		for (it = clints.begin(); it != clints.end(); it++) {
			clintsFile << createLineFromClint(*it)+"\n";
		}
		clints.clear();
		clintsFile.close();
	}

	void uploadDataToUsersFile(vector<stUser>users, string fileName) {
		fstream usersFile; usersFile.open(fileName, ios::out);

		vector<stUser>::iterator it;
		for (it = users.begin(); it != users.end(); it++) {
			usersFile << createLineFromUser(*it) + "\n";
		}
		users.clear();
		usersFile.close();
	}

	short readShortNumber() {
		short i; cin >> i; return i;
	}

	string readString() {
		string str;
		cin >> str;
		return str;
	}

	string readUserName() {
		cout << "User Name : ";
		string name = readString();
		return name;
	}

	string readPassword() {
		cout << "Password : ";
		string password = readString();
		return password;
	}

	bool readDecision() {
		char ch;
		cin >> ch;
		cout << endl;

		if (tolower(ch) == 'y')
			return true;
		else
			return false;
	}

	bool findUserByUserName(string name,vector<stUser> users) {
		for (stUser temp : users) {
			if (temp.userName == name)
				return true;
		}
		return false;
	}

	string readDistinctUserName(vector<stUser> users) {

		string name = readUserName(); cout << endl;
		while (findUserByUserName(name, users)) {
			cout << "Usre Is Exist , Try Again !" << endl;
			name = readUserName();
		}
		return name;
	}

	stUser findUserInfo(string name,vector<stUser> users) {
		for (stUser temp : users) {
			if (temp.userName == name)
				return temp;
		}
	}

	void printUserInfo(stUser user) {
		cout << "The Folowing Is The User Information : " << endl;
		tab();
		cout << "Username : " << user.userName << endl;
		cout << "Password : " << user.password << endl;
		cout << "Permissions : " << to_string(user.permissions) << endl;
		tab();
	}
}