#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus
}
#endif

namespace VAS {

class vasVariant
{
public:
    vasVariant();
    vasVariant(const vasVariant &var);
    ~vasVariant();

    template<typename VAR>
    bool set(VAR var)
    {
        /*TODO: 定义错误码throw*/
        if (m_pVar) {
            free(m_pVar);
            m_pVar = nullptr;
        }
        m_size = sizeof(VAR);
        m_pVar = malloc(m_size);
    }

    template<typename VAR>
    VAR get() const
    {

    }

    template<typename VAR>
    vasVariant &operator=(const vasVariant &var)
    {
        this->set<VAR>(var.get<VAR>());
        return *this;
    }

private:
    void   *m_pVar;
    size_t  m_size;
};

}