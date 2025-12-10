#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_
#include "CTree.h"
#include "CError.h"
#include "CResult.h"
#include "FileLogger.h"
#include <string>
#include<vector>
class UI {
private:
	CTree* t;
	FileLogger logger;
	bool isRunning;
	void printMenu();
	CResult<CTree*, CError> enter();
	CResult<void, CError> vars();
	CResult<void, CError> print ();
	CResult<void, CError> comp();
	void join();
public:
	UI();
	~UI();
	void run();
};
#endif
//