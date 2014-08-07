#ifndef _STOKED_ENTITY_SYSTEM_H_
#define _STOKED_ENTITY_SYSTEM_H_

#include "EntityPool.h"

namespace stoked
{
    class EntitySystem
    {
    public:
        
        EntitySystem(EntityPool *entityPool);
        
        ~EntitySystem();
        
        
    protected:
        
        EntityPool *m_entityPool;
        
        
    };
}


#endif