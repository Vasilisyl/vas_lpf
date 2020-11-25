#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "vasDefined.h"
#include "vasException.h"

namespace VAS {

/**
 * @brief vasVariant 通用的对象存储类，vasVariant的拷贝和赋值为深拷贝
 */
VAS_USER_INTERFACE_CLASS vasVariant
{
public:
    vasVariant() noexcept;
    vasVariant(const vasVariant &other) noexcept;
    vasVariant(vasVariant &&other) noexcept;
    ~vasVariant() noexcept;

    /**
     * @brief  set 设置需要存储的对象，vasVariant将会把传入的对象拷贝一份副本并保存到vasVariant中
     * @param  var 需要vasVariant存储的对象
     */
    template<typename VARIANT>
    void set(VARIANT var)  throw(VAS::vasException);

    /**
     * @brief  get       获取vasVariant中存储的对象
     * @return VARIANT * 返回vasVariant中已存储的对象副本
     */
    template<typename VARIANT>
    VARIANT get() const noexcept;

    vasVariant &operator=(const vasVariant &other) throw(VAS::vasException);

private:
    void   *m_pVar;
    size_t  m_size;
};

template<typename VARIANT>
void vasVariant::set(VARIANT var) throw(VAS::vasException)
{
    if (m_pVar) {
        free(m_pVar);
        m_pVar = nullptr;
    }
    m_size = sizeof(VARIANT);
    m_pVar = malloc(m_size);
    if (!m_pVar) { VAS_EXCEPTION_THROW(VAS::vasVariant, "Create the variant failed !"); }
    memcpy(m_pVar, (void *)&var, m_size);
}

template<typename VARIANT>
VARIANT vasVariant::get() const noexcept
{
    return *reinterpret_cast<VARIANT *>(m_pVar);
}

} /*namespace VAS*/