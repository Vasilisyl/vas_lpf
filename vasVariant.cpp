#include "vasVariant.h"

VAS::vasVariant::vasVariant() noexcept
    : m_pVar(nullptr),
      m_size(0)
{
    
}

VAS::vasVariant::vasVariant(const VAS::vasVariant &other) noexcept
    : m_size(other.m_size),
      m_pVar(nullptr)
{
    if (other.m_pVar) {
        m_pVar = malloc(m_size);
        memcpy(m_pVar, other.m_pVar, m_size);
    }
}

VAS::vasVariant::vasVariant(VAS::vasVariant &&other) noexcept
{
    m_size = other.m_size;
    m_pVar = other.m_pVar;
}

VAS::vasVariant::~vasVariant() noexcept
{
    if (m_pVar) {
        free(m_pVar);
    }
    m_pVar = nullptr;
}

VAS::vasVariant &VAS::vasVariant::operator=(const VAS::vasVariant &other) throw(VAS::vasException)
{
    if (m_pVar) {
        free(m_pVar);
        m_pVar == nullptr;
    }
    m_size = other.m_size;
    if (other.m_pVar) {
        m_pVar = malloc(m_size);
        if (!m_pVar) { VAS_EXCEPTION_THROW(VAS::vasVariant, "Copy the variant failed !") }
        memcpy(m_pVar, other.m_pVar, m_size);
    }
    else {
        VAS_EXCEPTION_THROW(VAS::vasVariant, "The variant is null !");
    }

    return *this;
}