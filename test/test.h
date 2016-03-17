#include <stoked.h>

template<class T> class ComponentPool;

class ComponentA : public stoked::Component {
private:
    uint32_t id;

    std::string value;

protected:

    friend class stoked::ComponentPool<ComponentA>;

    ComponentA() {}
};

class ComponentB : public stoked::Component {
private:
    uint32_t id;

    std::string value;

protected:

    friend class stoked::ComponentPool<ComponentB>;

    ComponentB() {}
};

class ComponentC : public stoked::Component {
private:
    uint32_t id;

    std::string value;

protected:

    friend class stoked::ComponentPool<ComponentC>;

    ComponentC() {}
};


class test {
public:

    ///
    /// Test the speed of component operations.
    ///
    static void TestSpeed();

};
