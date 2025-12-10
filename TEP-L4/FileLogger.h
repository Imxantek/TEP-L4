#ifndef FILELOGGER_H_
#define FILELOGGER_H_
#include "CError.h"
#include "CResult.h"
#include <string>
#include <fstream>
class FileLogger {
private:
	std::ofstream logFile;
public:
	FileLogger();
	~FileLogger();
	template<typename T>
	void log(CResult<T, CError>& result);
};

#endif
//