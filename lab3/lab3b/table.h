#ifndef TABLE_H
#define TABLE_H

int hash(int pos);
char *get_info_from_data(finfo *file, Data d);
Table *init_table(finfo *file, int msize2);
KeySpace1 read_elem_ks1(finfo *file, Data d);
KeySpace2 read_elem_ks2(finfo *file, Data d, int index);
int insert(Table *table, finfo *file, int key1, int key2, char *info, int first);
void update_ks2(finfo *file, Data d, int index, int busy, int key, char *info);
void print_table(finfo *file, Table *table);
char *find(finfo *file, Table *table, int key1, int key2);
char *find_ks1(finfo *file, Table *table, int key);
List *find_ks2(finfo *file, Table *table, int key);
int delete(finfo *file, Table *table, int key1, int key2);
int delete_ks2(finfo *file, Table *table, int key);
KeySpace1 get_elem_ks1(finfo *file, Data ks, char *str_info);
#endif
