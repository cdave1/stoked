#ifndef _STOKED_ENTITY_H_
#define _STOKED_ENTITY_H_

#include <string>
#include <map>
#include <uuid/uuid.h>
#include "Component.h"

#define kEntityUUIDSize 40

typedef unsigned long EntityIdentifier;

/**
 * An entity is a collection of components that represents something in the game space.
 *
 * Some restrictions on entities:
 * - Can only be instantiated by an entity pool.
 * - Only components maintain state information.
 * - The entity does not maintain any reference to, or copy of, the proxy data used to 
 *   create the entity.
 * - Entity pointers can not be directly destroyed, they can only be marked as "no longer 
 *   in use" via the entity pool.
 * - Entities on their own do not do anything.  The components are responsible for
 *   carrying data about the entity in question.  Entity Systems are responsible for
 *   passing messages between components for a particular entity.
 * - Entities should NOT be subclassed.
 */

namespace stoked
{
    extern const EntityIdentifier NullEntityIdentifier;
    
    class EntityPool;
    
    class Entity
    {
    private:
        
        EntityIdentifier m_ID;
        
        std::string m_name;
        
        uuid_t *m_uuid;
        
        std::map<std::string, Component *> m_components;
        
        
    public:
        
        const std::string & GetName() const;
        
        void SetName(const std::string &name);
		
        EntityIdentifier GetID() const;
        
        const uuid_t * GetUUID() const;
        
        void PrintUUID() const;
        
        void PrintDebugInfo();
        
        template<typename T>
        bool AddComponent(T *component);
        
        template<typename T>
        T * GetComponent();
        
        template<typename T>
        bool ContainsComponent();
        
        template<typename T1, typename T2>
        bool ContainsComponents();
        
        
    protected:
        
        friend class EntityPool;
        
        Entity(EntityIdentifier ID);
        
        void AddComponent(std::string key, Component *component);
        
        Component * GetComponent(std::string key);
        
        void Reset();
        
    };
}


template<typename T>
bool stoked::Entity::AddComponent(T *component)
{
    std::string key = ComponentType<T>().value();
    
    if (key == UNKNOWN_COMPONENT_TYPE)
    {
        return false;
    }
    
    if (GetComponent(key) == NULL)
    {
        AddComponent(key, component);
        return true;
    }
    return false;
}


template<typename T>
T * stoked::Entity::GetComponent()
{
    std::string key = ComponentType<T>().value();
    if (GetComponent(key) == NULL)
    {
        return NULL;
    }
    T * component = static_cast<T *>(GetComponent(key));
    return component;
}


template<typename T>
bool stoked::Entity::ContainsComponent()
{
    std::string key = ComponentType<T>().value();
    return m_components.count(key) != 0;
}


template<typename T1, typename T2>
bool stoked::Entity::ContainsComponents()
{
    return ContainsComponent<T1>() && ContainsComponent<T2>();
}

#endif
