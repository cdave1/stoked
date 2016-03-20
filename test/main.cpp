#include "test.h"

/// TODO: Use a real cpp testing framework.
int main (int argc, char ** argv) {

    test::TestEntityPool();
    test::TestEmptyEntityPool();
    test::TestComponentPool();
    test::TestEmptyComponentPool();
    test::TestEntityComponentAttachment();
    test::TestSpeed();

    return 0;
}
