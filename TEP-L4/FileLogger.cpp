#include "FileLogger.h"
#include "CTree.h"
#include <iostream>
#include <fstream>
FileLogger::FileLogger() {
	logFile.open("log.txt");
	if (!logFile.is_open()) {
		std::cerr << "Error opening log file." << std::endl;
	}
}
FileLogger::~FileLogger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}


template<>
void FileLogger::log(CResult<void, CError>& result) {
	if (!logFile.is_open()) {
		std::cerr << "Log file is not open." << std::endl;
	}
	if (result.bIsSuccess()) {
		logFile << "Operation succeeded.\n";
	}
	else {
		logFile << "Operation failed with errors:\n";
		for (const auto& error : result.vGetErrors()) {
			logFile << "- " << error->strGetMessage() << "\n";
		}
	}
	
}
//

template<>
void FileLogger::log(CResult<CTree*, CError>& result) {
	if (!logFile.is_open()) {
		std::cerr << "Log file is not open." << std::endl;
	}
	if (result.bIsSuccess()) {
		logFile << "Operation succeeded. Current CTree:\n";
		logFile << result.cGetValue()->toString() << "\n";
	}
	else {
		logFile << "Operation failed with errors:\n";	
		for (const auto& error : result.vGetErrors()) {
			logFile << "- " << error->strGetMessage() << "\n";
		}
	}
}
