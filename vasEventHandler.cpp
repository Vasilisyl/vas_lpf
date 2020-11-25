#include "vasEventHandler.h"
#include "vasEvent.h"

VAS::vasEventHandler::vasEventHandler() noexcept
{

}

VAS::vasEventHandler::~vasEventHandler() noexcept
{

}

void VAS::vasEventHandler::triggerEvent(const std::string &eventGroupKey, VAS::vasProperty property) noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    VAS::vasEventHandler::vasEventManager::iterator groupIt = m_eventMgr.find(eventGroupKey);
    if (groupIt == m_eventMgr.end()) {
        return;
    }

    for (auto item : groupIt->second) {
        VAS::vasEvent &event = item.second;
        event(property);
    }
    return;
}

void VAS::vasEventHandler::triggerEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasProperty property) noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    VAS::vasEventHandler::vasEventManager::iterator groupIt = m_eventMgr.find(eventGroupKey);
    if (groupIt == m_eventMgr.end()) {
        return;
    }

    VAS::vasEventHandler::vasEventGroup &group = groupIt->second;
    VAS::vasEventHandler::vasEventGroup::iterator eventIt = group.find(eventKey);
    if (eventIt == group.end()) {
        return;
    }
    VAS::vasEvent &event = eventIt->second;
    event(property);
    return;
}

void VAS::vasEventHandler::registEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasEvent event) noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    VAS::vasEventHandler::vasEventGroup &group = m_eventMgr[eventGroupKey];
    group.insert(std::pair<std::string, VAS::vasEvent>(eventKey, event));
    return;
}

void VAS::vasEventHandler::unregistEvent(const std::string &eventGroupKey, const std::string &eventKey) noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    VAS::vasEventHandler::vasEventManager::iterator groupIt = m_eventMgr.find(eventGroupKey);
    if (groupIt == m_eventMgr.end()) {
        return;
    }
    VAS::vasEventHandler::vasEventGroup &group = groupIt->second;
    group.erase(eventKey);
    return;
}