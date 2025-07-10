#include <gix_dll/gix_dll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef __internal_gix_dll_new

struct GixNode {
    void *prev;
    void *next;
    void *data;
    GixDLL *holder;
};

GixDLL *__internal_gix_dll_new(size_t data_size) {
    GixDLL *gdll = malloc(sizeof(GixDLL));

    gdll->head = NULL;
    gdll->tail = NULL;
    gdll->size = 0;
    gdll->data_size = data_size;

    return gdll;
}

GixNode *gix_dll_append(GixDLL *gdll, const void *val) {
    if (!gdll || !val) return NULL;

    GixNode *node = malloc(sizeof(GixNode));
    if (!node) return NULL;

    node->holder = gdll;

    node->data = malloc(gdll->data_size);
    if (!node->data) {
        free(node);
        return NULL;
    }
    memcpy(node->data, val, gdll->data_size);

    node->next = NULL;
    node->prev = gdll->tail;

    if (gdll->tail) {
        gdll->tail->next = node;
    } else {
        gdll->head = node;
    }

    gdll->tail = node;
    gdll->size++;

    return node;
}

GixNode *gix_dll_prepend(GixDLL *gdll, const void *val) {
    if (!gdll || !val) return NULL;

    GixNode *node = malloc(sizeof(GixNode));
    if (!node) return NULL;

    node->holder = gdll;

    node->data = malloc(gdll->data_size);
    if (!node->data) {
        free(node);
        return NULL;
    }
    memcpy(node->data, val, gdll->data_size);

    node->prev = NULL;
    node->next = gdll->head;

    if (gdll->head) {
        gdll->head->prev = node;
    } else {
        gdll->tail = node;
    }

    gdll->head = node;
    gdll->size++;

    return node;
}

GixNode *gix_dll_insert_after(GixDLL *gdll, GixNode *node, const void *val) {
    if (!gdll || !node || !val) return NULL;

    if (gdll != node->holder) {
        return NULL;
    }

    GixNode *new_node = malloc(sizeof(GixNode));
    if (!new_node) return NULL;

    new_node->holder = gdll;

    new_node->data = malloc(gdll->data_size);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }
    memcpy(new_node->data, val, gdll->data_size);

    new_node->prev = node;
    new_node->next = node->next;

    if (node->next) {
        GixNode *next = node->next;
        next->prev = new_node;
    } else {
        gdll->tail = new_node;
    }

    node->next = new_node;
    gdll->size++;

    return new_node;
}

GixNode *gix_dll_insert_before(GixDLL *gdll, GixNode *node, const void *val) {
    if (!gdll || !node || !val) return NULL;

    if (gdll != node->holder) {
        return NULL;
    }

    GixNode *new_node = malloc(sizeof(GixNode));
    if (!new_node) return NULL;

    new_node->holder = gdll;

    new_node->data = malloc(gdll->data_size);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }
    memcpy(new_node->data, val, gdll->data_size);

    new_node->prev = node->prev;
    new_node->next = node;

    if (node->prev) {
        GixNode *prev = node->prev;
        prev->next = new_node;
    } else {
        gdll->head = new_node;
    }

    node->prev = new_node;
    gdll->size++;

    return new_node;
}
void gix_dll_remove(GixDLL *gdll, GixNode *node) {
    if (!gdll || gdll->size == 0 || !node) return;

    if (gdll != node->holder) {
        return;
    }

    if (node->prev) {
        GixNode *tmp = node->prev;
        tmp->next = node->next;
    } else
        gdll->head = node->next;

    if (node->next) {
        GixNode *tmp = node->next;
        tmp->prev = node->prev;
    } else
        gdll->tail = node->prev;

    free(node);

    gdll->size--;
}

void gix_dll_destroy(GixDLL *gdll) {
    if (!gdll) return;

    GixNode *node = gdll->head;
    while (node) {
        GixNode *next = node->next;
        free(node);
        node = next;
    }

    gdll->head = NULL;
    gdll->tail = NULL;
    gdll->size = 0;

    free(gdll);
}

void gix_dll_print(GixDLL *gdll, void (*print_fn)(const void *)) {
    if (!gdll || !print_fn) {
        printf("[none]\n");
        return;
    }

    printf("[");
    GixNode *node = gdll->head;
    while (node) {
        print_fn(node->data);
        if (node->next) printf(", ");
        node = node->next;
    }
    printf("]\n");
}

const void *gix_dll_get_value_at(GixDLL *gdll, size_t index) {
    if (!gdll || index >= gdll->size) {
        return NULL;
    }

    GixNode *node;
    size_t i;

    if (index < gdll->size / 2) {
        node = gdll->head;
        i = 0;
        while (i < index && node) {
            node = node->next;
            i++;
        }
    } else {
        node = gdll->tail;
        i = gdll->size - 1;
        while (i > index && node) {
            node = node->prev;
            i--;
        }
    }

    return node->data;
}

void gix_dll_remove_at(GixDLL *gdll, size_t index) {
    if (!gdll || index >= gdll->size) {
        return;
    }

    GixNode *node;
    size_t i;

    if (index < gdll->size / 2) {
        node = gdll->head;
        i = 0;
        while (i < index && node) {
            node = node->next;
            i++;
        }
    } else {
        node = gdll->tail;
        i = gdll->size - 1;
        while (i > index && node) {
            node = node->prev;
            i--;
        }
    }
    gix_dll_remove(gdll, node);
}

const void *gix_node_get_value(GixNode *node) {
    if (!node) {
        return NULL;
    }
    return node->data;
}
void gix_node_set_value(GixNode *node, const void *val) {
    GixDLL *gdll = node->holder;
    if (!node || !gdll || !val) {
        return;
    }

    memcpy(node->data, val, gdll->data_size);
}
GixNode *gix_node_prev(GixNode *node) {
    if (!node) {
        return NULL;
    }
    return node->prev;
}
GixNode *gix_node_next(GixNode *node) {
    if (!node) {
        return NULL;
    }
    return node->next;
}
