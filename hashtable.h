#pragma once
#define BASE_SIZE 10
#define PRIME_1 19
#define PRIME_2 53
typedef struct {
  char* key;
  char* value;
} item;

typedef struct {
  int base_size;
  int size;
  int count;
  item** items;
} table;

item* new_item(const char*, const char*);
table* new_table();
void del_item(item*);
void del_table(table*);

void print_table(table*);

int naive_hash(const char*, const int, const int);
int get_hash(const char*, const int, const int);

void table_insert(table*, const char*, const char*);
char* table_search(table*, const char*);
void table_delete(table*, const char*);

table* table_new_size(const int);
void table_resize(table*, const int);
void resize_up(table*);
void resize_down(table*);