#ifndef __RN_TYPE_H__
#define __RN_TYPE_H__

typedef void               VOID;
typedef char               BYTE;
typedef char               CHAR;
typedef short              SHORT;
typedef int                INT;
typedef int                BOOL;
typedef long               LONG;
typedef long long          LLONG;
typedef float              FLOAT;
typedef double             DOUBLE;

typedef char*              LPSTR;
typedef const char*        LPCSTR;

typedef void*              LPVOID;
typedef short*             LPSHORT;
typedef int*               LPINT;
typedef long*              LPLONG;
typedef long long*         LPLLONG;
typedef float*             LPFLOAT;
typedef double*            LPDOUBLE;

typedef unsigned int       DWORD;
typedef unsigned short     WORD;

#undef  NULL
#define NULL               (LPVOID)0

#endif // __RN_TYPE_H__ //