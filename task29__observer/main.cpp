#include <iostream>
#include <string>
#include <memory>

#include "event.h"
#include "eventlistener.h"
#include "eventmanager.h"

using namespace std;


struct FileLogger : EventListener
{
    void notify(const Event& ev) override
    {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << ev.getDescription() << endl;
    }
};

struct ConnectionMgr : EventListener
{
    void notify(const Event& ev) override
    {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << ev.getDescription() << endl;
    }
};


struct EventHandler : EventListener
{
    void notify(const Event& ev) override
    {
        cout << __PRETTY_FUNCTION__ << endl;
        cout << ev.getDescription() << endl;
    }
};


int main()
{
    shared_ptr<EventListener> evListener1 = make_shared<FileLogger>();
    shared_ptr<EventListener> evListener2 = make_shared<ConnectionMgr>();
    shared_ptr<EventListener> evListener3 = make_shared<EventHandler>();


    Event ev("Open file");

    EventManager::getInstance().addListener(evListener1);
    EventManager::getInstance().addListener(evListener2);
    EventManager::getInstance().addListener(evListener3);
    EventManager::getInstance().addListener(evListener3); // duplicate
    EventManager::getInstance().publishEvent(ev);
    std::cout << "------------------------------------------------------" << endl;
    EventManager::getInstance().removeListener(evListener3);
    EventManager::getInstance().publishEvent(ev);
    std::cout << "------------------------------------------------------" << endl;
    {
    shared_ptr<EventListener> evListener4 = make_shared<FileLogger>();
    EventManager::getInstance().addListener(evListener4);
    EventManager::getInstance().publishEvent(ev);
    }
    std::cout << "------------------------------------------------------" << endl;
    EventManager::getInstance().publishEvent(ev);
    return 0;
}
