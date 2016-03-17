#include "Entity.h"
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

const EntityIdentifier stoked::NullEntityIdentifier = ULONG_MAX;

using namespace stoked;


unsigned long Entity::GetID() const {
    return m_ID;
}


const uuid_t * Entity::GetUUID() const {
    return m_uuid;
}


void Entity::PrintUUID() const {
    char uuidStr[40];
    uuid_unparse(* m_uuid, uuidStr);
    fprintf(stderr, "%s\n", uuidStr);
}


void Entity::PrintDebugInfo() {}


#pragma mark - Private constructors

Entity::Entity(EntityIdentifier ID) :
  m_ID(ID),
  m_name(NULL),
  m_uuid(NULL),
  m_components() {
    if (!(m_uuid = (uuid_t *)calloc(1, sizeof(uuid_t)))) {
        fprintf(stderr, "Calloc\n");
    }
    uuid_generate(* m_uuid);
}


void Entity::AddComponent(ComponentTypeValue key, Component *component) {
    if (key < m_components.size()) {
        m_components[uint32_t(key)] = component;
    }
}


Component * Entity::GetComponent(ComponentTypeValue key) const {
    return m_components.at(uint32_t(key));
}


void Entity::Reset() {
    for (auto component : m_components) {
        if (component) {
            component->Free();
        }
    }
    m_components.fill(nullptr);
}
