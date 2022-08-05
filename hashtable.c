#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "prime.h"

item DELETED_ITEM = {NULL, NULL};

item* new_item(const char* key, const char* value) {
  item* i = malloc(sizeof(item));
  if (i == NULL) {
    fprintf(stderr, "fail to malloc");
    exit(1);
  }
  i->key = strdup(key);
  i->value = strdup(value);
  return i;
}

table* new_table() {
  return table_new_size(BASE_SIZE);
}

table* table_new_size(const int base_size) {
  table* t = malloc(sizeof(table));
  t->base_size = base_size;
  t->size = next_prime(t->base_size);
  t->count = 0;
  t->items = calloc((size_t)t->size, sizeof(item*));
  return t;
}

void del_item(item* i) {
  free(i->key);
  free(i->value);
  free(i);
}

void del_table(table* t) {
  for (int i = 0; i < t->size; i++) {
    item* it = t->items[i];
    if (it != NULL && it != &DELETED_ITEM)
      del_item(it);
  }
  free(t->items);
  free(t);
}

void print_table(table* t) {
  printf("--------------------------------\n");
  printf("Table Load: %d / %d                     \n", t->count, t->size);
  printf("--------------------------------\n");
  printf("%7s %5s %7s\n", "key", "", "value");
  printf("--------------------------------\n");
  for (int i = 0; i < t->size; i++) {
    item* it = t->items[i];
    if (it == NULL) {
      printf("%d %5s %5s %5s\n", i + 1, "", "", "");
    } else if (it == &DELETED_ITEM) {
      printf("%d %5s %5s %5s\n", i + 1, "DELETED", "", "DELETED");
    } else {
      printf("%d %5s %5s %5s\n", i + 1, it->key, "", it->value);
    }
  }
  printf("--------------------------------\n");
}

int naive_hash(const char* s, const int a, const int m) {
  long hash = 0;
  const int len_s = strlen(s);
  for (int i = 0; i < len_s; i++) {
    hash += (long)pow(a, len_s - (i + 1)) * s[i];
    hash = hash % m;
  }
  return (int)hash;
}

int get_hash(const char* s, const int num_buckets, const int attempt) {
  const int hash_a = naive_hash(s, PRIME_1, num_buckets);
  const int hash_b = naive_hash(s, PRIME_2, num_buckets);
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void table_insert(table* t, const char* key, const char* value) {
  const int load = t->count * 100 / t->size;
  if (load > 70) {
    resize_up(t);
  }

  item* i = new_item(key, value);

  int index = get_hash(i->key, t->size, 0);
  item* cur_item = t->items[index];
  int j = 1;
  while (cur_item != NULL && cur_item != &DELETED_ITEM) {
    // update
    if (strcmp(cur_item->key, key) == 0) {
      del_item(cur_item);
      t->items[index] = i;
      return;
    }

    index = get_hash(i->key, t->size, j);
    cur_item = t->items[index];
    j++;
  }

  t->items[index] = i;
  t->count++;
}

char* table_search(table* t, const char* key) {
  int index = get_hash(key, t->size, 0);
  item* cur_item = t->items[index];
  int j = 1;
  while (cur_item != NULL) {
    if (cur_item != &DELETED_ITEM) {
      if (strcmp(cur_item->key, key) == 0) {
        return cur_item->value;
      }
    }

    index = get_hash(key, t->size, j);
    cur_item = t->items[index];
    j++;
  }
  return NULL;
}

void table_delete(table* t, const char* key) {
  const int load = t->count * 100 / t->size;
  if (load < 20) {
    resize_down(t);
  }

  int index = get_hash(key, t->size, 0);
  item* cur_item = t->items[index];
  int j = 1;
  while (cur_item != NULL && cur_item != &DELETED_ITEM) {
    if (strcmp(cur_item->key, key) == 0) {
      del_item(cur_item);
      t->items[index] = &DELETED_ITEM;
    }

    index = get_hash(key, t->size, j);
    cur_item = t->items[index];
    j++;
  }
  t->count--;
}

void table_resize(table* t, const int base_size) {
  if (base_size < BASE_SIZE)
    return;

  table* new_table = table_new_size(base_size);
  for (int i = 0; i < t->size; i++) {
    item* it = t->items[i];
    if (it != NULL && it != &DELETED_ITEM) {
      table_insert(new_table, it->key, it->value);
    }
  }

  t->base_size = new_table->base_size;
  t->count = new_table->count;

  // since we insert old items into new_table,
  // we have to swap size and items so as
  // to successfully call del_table(new_table)
  const int tmp_size = t->size;
  t->size = new_table->size;
  new_table->size = tmp_size;

  item** tmp_items = t->items;
  t->items = new_table->items;
  new_table->items = tmp_items;

  del_table(new_table);
}

void resize_up(table* t) {
  const int new_size = t->base_size * 2;
  table_resize(t, new_size);
}

void resize_down(table* t) {
  const int new_size = t->base_size / 2;
  table_resize(t, new_size);
}