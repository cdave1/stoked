#ifndef _STOKED_COMPONENT_H_
#define _STOKED_COMPONENT_H_

#include <string>

typedef uint32_t ComponentIdentifier;

typedef uint32_t ComponentTypeValue;

/**
 * Abstract component
 */
namespace stoked {
    class AbstractComponentPool;

    class Component {
    private:

        const ComponentIdentifier m_ID;

        bool m_isFree;

        AbstractComponentPool *m_componentPool;


    public:

        ComponentIdentifier GetID() const;

        void PrintDebugInfo() const;

        void const Free();

        bool IsFree() const;


    protected:

        friend class AbstractComponentPool;

        Component();

        Component(ComponentIdentifier ID);

        ~Component();

        virtual void Reset();

        void SetComponentPool(AbstractComponentPool *componentPool);

        void SetBusy();

    };

    class ComponentType {
        static ComponentTypeValue typeValueCounter;

    public:
        template<typename T>
        static inline ComponentTypeValue value() {
            static ComponentTypeValue v = typeValueCounter++;
            return v;
        }
    };
}

#define UNKNOWN_COMPONENT_TYPE "unknown"

template<typename>
struct ComponentName {
    static std::string value() { return UNKNOWN_COMPONENT_TYPE; }
};


#define RegisterComponentName(X) \
template<> struct ComponentName<X> { static std::string value() { return string(#X); } }

#endif
