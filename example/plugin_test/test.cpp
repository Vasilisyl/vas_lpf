#include "test.h"
#include <iostream>

Test::Test(int testInt)
    : m_testInt(testInt)
{
    std::cout << "constract Test() !" << std::endl;
}

Test::~Test()
{
    std::cout << "release Test() !" << std::endl;
}

void Test::testFunc()
{
    std::cout << "The Test::m_testInt = " << m_testInt << " !" << std::endl;
}
