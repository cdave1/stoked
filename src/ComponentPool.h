#ifndef _STOKED_COMPONENT_POOL_H_
#define _STOKED_COMPONENT_POOL_H_

#include "AbstractComponentPool.h"

#include <assert.h>

#include <vector>


// Pull a component off the "available" pool and put into the
// "used" elements pool.  When the component is
// destroyed, it must be returned to the available pool.
// Create a component is as simple as pulling a component from the top
// of the "available" pool and returning the reference, while inserting
// into the used" pool.
namespace stoked {
    template<class T>
    class ComponentPool : public AbstractComponentPool {
    private:
        std::vector<T *> m_items;

        std::vector<T *> m_freeItems;

        unsigned int m_capacity;

        T * m_nullComponent;

        bool m_debugMessages;


    public:

        ComponentPool(const unsigned int capacity);

        ~ComponentPool() {}

        T * Get();

        bool Free(Component *component);

        void FreeAll();

        bool Available();

        bool IsNull(T * component);

        void PrintDebugInfo();

        void EnableDebugMessages();

        void DisableDebugMessages();

    };
}


template<class T>
stoked::ComponentPool<T>::ComponentPool(const unsigned int capacity) :
    AbstractComponentPool(),
    m_items(capacity),
    m_freeItems(capacity),
    m_capacity(capacity),
    m_debugMessages(false) {
    for (int i = 0; i < m_capacity; ++i) {
        T *component = new T(i);
        component->SetComponentPool(this);
        m_items.push_back(component);
        m_freeItems.push_back(component);
    }

    m_nullComponent = new T(0);
}


template<class T>
bool stoked::ComponentPool<T>::Available() {
    return !m_freeItems.empty();
}


template<class T>
bool stoked::ComponentPool<T>::IsNull(T * component) {
    return component == m_nullComponent;
}


template<class T>
T * stoked::ComponentPool<T>::Get() {
    assert(m_freeItems.size() <= m_items.size());

    if (m_freeItems.empty()) {
        return m_nullComponent;
    }

    T * freeItem = m_freeItems.back();
    m_freeItems.pop_back();

    assert(freeItem->IsFree());

    freeItem->SetBusy();

    return freeItem;
}


template<class T>
bool stoked::ComponentPool<T>::Free(Component *usedComponent) {
    T *component = static_cast<T *>(usedComponent);

    assert(m_freeItems.size() <= m_items.size());

    if (component == NULL) {
        return false;
    }

    if (m_freeItems.size() == m_items.size()) {
        return false;
    }

    if (component < m_items.at(0) || component > m_items.at(m_items.size() - 1)) {
        return false;
    }

    assert(component->IsFree());
    component->Reset();

    m_freeItems.push_back(component);

    return true;
}


template<class T>
void stoked::ComponentPool<T>::FreeAll() {
    m_freeItems.clear();

    for (int i = 0; i < m_items.size(); ++i) {
        T *component = m_items.at(i);
        component->Reset();
        component->Free();
        m_freeItems.push_back(component);
    }
}


template<class T>
void stoked::ComponentPool<T>::PrintDebugInfo() {
    fprintf(stderr, "%d items on the available pool.\n", m_items.size());
    m_freeItems->PrintDebugInfo();
}


template<class T>
void stoked::ComponentPool<T>::EnableDebugMessages() {
    m_debugMessages = true;
}


template<class T>
void stoked::ComponentPool<T>::DisableDebugMessages() {
    m_debugMessages = false;
}

#endif
