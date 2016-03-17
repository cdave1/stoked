#ifndef _STOKED_COMPONENT_H_
#define _STOKED_COMPONENT_H_

#include <string>

typedef unsigned long ComponentIdentifier;

/**
 * Abstract component
 */
namespace stoked {
    class AbstractComponentPool;

    class Component {
    private:

        ComponentIdentifier m_ID;

        bool m_isFree;

        AbstractComponentPool *m_componentPool;


    public:

        ComponentIdentifier GetID() const;

        void PrintDebugInfo() const;

        void const Free();

        bool IsFree() const;


    protected:

        friend class AbstractComponentPool;

        Component(ComponentIdentifier ID);

        ~Component();

        virtual void Reset();

        void SetComponentPool(AbstractComponentPool *componentPool);

        void SetBusy();

    };
}


#define UNKNOWN_COMPONENT_TYPE "unknown"

template<typename>
struct ComponentType {
    static std::string value() { return UNKNOWN_COMPONENT_TYPE; }
};


#define RegisterComponentType(X) \
template<> struct ComponentType<X> { static std::string value() { return string(#X); } }


#endif
