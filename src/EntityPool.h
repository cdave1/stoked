#ifndef _STOKED_ENTITY_POOL_H_
#define _STOKED_ENTITY_POOL_H_

#include <vector>
#include <Entity.h>

namespace stoked {
    class EntityPool {
    private:

        std::vector<Entity *> m_entities;

        std::vector<Entity *> m_freeEntities;

        std::vector<Entity *> m_usedEntities;

        unsigned int m_capacity;
        
        Entity * m_nullEntityRef;


    public:

        EntityPool(const unsigned long capacity);

        Entity * Create();

        bool Free(Entity * entity);

        bool Available();

        bool Empty();

        bool IsNull(Entity * ref);

        void PrintDebugInfo();

        const std::vector<Entity *> * GetEntities() const;


    private:

        void Init();

        void Clear();

    };
}

#endif
