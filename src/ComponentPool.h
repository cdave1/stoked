#ifndef _HD_COMPONENT_POOL_H_
#define _HD_COMPONENT_POOL_H_

#include "Core/Component/AbstractComponentPool.h"

// Pull a component off the "available" pool and put into the
// "used" elements pool.  When the component is
// destroyed, it must be returned to the available pool.
// Create a component is as simple as pulling a component from the top
// of the "available" pool and returning the reference, while inserting
// into the used" pool.
namespace stoked
{
    template<class T>
    class ComponentPool : public AbstractComponentPool
    {
    private:
        std::vector<T *> * m_items;
        
        std::vector<T *> * m_freeItems;
        
        unsigned int m_capacity;
        
        T * m_nullComponent;
        
        bool m_debugMessages;
        
        
    public:
        
        ComponentPool(const unsigned int capacity);
        
        ~ComponentPool()
        {
            hdDeleteSafely(m_items);
            hdDeleteSafely(m_freeItems);
        }
        
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
  m_items(NULL),
  m_freeItems(NULL),
  m_capacity(capacity),
  m_debugMessages(false)
{
    m_items = new stoked::Vector<T *>(capacity);
    m_freeItems = new stoked::Vector<T *>(capacity);
    
    for (int i = 0; i < m_capacity; ++i)
    {
        T *component = new T(i);
        component->SetComponentPool(this);
        m_items->Add(component);
        m_freeItems->Add(component);
    }
    
    m_nullComponent = new T(0);
}


template<class T>
bool stoked::ComponentPool<T>::Available()
{
    return !m_freeItems->empty();
}


template<class T>
bool stoked::ComponentPool<T>::IsNull(T * component)
{
    return component == m_nullComponent;
}


template<class T>
T * stoked::ComponentPool<T>::Get()
{
    hdAssert(m_freeItems->Size() <= m_items->Size());
    
    if (m_freeItems->IsEmpty())
    {
        return m_nullComponent;
    }
    
    T * freeItem = m_freeItems->Top();
    m_freeItems->Pop();
    
    hdAssert(freeItem->IsFree());
    
    freeItem->SetBusy();
    
    return freeItem;
}


template<class T>
bool stoked::ComponentPool<T>::Free(Component *usedComponent)
{
    T *component = static_cast<T *>(usedComponent);
    
    hdAssert(m_freeItems->Size() <= m_items->Size());
    
    if (component == NULL)
    {
        return false;
    }
    
    if (m_freeItems->Size() == m_items->Size())
    {
        return false;
    }
    
    if (component < m_items->At(0) ||
        component > m_items->At(m_items->Size() - 1))
    {
        return false;
    }
    
    hdAssert(component->IsFree());
    component->Reset();
    
    m_freeItems->Add(component);
    
    return true;
}


template<class T>
void stoked::ComponentPool<T>::FreeAll()
{
    m_freeItems->Clear();
    
    for (int i = 0; i < m_items->Size(); ++i)
    {
        T *component = m_items->At(i);
        component->Reset();
        component->Free();
        m_freeItems->Add(component);
    }
}


template<class T>
void stoked::ComponentPool<T>::PrintDebugInfo()
{
    hdPrintf("%d items on the available pool.\n", m_items->GetSize());
    m_freeItems->PrintDebugInfo();
}


template<class T>
void stoked::ComponentPool<T>::EnableDebugMessages()
{
    m_debugMessages = true;
}


template<class T>
void stoked::ComponentPool<T>::DisableDebugMessages()
{
    m_debugMessages = false;
}

#endif