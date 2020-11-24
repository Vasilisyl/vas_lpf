#pragma once

#include <exception>
#include "vasDefined.h"

namespace VAS {

/**
 * @brief vasException 异常类
 */
class vasException : public std::exception
{
public:
    vasException(const char *pFuncName, const char *pFileName, int lineNum, const std::string &description) throw();
    virtual ~vasException() throw();

    virtual const char *what() const throw() override;

protected:
    const char *const   m_pFuncName;
    const char *const   m_pFileName;
    const int           m_lineNum;
    mutable std::string m_description;
};

} /*namespace VAS*/