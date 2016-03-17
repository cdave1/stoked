#include <stoked.h>

template<class T> class ComponentPool;

class ComponentA : public stoked::Component {
private:
    uint32_t id;

    std::string value;

protected:

    friend class stoked::ComponentPool<ComponentA>;

    ComponentA(ComponentIdentifier ID) : stoked::Component(ID) {}
};

class ComponentB : public stoked::Component {
private:
    uint32_t id;

    std::string value;

protected:

    friend class stoked::ComponentPool<ComponentB>;

    ComponentB(ComponentIdentifier ID) : stoked::Component(ID) {}
};

class ComponentC : public stoked::Component {
private:
    uint32_t id;

    std::string value;

protected:

    friend class stoked::ComponentPool<ComponentC>;

    ComponentC(ComponentIdentifier ID) : stoked::Component(ID) {}
};


class test {
public:

    ///
    /// Test the speed of component operations.
    ///
    static void TestSpeed();

};
