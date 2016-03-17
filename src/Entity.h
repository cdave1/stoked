#ifndef _STOKED_ENTITY_H_
#define _STOKED_ENTITY_H_

#include <string>
#include <array>
#include <uuid/uuid.h>
#include <Component.h>

#define kEntityUUIDSize 40

typedef unsigned long EntityIdentifier;

/**
 * An entity is a collection of components tied to a unique identifier.  That's it!
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

namespace stoked {
    extern const EntityIdentifier NullEntityIdentifier;

    class EntityPool;

    class Entity {
    private:

        EntityIdentifier m_ID;

        std::string m_name;

        uuid_t *m_uuid;

        std::array<stoked::Component *, 64> m_components;


    public:

        std::string GetName() const {
            return m_name;
        }

        void SetName(const std::string &name) {
            m_name = name;
        }

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

        template<typename T1, typename T2, typename ... Types>
        bool ContainsComponent();


    protected:

        friend class EntityPool;

        Entity(EntityIdentifier ID);

        void AddComponent(ComponentTypeValue key, Component *component);

        Component * GetComponent(ComponentTypeValue key) const;

        void Reset();

    };
}


template<typename T>
bool stoked::Entity::AddComponent(T *component) {
    ComponentTypeValue key = ComponentType::value<T>();

    if (GetComponent(key) == nullptr) {
        AddComponent(key, component);
        return true;
    }
    return false;
}


template<typename T>
T * stoked::Entity::GetComponent() {
    Component *component = GetComponent(ComponentType::value<T>());
    if (component == nullptr) {
        return nullptr;
    } else {
        return static_cast<T *>(component);
    }
}


template<typename T>
bool stoked::Entity::ContainsComponent() {
    ComponentTypeValue key = stoked::ComponentType::value<T>();
    return m_components.at(uint32_t(key)) != nullptr;
}


template<typename T1, typename T2, typename ... Types>
bool stoked::Entity::ContainsComponent() {
    return ContainsComponent<T1>() && ContainsComponent<T2, Types ...>();
}

#endif
