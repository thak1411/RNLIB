#ifndef __RN_MEMORY_H__
#define __RN_MEMORY_H__

#include "../RN_UTIL/rn_lib.h"
#include "../RN_UTIL/rn_type.h"

#include <utility>  // std::pair //
#include <cstdlib>  // std::malloc, std::free //
#include <vector>   // std::vector //
#include <cstdio>   // fprintf //

namespace rn {
    enum RN_ALLOC_OWNER {
        MEMOWNER_REALLOC = 1,
        MEMOWNER_A       = 2,
    };
}

#ifdef __MEMDEBUG__
namespace rn {
    SIZE getMemCount();
    VOID printMemoryInfo();
}

LPVOID operator new(SIZE_T sz, rn::RN_ALLOC_OWNER);
VOID operator delete(LPVOID p) noexcept;
#else // NOT(__MEMDEBUG__) //
LPVOID operator new(SIZE_T sz, rn::RN_ALLOC_OWNER);
#endif // __MEMDEBUG__ //

#endif // __RN_MEMORY_H__ //