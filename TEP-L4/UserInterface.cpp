#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "UserInterface.h"
#include "CError.h"
#include "CResult.h"

UI::UI() {
	t = new CTree();
}

UI::~UI() {
	delete t;
}


void UI::run() {
	std::cout << "====== Welcome to CTree prefix notation evaluation program! ======\n";
	isRunning = true;
	while (isRunning) {
		printMenu();
		std::string sel;
		std::cout << "> ";
		std::cin >> sel;
		std::cin.ignore();
		if (sel == "enter") {
			CResult<CTree*, CError> result = enter();
			logger.log(result);
			if (result.bIsSuccess()) {
				std::cout << "Expression entered successfully.\n";
				std::cout << "Current CTree:\n";
				result.cGetValue()->print();
			}
			else {
				result.printErrors();
			}
		}
		else if (sel == "vars") {
			CResult<void, CError> result = vars();
			logger.log(result);
			if (result.bIsSuccess()) {
				std::cout << "\nVariables printed successfully.\n";
			}
			else {
				result.printErrors();
			}
		}
		else if (sel == "print") {
			CResult<void, CError> result = print();
			logger.log(result);
			if(result.bIsSuccess()) {
				std::cout << "\nCTree printed successfully.\n";
			}
			else {
				result.printErrors();
			}
		}
		else if (sel == "comp") {
			CResult<void, CError> result = comp();
			logger.log(result);
			if (result.bIsSuccess()) {
				std::cout << "\nComputation completed successfully.\n";
			}
			else {
				result.printErrors();
			}
		}
		else if (sel == "join") {
			join();
		}
		else if (sel == "exit") {
			std::cout << "Thank you for using my program\n Goodbye!";

			isRunning = false;
		}
		else {
			std::cout << "Error - no such function!\n";
		}
		std::cout << "\n";
	}
}


void UI::printMenu() {
	std::cout << "\n---Available operations:---\n";
	std::cout << "- enter <formula> - input the formula into a CTree\n";
	std::cout << "- vars - print all variables currently inputed into the CTree\n";
	std::cout << "- print - print the current CTree using a prefix notation\n";
	std::cout << "- comp <var0> <var1> ... <varN> - compile the equation while assuming <var0> - <varN> as values of subsequent variables\n";
	std::cout << "- join <formula> - join another CTree (selected algorithm - leftmost leaf)\n";
	std::cout << "- exit - exits the program\n";
}
CResult<CTree*, CError> UI::enter() {
	//std::cout << "Enter your expression:\n";
	std::string exp;
	std::getline(std::cin, exp);
	try {
		t->enter(exp);
	}
	catch (std::invalid_argument& e) {
		return CResult<CTree*, CError>::cFail(new CError(e.what()));
	}
	return CResult<CTree*, CError>::cOk(t);
}

CResult<void, CError> UI::vars() {
	try {
		t->vars();
	}catch(std::exception e) {
		return CResult<void, CError>::cFail(new CError(e.what()));
	}
	return CResult<void, CError>::cOk();
}

CResult<void, CError> UI::print() {
	try {
		t->print();
	}
	catch (std::exception e) {
		return CResult<void, CError>::cFail(new CError(e.what()));
	}
	return CResult<void, CError>::cOk();
}

bool isNumber(const std::string& s) {
	if (s.empty()) return false;
	int start = 0;
	if (s[0] == '-') start = 1;
	for (int i = start; i < s.length(); ++i) {
		if (!isdigit(s[i])) return false;
	}
	return true;
}


CResult<void, CError> UI::comp() {
	std::string input;
	std::getline(std::cin, input);
	std::vector<int> vec;
	std::stringstream ss(input);
	std::string token;
	while (ss >> token) {
		if (isNumber(token)) {
			vec.push_back(std::stoi(token.c_str()));
		}
		else {
			return CResult<void, CError>::cFail(new CError("Non-numeric value entered in comp command."));
		}
	}
	try {
		t->comp(vec);
	}
	catch (std::exception e) {
		return CResult<void, CError>::cFail(new CError(e.what()));
	}
	return CResult<void, CError>::cOk();
}
void UI::join() {
	std::cout << "Enter the formula of the CTree you will be joining:\n";
	std::string exp;
	std::getline(std::cin, exp);
	t->join(exp);
}
//