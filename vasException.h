#pragma once

#include <exception>
#include <vector>
#include "vasDefined.h"

#ifndef VAS_EXCEPTION
    #define VAS_EXCEPTION(str) \
        { \
            throw VAS::vasException(__FUNCTION__, __FILE__, __LINE__, str); \
        }
#endif /*VAS_EXCEPTION*/

#ifndef VAS_TRACE_MAX_SIZE
    #define VAS_TRACE_MAX_SIZE 50
#endif /*VAS_TRACE_MAX_SIZE*/

namespace VAS {

/**
 * @brief vasException 异常类
 */
class vasException : public std::exception
{
public:
    vasException(const char *pFileName, int lineNum, const char *pFuncName, const std::string &description) throw();
    virtual ~vasException() throw();

    virtual const char *what() const throw() override;

protected:
    const char *const   m_pFuncName;
    const char *const   m_pFileName;
    const int           m_lineNum;
    mutable std::string m_description;

    void *              m_traceArray[VAS_TRACE_MAX_SIZE];
};

} /*namespace VAS*/