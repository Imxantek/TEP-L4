#include "FileLogger.h"
#include "CTree.h"
#include <iostream>
#include <fstream>
FileLogger::FileLogger() {
	logFile.open("log.txt", std::ios::app);
	if (!logFile.is_open()) {
		std::cerr << "Error opening log file." << std::endl;
	}
}
FileLogger::~FileLogger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}
template<typename T>
void FileLogger::log(const CResult<T, CError>& result) {
	if (!logFile.is_open()) {
		std::cerr << "Log file is not open." << std::endl;
		return;
	}
	if (std::is_same<T, CTree*>::value) {
		if (result.bIsSuccess) {
			logFile << "Operation succeeded. Current CTree:\n";
			logFile << result.cGetValue()->print() << "\n";
			return;
		}
		else {
			logFile << "Operation failed with errors:\n";	
			for (const auto& error : result.vGetErrors()) {
				logFile << "- " << error->strGetMessage() << "\n";
			}
			return;
		}
	}
	else {
		if(result.bIsSuccess()) {
			logFile << "Operation succeeded.\n";
			return;
		}
		else {
			logFile << "Operation failed with errors:\n";
			for (const auto& error : result.vGetErrors()) {
				logFile << "- " << error->strGetMessage() << "\n";
			}
			return;
		}
	}
}