#ifndef _STOKED_ABSTRACT_COMPONENT_POOL_H_
#define _STOKED_ABSTRACT_COMPONENT_POOL_H_

namespace stoked
{
    class Component;
    
    class AbstractComponentPool
    {
    public:
        
        AbstractComponentPool() {}
        
        virtual bool Free(Component *component) = 0;
        
        virtual void FreeAll() = 0;
        
    };
}

#endif