#include "EntityPool.h"
#include <assert.h>

using namespace stoked;

stoked::EntityPool::EntityPool(const unsigned long capacity) :
  m_entities(capacity),
  m_freeEntities(capacity),
  m_usedEntities(capacity),
  m_capacity(capacity),
  m_nullEntityRef(NULL) {
    assert(stoked::NullEntityIdentifier > 0);
    m_capacity = capacity;

    for (EntityIdentifier i = 0; i < m_capacity; ++i) {
        Entity *entity = new stoked::Entity(i);
        m_entities.push_back(entity);
        m_freeEntities.push_back(entity);
    }

    m_nullEntityRef = new Entity(stoked::NullEntityIdentifier);
}


bool stoked::EntityPool::Available() {
    return m_freeEntities.size() > 0;
}


bool stoked::EntityPool::Empty() {
    return m_freeEntities.empty();
}


stoked::Entity * stoked::EntityPool::Create() {
    assert(m_freeEntities.size() <= m_entities.size());
    assert(m_usedEntities.size() + m_freeEntities.size() == m_entities.size());

    if (m_freeEntities.empty()) {
        return m_nullEntityRef;
    }

    Entity * entity = m_freeEntities.back();
    m_freeEntities.pop_back();
    m_usedEntities.push_back(entity);
    return entity;
}


bool EntityPool::Free(Entity * entity) {
    assert(m_freeEntities.size() <= m_entities.size());

    if (entity == NULL) {
        return false;
    }

    if (m_freeEntities.size() == m_entities.size()) {
        return false;
    }

    if (entity < m_entities.at(0) || entity > m_entities.at(m_entities.size() - 1)) {
        fprintf(stderr, "Entity is not part of this pool!");
        return false;
    }

    m_usedEntities.erase(std::find(m_usedEntities.begin(), m_usedEntities.end(), entity));

    entity->Reset();
    m_freeEntities.push_back(entity);

    assert(m_usedEntities.size() + m_freeEntities.size() == m_entities.size());

    return true;
}


void EntityPool::FreeAll() {
    // TODO!
}


void EntityPool::PrintDebugInfo() {
    fprintf(stderr, "%lu free entities available in this pool.\n", m_freeEntities.size());
    //m_usedPool.PrintDebugInfo();
}


const std::vector<Entity *> * EntityPool::GetEntities() const {
    return &m_usedEntities;
}
