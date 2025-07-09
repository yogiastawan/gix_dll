#ifndef __GIX_DLL_H__
#define __GIX_DLL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct GixNode GixNode;

typedef struct {
    uint64_t data_size;
    GixNode *head;
    GixNode *tail;
    uint32_t size;
} GixDLl;

#define gix_dll_new(T) (__internal_gix_dll_new)(sizeof(T))

GixDLl *__internal_gix_dll_new(uint64_t data_size);
#define __internal_gix_dll_new(...) \
    Do not call this function direcly.Use gix_dll_new(Type type)

GixNode *gix_dll_append(GixDLl *gdll, const void *val);
GixNode *gix_dll_prepend(GixDLl *gdll, const void *val);
GixNode *gix_dll_insert_after(GixDLl *gdll, GixNode *node, const void *val);
GixNode *gix_dll_insert_before(GixDLl *gdll, GixNode *node, const void *val);
void gix_dll_remove(GixDLl *gdll, GixNode *node);
void gix_dll_destroy(GixDLl *gdll);
void gix_dll_print(GixDLl *gdll, void (*print_fn)(const void *));
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __GIX_DLL_H__
