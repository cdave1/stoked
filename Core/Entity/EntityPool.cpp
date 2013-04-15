#include "EntityPool.h"

using namespace stoked;

EntityPool::EntityPool(const unsigned long capacity) :
  m_entities(capacity),
  m_freeEntities(capacity),
  m_usedEntities(capacity),
  m_capacity(capacity),
  m_nullEntityRef(NULL)
{
    assert(stoked::NullEntityIdentifier > 0);
    m_capacity = hdClamp(capacity, 0UL, stoked::NullEntityIdentifier - 1);
    
    for (EntityIdentifier i = 0; i < m_capacity; ++i)
    {
        Entity *entity = new Entity(i);
        m_entities.Add(entity);
        m_freeEntities.Add(entity);
    }
    
    m_nullEntityRef = new Entity(stoked::NullEntityIdentifier);
}


bool EntityPool::Available()
{
    return m_freeEntities.size() > 0;
}


bool EntityPool::Empty()
{
    return m_freeEntities.empty();
}


Entity * EntityPool::Create()
{
    assert(m_freeEntities.size() <= m_entities.size());
    assert(m_usedEntities.size() + m_freeEntities.size() == m_entities.size());
    
    if (m_freeEntities.IsEmpty())
    {
        return m_nullEntityRef;
    }
    
    Entity * entity = m_freeEntities.Top();
    m_freeEntities.Pop();
    m_usedEntities.Add(entity);
    return entity;
}


bool EntityPool::Free(Entity * entity)
{
    assert(m_freeEntities.Size() <= m_entities.Size());
    
    if (entity == NULL)
    {
        return false;
    }
    
    if (m_freeEntities.Size() == m_entities.Size())
    {
        return false;
    }
    
    if (entity < m_entities.At(0) ||
        entity > m_entities.At(m_entities.Size() - 1))
    {
        hdError("Entity is not part of this pool!");
        return false;
    }
    
    m_usedEntities.Remove(entity);
    
    entity->Reset();
    m_freeEntities.Add(entity);
    
    assert(m_usedEntities.Size() + m_freeEntities.Size() == m_entities.Size());
    
    return true;
}


void EntityPool::PrintDebugInfo()
{
    hdPrintf("%d free entities available in this pool.\n", m_freeEntities.GetSize());
    //m_usedPool.PrintDebugInfo();
}


const stoked::Vector<Entity *> * EntityPool::GetEntities() const
{
    return &m_usedEntities;
}
