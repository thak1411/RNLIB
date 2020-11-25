#ifndef __RN_TEST_H__
#define __RN_TEST_H__

#include "../RN_UTIL/rn_type.h"

namespace rn {
    class A {
    public:
        A();
        A(int);
        ~A();
    };
    VOID testMemAlloc();
    VOID testMemAlloc2();
}

#endif // __RN_TEST_H__ //