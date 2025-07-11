#include <assert.h>
#include <gix_dll/gix_dll.h>
#include <stdio.h>

static void print_dll_int(const void *data);

int main(int argc, char *argv[]) {
    // setbuf(stdout, NULL);
    GixDLL *gdll = gix_dll_new(int);

    int a = 10, b = 20, c = 5, d = 30, e = 15, f = 25, g = 60;
    GixNode *node_a = gix_dll_append(gdll, &a);
    GixNode *node_b = gix_dll_append(gdll, &b);
    GixNode *node_c = gix_dll_prepend(gdll, &c);
    GixNode *node_d = gix_dll_insert_after(gdll, node_a, &d);
    GixNode *node_e = gix_dll_insert_after(gdll, node_b, &e);
    GixNode *node_f = gix_dll_insert_before(gdll, node_c, &f);

    gix_dll_print(gdll, print_dll_int);
    // [25, 5, 10, 30, 20, 15]

    assert(gdll->size == 6);
    gix_dll_remove(gdll, node_a);
    assert(gdll->size == 5);
    assert(b == *(int *)gix_node_get_value(node_b));
    assert(c == *(int *)gix_dll_get_value_at(gdll, 1));
    gix_dll_print(gdll, print_dll_int);
    // [25, 5, 30, 20, 15]

    gix_dll_remove_at(gdll, 1);  // **REMOVE NODE_C**
    gix_dll_print(gdll, print_dll_int);
    // [25, 30, 20, 15]
    bool res = gix_node_set_value(
        node_c,
        &g);  // false because node_c is already removed in **REMOVE NODE_C**
    assert(!res);

    gix_dll_set_value_at(gdll, 1, &g);
    gix_dll_print(gdll, print_dll_int);
    // [25, 60, 20, 15]

    gix_dll_destroy(gdll);
    return 0;
}

static void print_dll_int(const void *data) {
    printf("%d", *(int *)data);
    // fflush(stdout);
}
