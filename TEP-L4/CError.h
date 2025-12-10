#ifndef CERROR_H_
#define CERROR_H_

#include <string>

class CError {
private:
    std::string str_message;
public:
    CError(const std::string& message);
    CError(const CError& pcOther);
    std::string strGetMessage() const;
};

#endif // CERROR_H_
//