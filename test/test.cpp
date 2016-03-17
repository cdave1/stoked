#include "test.h"

#include <stoked.h>

#include <assert.h>

void test::TestSpeed() {
    auto c1 = new stoked::ComponentPool<ComponentA>(1024);
    auto c2 = new stoked::ComponentPool<ComponentB>(1024);
    auto c3 = new stoked::ComponentPool<ComponentC>(1024);

    ComponentTypeValue c1ValueType = ComponentType::value<ComponentA>();
    ComponentTypeValue c2ValueType = ComponentType::value<ComponentB>();
    ComponentTypeValue c3ValueType = ComponentType::value<ComponentC>();

    assert(c1ValueType == ComponentType::value<ComponentA>());
    assert(c2ValueType == ComponentType::value<ComponentB>());
    assert(c3ValueType == ComponentType::value<ComponentC>());

    auto components = new stoked::ComponentPool<ComponentA>(1024);
    auto entities = new stoked::EntityPool(4096);

    auto start = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

    const unsigned int ITERATIONS = 10000;
    for (int i = 0; i < ITERATIONS; ++i) {
        unsigned int j = 0;
        while (j < entities->GetEntities()->Capacity()) {
            auto ent = entities->Create();
            assert(ent != nullptr);

            auto testComponent = components->Get();

            ent->AddComponent(testComponent);

            if (ent->ContainsComponent<ComponentA>()) {
                auto com = ent->GetComponent<ComponentA>();
                assert(com != nullptr);
            }
            ++j;
        }

        entities->FreeAll();
    }

    auto end = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

    fprintf(stderr, "Took %3.9f\n", end - start);

    delete entities;
    delete components;
}
