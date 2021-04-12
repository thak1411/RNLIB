#include "../RN_MEMORY/rn_memory.h"
#include "test.h"

int main() {
    rn::testMemAlloc();
    rn::testMemAlloc2();
    return 0;
}

namespace rn {
    A::A() { puts("A()"); }
    A::A(int x) { printf("A(%d)\n", x); }
    A::~A() { puts("~A()"); }
    VOID testMemAlloc() {
        puts("\n\n [ TEST Memory Allocate ] ");
        puts(" > Before Make A");
        A* a = new("Alloc A") A(3);
        puts(" > After Make A");
        delete a;
        puts(" > Delete A");
        rn::getMemoryInfo(); // if (rn::getMemCount() > 0) {}
    }
    VOID testMemAlloc2() {
        puts("\n\n [ TEST Memory Allocate2 ] ");
        puts(" > Before Make A");
        A* a = new("Alloc A in 2") A(3);
        puts(" > After Make A");
        rn::getMemoryInfo(); // if (rn::getMemCount() > 0) {}
        delete a;
        puts(" > Delete A");
        rn::getMemoryInfo(); // if (rn::getMemCount() > 0) {}
    }
}