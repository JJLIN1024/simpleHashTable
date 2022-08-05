#include <stdio.h>

#include "hashtable.h"

int main() {
  table* t = new_table();
  printf("Insert from 'a' to 'h' \n");
  table_insert(t, "a", "A");
  table_insert(t, "b", "B");
  table_insert(t, "c", "C");
  table_insert(t, "d", "D");
  table_insert(t, "e", "E");
  table_insert(t, "f", "F");
  table_insert(t, "g", "G");
  table_insert(t, "h", "H");
  print_table(t);

  printf("Insert from 'i', expect table doubling \n");
  // expect table doubling
  table_insert(t, "i", "I");
  print_table(t);

  printf("Search for key 'h'... \n");
  char* result = table_search(t, "h");
  printf("value for key 'h' is: %s\n", result);

  printf("Update key 'a' value from 'A' to 'AAAA' \n");
  table_insert(t, "a", "AAAA");
  print_table(t);

  printf("Delete key from 'b' to 'h', expect table halving \n");
  table_delete(t, "b");
  table_delete(t, "c");
  table_delete(t, "d");
  table_delete(t, "e");
  table_delete(t, "f");
  table_delete(t, "g");
  table_delete(t, "h");
  print_table(t);

  del_table(t);
  return 0;
}