#include "hashtable.h"

int main() {
  table* t = new_table();

  table_insert(t, "c", "d");
  print_table(t);

  del_table(t);
}