#include "vasVariant.h"

VAS::vasVariant::vasVariant()
    : m_pVar(nullptr),
      m_size(0)
{
    
}

VAS::vasVariant::vasVariant(const VAS::vasVariant &other)
    : m_size(other.m_size),
      m_pVar(nullptr)
{
    if (other.m_pVar) {
        m_pVar = malloc(m_size);
        memcpy(m_pVar, other.m_pVar, m_size);
    }
}

VAS::vasVariant::vasVariant(VAS::vasVariant &&other)
{
    m_size = other.m_size;
    m_pVar = other.m_pVar;
}

VAS::vasVariant::~vasVariant()
{
    if (m_pVar) {
        free(m_pVar);
    }
    m_pVar = nullptr;
}

VAS::vasVariant &VAS::vasVariant::operator=(const VAS::vasVariant &other)
{
    m_size = other.m_size;
    if (other.m_pVar) {
        m_pVar = malloc(m_size);
        memcpy(m_pVar, other.m_pVar, m_size);
    }
    else {
        m_pVar = nullptr;
    }

    return *this;
}