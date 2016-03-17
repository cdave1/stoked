#include "Component.h"
#include "AbstractComponentPool.h"

using namespace stoked;

ComponentTypeValue stoked::ComponentType::typeValueCounter = 0;

ComponentIdentifier Component::GetID() const {
    return m_ID;
}


void Component::PrintDebugInfo() const {
    fprintf(stderr, "Component with ID: %lu\n", m_ID);
}


void const Component::Free() {
    m_isFree = true;
    if (m_componentPool) {
        m_componentPool->Free(this);
    }
}


bool Component::IsFree() const {
    return m_isFree;
}


Component::Component() :
    m_ID(0),
    m_isFree(true),
    m_componentPool(NULL) {}


Component::Component(ComponentIdentifier ID) :
    m_ID(ID),
    m_isFree(true),
    m_componentPool(NULL) {}


Component::~Component() {}


void Component::Reset() {}


void Component::SetComponentPool(AbstractComponentPool *componentPool) {
    m_componentPool = componentPool;
}


void Component::SetBusy() {
    m_isFree = false;
}
