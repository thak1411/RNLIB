#include "rn_memory.h"

#ifdef __MEMDEBUG__
namespace rn {
    /**
     * Management Memory Allocate Count
     */
    static std::vector < std::pair < LPVOID, RN_ALLOC_OWNER > > memList;
    SIZE getMemCount() { return memList.size(); }
    /**
     * Print Memory Allocated Status
     */
    VOID printMemoryInfo() {
        printf(" Not Deallocated Count: %lu\n", memList.size());
        for (int i = 0; i < memList.size(); ++i) {
            printf(" > %p By: %d\n", memList[i].first, memList[i].second);
        }
    }
}
/**
 * OverLoading New Operator For Debug Memory
 */
LPVOID operator new(SIZE_T sz, rn::RN_ALLOC_OWNER owner) {
    LPVOID block;
    if ((block = std::malloc(sz)) != NULL) rn::memList.push_back(std::make_pair(block, owner));
    else std::fprintf(stderr, "Mem Alloc Error. Owner=%d, ReqSize=%lu\n", owner, sz);
    return block;
}
/**
 * OverLoading New Operator For Debug Memory
 */
VOID operator delete(LPVOID p) noexcept {
    if (p != NULL) {
        int it = -1;
        for (int i = 0; i < rn::memList.size(); ++i) {
            if (rn::memList[i].first == p) { it = i; break; }
        }
        // TODO Fix - Called Delete Operator Not in MemList
        
        // if (it == -1) fprintf(stderr, "Mem Free Error. Can't Free Variable: %p\n", p);
        // else std::free(p), rn::memList.erase(rn::memList.begin() + it);
        std::free(p);
        if (it != -1) rn::memList.erase(rn::memList.begin() + it);
    }
}
#else // NOT(__MEMDEBUG__) //
LPVOID operator new(SIZE_T sz, rn::RN_ALLOC_OWNER owner) {
    return std::malloc(sz);
}
#endif // __MEMDEBUG__ //