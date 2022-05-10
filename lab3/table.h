#ifndef TABLE_H
#define TABLE_H

Table *init_table(int msize2);
int insert_keyspace1(Table *table, int key, char *info);
int insert_keyspace2(Table *table, int key, char *info);
int insert(Table *table, int key1, int key2, char *info);
char *find(Table *table, int key1, int key2);
int delete(Table *table, int key1, int key2);
int delete_ks2(Table *table, int key);
char *find_ks1(Table *table, int key);
List *find_ks2(Table *table, int key);
void clear_table_mem(Table *table);
void print_table(Table *table);
int hash(int pos);

#endif
