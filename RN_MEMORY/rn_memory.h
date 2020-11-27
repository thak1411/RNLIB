#ifndef __RN_MEMORY_H__
#define __RN_MEMORY_H__

#include "../RN_UTIL/rn_lib.h"
#include "../RN_UTIL/rn_type.h"

#include <utility>  // std::pair //
#include <cstdlib>  // std::malloc, std::free //
#include <cstdio>   // printf, fprintf, puts //
#include <string>   // std::string //
#include <vector>   // std::vector //

#define __STRICT__ // Show All Memory Alloc & DeAlloc //

#ifdef __MEMDEBUG__
namespace rn {
    /**
     * ManageMent Memory Allocated Data
     */
    static std::vector < std::pair < LPVOID, std::string > > memList;
    SIZE_T getMemoryCount() { return memList.size(); }
    /**
     * Print Memory Allocated Count
     */
    VOID getMemoryInfo() {
        puts("\n [ MEMORY INFO ]\n");
        printf("Not Deallocated Count: %lu\n", rn::memList.size());
        for (INT i = 0; i < rn::memList.size(); ++i) {
            printf(" > %p - By %s\n", rn::memList[i].first, rn::memList[i].second.c_str());
        }
    }
}
/**
 * Overloading New Operator For Debug Memory
 * T* t = new("DEBUG MESSAGE") T;
 */
LPVOID operator new(SIZE_T sz, std::string owner) {
    LPVOID block;
    if ((block = std::malloc(sz)) != NULL) rn::memList.push_back(std::make_pair(block, owner));
    else fprintf(stderr, "Mem Alloc Error. Req=%lu, Owner=%s\n", sz, owner.c_str());
#ifdef __STRICT__
    printf("Alloc: %p - By %s\n", block, owner.c_str());
#endif // __STRICT__ //
    return block;
}
/**
 * Overloading New[] Operator For Debug Memory
 * T* t = new("DEBUG MESSAGE") T[N];
 */
LPVOID operator new[](SIZE_T sz, std::string owner) {
    LPVOID block;
    if ((block = std::malloc(sz)) != NULL) rn::memList.push_back(std::make_pair(block, owner));
    else fprintf(stderr, "Mem Alloc Error. Req=%lu, Owner=%s\n", sz, owner.c_str());
#ifdef __STRICT__
    printf("Alloc: %p - By %s\b\n", block, owner.c_str());
#endif // __STRICT__ //
    return block;
}
/**
 * Overloading Delete Operator For Debug Memory
 * delete t;
 */
VOID operator delete(LPVOID block) noexcept {
    if (block == NULL) return;
    INT ax = -1;
    for (INT i = 0; i < rn::memList.size(); ++i) {
        if (rn::memList[i].first == block) ax = i;
    }
#ifdef __STRICT__
    if (ax != -1) printf("Delete: %p - By %s\n", block, rn::memList[ax].second.c_str());
#endif // __STRICT__ //
    if (ax != -1) rn::memList.erase(rn::memList.begin() + ax);
    std::free(block);
}
/**
 * Overloading Delete[] Operator For Debug Memory
 * delete[] t;
 */
VOID operator delete[](LPVOID block) noexcept {
    if (block == NULL) return;
    INT ax = -1;
    for (INT i = 0; i < rn::memList.size(); ++i) {
        if (rn::memList[i].first == block) ax = i;
    }
#ifdef __STRICT__
    if (ax != -1) printf("Delete: %p - By %s\n", block, rn::memList[ax].second.c_str());
#endif // __STRICT__ //
    if (ax != -1) rn::memList.erase(rn::memList.begin() + ax);
    std::free(block);
}
#else // NOT(__MEMDEBUG__) //
/**
 * Default New Operator
 */
LPVOID operator new(SIZE_T sz, LPCSTR owner) {
    return std::malloc(sz);
}
#endif // __MEMDEBUG__ //

#endif // __RN_MEMORY_H__ //