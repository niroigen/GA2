#include "GA/migration.hpp"

void migrateIndividual(GA* ga1, GA* ga2)
{
    while(ga1 != nullptr || ga2 != nullptr)
    {
        while(ga1 != nullptr && ga1->canRun)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        while(ga2 != nullptr && ga2->canRun)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        if (ga1 != nullptr && ga2 != nullptr)
        {
            
        } 
        else if (ga1 == nullptr)
        {
            ga2->canRun = true;
        }
        else if (ga2 == nullptr)
        {
            ga1->canRun = true;
        }
        else 
        {
            break;
        }
    }
}