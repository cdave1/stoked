#include "Entity.h"
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

const EntityIdentifier stoked::NullEntityIdentifier = ULONG_MAX;

using namespace stoked;

const std::string & Entity::GetName() const
{
    return m_name;
}


void Entity::SetName(const std::string &name)
{
    m_name = name;
}


unsigned long Entity::GetID() const
{
    return m_ID;
}


const uuid_t * Entity::GetUUID() const
{
    return m_uuid;
}


void Entity::PrintUUID() const
{
    char uuidStr[40];
    uuid_unparse(* m_uuid, uuidStr);
    fprintf(stderr, "%s\n", uuidStr);
}


void Entity::PrintDebugInfo()
{
}


#pragma mark - Private constructors

Entity::Entity(EntityIdentifier ID) :
  m_ID(ID),
  m_name(NULL),
  m_uuid(NULL),
  m_components()
{
    if (!(m_uuid = (uuid_t *)calloc(1, sizeof(uuid_t))))
    {
        fprintf(stderr, "Calloc\n");
    }
    uuid_generate(* m_uuid);
}


void Entity::AddComponent(std::string key, Component *component)
{
    m_components.insert(m_components.begin(), std::pair<std::string, Component *>(key, component));
}


Component * Entity::GetComponent(std::string key)
{
    if (m_components.count(key) == 0)
    {
        return NULL;
    }
    return m_components[key];
}


void Entity::Reset()
{
    for (std::map<std::string, Component *>::iterator it = m_components.begin();
         it != m_components.end(); ++it)
    {
        Component *component = it->second;
        component->Free();
    }
    m_components.clear();
}
