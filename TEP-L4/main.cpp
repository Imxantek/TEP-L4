#include <iostream>
#include "CError.h"   
#include "CResult.h"
#include "UserInterface.h"

CResult<double, CError> eDivide(double a, double b)
{
    if (b == 0)
        return CResult<double, CError>::cFail(new CError("division by zero"));

    return CResult<double, CError>::cOk(a / b);
}

int main()
{
    /*CResult<double, CError> r = eDivide(10, 0);

    if (r.bIsSuccess())
        std::cout << "Result: " << r.cGetValue() << std::endl;
    else
        std::cout << "Error: " << r.vGetErrors()[0]->strGetMessage() << std::endl;

    std::cout << "Koniec programu. Nacisnij Enter..." << std::endl;
    std::cin.get(); */
    UI().run();
    return 0;
}
//