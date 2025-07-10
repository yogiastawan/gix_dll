#ifndef __GIX_DLL_H__
#define __GIX_DLL_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct GixNode GixNode;

typedef struct {
    size_t data_size;
    GixNode *head;
    GixNode *tail;
    size_t size;
} GixDLL;

#define gix_dll_new(T) (__internal_gix_dll_new)(sizeof(T))

GixDLL *__internal_gix_dll_new(size_t data_size);
#define __internal_gix_dll_new(...) \
    Do not call this function direcly.Use gix_dll_new(Type type)

GixNode *gix_dll_append(GixDLL *gdll, const void *val);
GixNode *gix_dll_prepend(GixDLL *gdll, const void *val);
GixNode *gix_dll_insert_after(GixDLL *gdll, GixNode *node, const void *val);
GixNode *gix_dll_insert_before(GixDLL *gdll, GixNode *node, const void *val);
void gix_dll_remove(GixDLL *gdll, GixNode *node);
void gix_dll_destroy(GixDLL *gdll);
void gix_dll_print(GixDLL *gdll, void (*print_fn)(const void *));

const void *gix_node_get_value(GixNode *node);
void gix_node_set_value(GixDLL *gdll, GixNode *node, const void *val);
GixNode *gix_node_prev(GixNode *node);
GixNode *gix_node_next(GixNode *node);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __GIX_DLL_H__
