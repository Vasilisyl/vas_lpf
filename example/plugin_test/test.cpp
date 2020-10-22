#include "test.h"
#include <iostream>

Test::Test(int testInt)
    : m_testInt(testInt)
{
    std::cout << "constract Test() !" << std::endl;
}

Test::~Test()
{
    std::cout << "delete Test() !" << std::endl;
}

void Test::testFunc()
{
    std::cout << "The Test::testInt = " << m_testInt << " !" << std::endl;
}
