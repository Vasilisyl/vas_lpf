#pragma once

#include <exception>
#include <vector>
#include <cstdlib>
#include "vasDefined.h"

#ifndef VAS_EXCEPTION_THROW
    #define VAS_EXCEPTION_THROW(className, str) \
        { \
            throw VAS::vasException(__FILE__, __LINE__, #className, __FUNCTION__, str); \
        }
#endif /*VAS_EXCEPTION_THROW*/

#ifndef VAS_TRACE_MAX_SIZE
    #define VAS_TRACE_MAX_SIZE 50
#endif /*VAS_TRACE_MAX_SIZE*/

namespace VAS {

extern bool         g_isTraceEnabled;

/**
 * @brief vasException 异常类
 */
VAS_USER_CLASS vasException : public std::exception
{
public:
    vasException(const char *pFileName, int lineNum, const char *pClassName, \
        const char *pFuncName, const std::string &description) noexcept;
    virtual ~vasException() noexcept;

    virtual const char *what() const noexcept override;

    inline std::string getExceptionClassName() const noexcept { return m_pClassName; }

    inline std::string getExceptionFuncName() const noexcept { return m_pFuncName; }

    inline std::string getExceptionFileName() const noexcept { return m_pFileName; }

    inline int getExceptionFileLineNumber() const noexcept { return m_lineNum; };

protected:
    const char *const   m_pClassName;
    const char *const   m_pFuncName;
    const char *const   m_pFileName;
    const int           m_lineNum;
    mutable std::string m_description;

    void               *m_traceArray[VAS_TRACE_MAX_SIZE];
};

} /*namespace VAS*/