#include "vasEventHandler.h"

VAS::vasEventHandler::vasEventHandler()
{

}

VAS::vasEventHandler::~vasEventHandler()
{

}

void VAS::vasEventHandler::publishEvent(const std::string &eventKey, VAS::vasProperty property)
{
    std::pair<VAS::vasEventMap::iterator, VAS::vasEventMap::iterator> rangePair = m_eventMap.equal_range(eventKey);

    while (rangePair.first != rangePair.second) {

        VAS::vasEvent &event = rangePair.first->second;

        event(property);

        ++(rangePair.first);
    }
}

void VAS::vasEventHandler::subscribeEvent(const std::string &eventKey, VAS::vasEvent event)
{
    m_eventMap.insert(std::make_pair(eventKey, event));
}

void VAS::vasEventHandler::unSubscribeEvent(const std::string &eventKey)
{
    /*TODO*/
    // event.target
}