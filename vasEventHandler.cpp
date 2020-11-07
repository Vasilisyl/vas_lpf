#include "vasEventHandler.h"

VAS::vasEventHandler::vasEventHandler()
{

}

VAS::vasEventHandler::~vasEventHandler()
{

}

void VAS::vasEventHandler::publishEvent(const std::string &eventGroupKey, VAS::vasProperty property)
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

void VAS::vasEventHandler::publishEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasProperty property)
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

void VAS::vasEventHandler::subscribeEvent(const std::string &eventGroupKey, const std::string &eventKey, VAS::vasEvent event)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    VAS::vasEventHandler::vasEventGroup &group = m_eventMgr[eventGroupKey];
    group.insert(std::pair<std::string, VAS::vasEvent>(eventKey, event));
    return;
}

void VAS::vasEventHandler::unSubscribeEvent(const std::string &eventGroupKey, const std::string &eventKey)
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