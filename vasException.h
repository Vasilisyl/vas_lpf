#pragma once

#include <exception>
#include <vector>
#include <cstdlib>
#include "vasDefined.h"

/*抛出异常*/
#ifndef VAS_EXCEPTION_THROW
    #define VAS_EXCEPTION_THROW(className, str) \
        { \
            throw VAS::vasException(__FILE__, __LINE__, #className, __FUNCTION__, str); \
        }
#endif /*VAS_EXCEPTION_THROW*/

/*函数堆栈打印最大深度*/
#ifndef VAS_TRACE_MAX_SIZE
    #define VAS_TRACE_MAX_SIZE 50
#endif /*VAS_TRACE_MAX_SIZE*/

namespace VAS {

extern bool         g_isTraceEnabled; /*是否跟踪函数堆栈*/

/**
 * @brief vasException 异常类
 */
VAS_USER_CLASS vasException : public std::exception
{
public:
    vasException(const char *pFileName, int lineNum, const char *pClassName, \
        const char *pFuncName, const std::string &description) noexcept;
    virtual ~vasException() noexcept;

    /**
     * @brief  what         获取异常说明
     * @return const char * 异常说明
     */
    virtual const char *what() const noexcept override;

    /**
     * @brief  getExceptionClassName 获取触发异常的类名
     * @return std::string           触发异常的类名
     */
    inline std::string getExceptionClassName() const noexcept { return m_pClassName; }

    /**
     * @brief  getExceptionFuncName  获取触发异常的函数名
     * @return std::string           触发异常的函数名
     */
    inline std::string getExceptionFuncName() const noexcept { return m_pFuncName; }

    /**
     * @brief  getExceptionFileName  获取触发异常的文件名
     * @return std::string           触发异常的文件名
     */
    inline std::string getExceptionFileName() const noexcept { return m_pFileName; }

    /**
     * @brief  getExceptionFileLineNumber 获取触发异常的文件行号
     * @return int                        触发异常的文件行号
     */
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