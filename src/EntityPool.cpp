#include "EntityPool.h"
#include <assert.h>

using namespace stoked;

stoked::EntityPool::EntityPool(const unsigned long capacity) :
  m_entities(capacity),
  m_freeEntities(capacity),
  m_usedEntities(0),
  m_capacity(capacity),
  m_nullEntityRef(NULL) {
    assert(stoked::NullEntityIdentifier > 0);
    m_capacity = capacity;

    for (EntityIdentifier i = 0; i < m_capacity; ++i) {
        Entity *entity = new stoked::Entity(i);
        m_entities[i] = entity;
        m_freeEntities[i] = entity;
    }

    m_nullEntityRef = new Entity(stoked::NullEntityIdentifier);
}


EntityPool::~EntityPool() {
    m_usedEntities.clear();
    m_freeEntities.clear();

    std::vector<Entity *> entities(m_entities);
    m_entities.clear();

    for (uint32_t i = 0; i < entities.size(); ++i) {
        Entity *entity = entities.at(i);
        entity->Reset();
        delete entity;
    }

    m_nullEntityRef->Reset();
    delete m_nullEntityRef;
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
    m_usedEntities.clear();
    m_freeEntities.clear();

    for (uint32_t i = 0; i < m_entities.size(); ++i) {
        Entity *entity = m_entities.at(i);
        entity->Reset();
        m_freeEntities.push_back(entity);
    }

    assert(m_usedEntities.size() + m_freeEntities.size() == m_entities.size());
}


void EntityPool::PrintDebugInfo() {
    fprintf(stdout, "Used: %lu, Free: %lu, Total: %lu\n", m_usedEntities.size(), m_freeEntities.size(), m_entities.size());
    fprintf(stderr, "%lu free entities available in this pool.\n", m_freeEntities.size());
}


const std::vector<Entity *> * EntityPool::GetEntities() const {
    return &m_freeEntities;
}
