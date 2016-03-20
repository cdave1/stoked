#include "test.h"

#include <chrono>
#include <assert.h>

#include <stoked.h>

#define PASSED() { fprintf(stdout, "%s Passed ✓\n", __FUNCTION__); }


void test::TestEntityPool() {
    auto entities = new stoked::EntityPool(4);

    auto e1 = entities->Create();
    auto e2 = entities->Create();
    auto e3 = entities->Create();
    auto e4 = entities->Create();

    assert(e1 != nullptr);
    assert(e2 != nullptr);
    assert(e3 != nullptr);
    assert(e4 != nullptr);

    assert(e1->GetID() < entities->GetCapacity());
    assert(e2->GetID() < entities->GetCapacity());
    assert(e3->GetID() < entities->GetCapacity());
    assert(e4->GetID() < entities->GetCapacity());

    assert(entities->Empty() && !entities->Available());

    entities->FreeAll();

    assert(!entities->Empty() && entities->Available());

    e1 = entities->Create();
    bool freeResult = entities->Free(e1);
    assert(freeResult == true);

    delete entities;

    PASSED();
}


void test::TestEmptyEntityPool() {
    auto entities = new stoked::EntityPool(2);
    entities->Create();
    entities->Create();
    assert(entities->Empty() && !entities->Available());

    auto nullEntity1 = entities->Create();
    auto nullEntity2 = entities->Create();

    assert(nullEntity1 == nullEntity2);
    assert(nullEntity1->IsNullEntity());
    assert(nullEntity2->IsNullEntity());

    PASSED();
}


void test::TestComponentPool() {
    auto components = new stoked::ComponentPool<ComponentA>(4);

    auto c1 = components->Get();
    auto c2 = components->Get();
    auto c3 = components->Get();
    auto c4 = components->Get();

    assert(c1 != nullptr);
    assert(c2 != nullptr);
    assert(c3 != nullptr);
    assert(c4 != nullptr);

    assert(c1->GetID() < components->GetCapacity());
    assert(c2->GetID() < components->GetCapacity());
    assert(c3->GetID() < components->GetCapacity());
    assert(c4->GetID() < components->GetCapacity());

    // Currently, when "Get" is called, the component is not "free", in the sense that it is assumed that it is
    // attached to an entity.  This is actually pretty confusing.
    assert(!c1->IsFree());
    assert(!c2->IsFree());
    assert(!c3->IsFree());
    assert(!c4->IsFree());

    PASSED();
}


void test::TestEmptyComponentPool() {
    PASSED();
}


void test::TestEntityComponentAttachment() {
    auto entities = new stoked::EntityPool(2);
    auto componentPoolA = new stoked::ComponentPool<ComponentA>(4);
    auto componentPoolB = new stoked::ComponentPool<ComponentB>(4);

    while (entities->Available()) {
        auto e1 = entities->Create();
        auto a = componentPoolA->Get();
        auto b = componentPoolB->Get();

        bool resA = e1->AddComponent(a);
        bool resB = e1->AddComponent(b);

        assert(resA);
        assert(resB);
    }

    PASSED();
}


void test::TestSpeed() {
    auto c1 = new stoked::ComponentPool<ComponentA>(1024);
    auto c2 = new stoked::ComponentPool<ComponentB>(1024);
    auto c3 = new stoked::ComponentPool<ComponentC>(1024);

    ComponentTypeValue c1ValueType = stoked::ComponentType::value<ComponentA>();
    ComponentTypeValue c2ValueType = stoked::ComponentType::value<ComponentB>();
    ComponentTypeValue c3ValueType = stoked::ComponentType::value<ComponentC>();

    assert(c1ValueType == stoked::ComponentType::value<ComponentA>());
    assert(c2ValueType == stoked::ComponentType::value<ComponentB>());
    assert(c3ValueType == stoked::ComponentType::value<ComponentC>());

    auto components = new stoked::ComponentPool<ComponentA>(1024);
    auto entities = new stoked::EntityPool(4096);

    auto start = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

    unsigned int totalComponentsAdded = 0;
    const unsigned int ITERATIONS = 10000;
    for (int i = 0; i < ITERATIONS; ++i) {
        unsigned int j = 0;
        while (j < entities->GetEntities()->size()) {
            auto ent = entities->Create();
            assert(ent != nullptr);

            auto testComponent = components->Get();
            if (testComponent) {
                totalComponentsAdded++;
                ent->AddComponent(testComponent);

                assert(ent->ContainsComponent<ComponentA>());

                if (ent->ContainsComponent<ComponentA>()) {
                    auto com = ent->GetComponent<ComponentA>();
                    assert(com != nullptr);
                }
            }

            ++j;
        }
        entities->FreeAll();
    }

    auto end = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

    fprintf(stderr, "Took %lu ms for %lu components\n", end - start, totalComponentsAdded);

    delete entities;
    delete components;

    PASSED();
}
