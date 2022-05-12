#ifndef TABLE_H
#define TABLE_H

int hash(int pos);
char *get_info_from_data(finfo *file, Data d);
Table *init_table(finfo *file, int msize2);
KeySpace2 read_elem_ks2(finfo *file, Data d, int index);
int insert(Table *table, finfo *file, int key1, int key2, char *info);
void update_ks2(finfo *file, Data d, int index, int busy, int key, char *info);
#endif
