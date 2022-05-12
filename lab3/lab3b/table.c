#include "struct.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Data malloc_ks2(finfo *file, int size) { 
    Data data;
    data.pos = file->first_free_pos;
    data.size = sizeof(KeySpace2);

    KeySpace2 ks2;
    ks2.busy = 0;

    fseek(file->f, 0, data.pos);
    for (int i = 0; i < size; ++i) {
        fwrite(&ks2, sizeof(KeySpace2), 1, file->f);
    }
    
    file->first_free_pos = ftell(file->f);
    return data;
}

KeySpace2 read_elem_ks2(finfo *file, Data d, int index) {
    KeySpace2 ks2;
    fseek(file->f, index * d.size, d.pos);
    fread(&ks2, d.size, 1, file->f);

    return ks2;
}

Table *init_table(finfo *file, int msize2) {
    Table *table = (Table *)malloc(sizeof(Table));
    table->msize2 = msize2;
    table->ks2 = malloc_ks2(file, msize2);

    return table;
}

void update_ks2(finfo *file, Data d, int index, int busy, int key, char *info) {
    KeySpace2 ks2 = read_elem_ks2(file, d, index);

    Data dinfo;
    dinfo.pos = file->first_free_pos;
    dinfo.size = strlen(info) * sizeof(char);
    ks2.info = dinfo;

    fseek(file->f, dinfo.pos, 0);
    fwrite(info, dinfo.size, 1, file->f);

    file->first_free_pos = ftell(file->f);

    ks2.key = key;
    ks2.busy = busy;
    ks2.info = dinfo;

    fseek(file->f, index * d.size, d.pos);
    fwrite(&ks2, d.size, 1, file->f);
}

char *get_info_from_data(finfo *file, Data d) {
    fseek(file->f, d.pos, 0);
    char *info = (char *)malloc(d.size);
    fread(info, d.size, 1, file->f);
    return info;
}

int hash(int pos) {
    return pos % 10;
}

// int key_exists_ks1(Table *table, int key) {
//     KeySpace1 *ks = table->ks1;
//     while (ks != NULL) {
//         if (ks->key == key) {
//             return 1;
//         }
//         ks = ks->next;
//     }

//     return 0;
// }

Data malloc_ks1(finfo *file, int key, char *info, Data next) {
    KeySpace1 ks1;
    ks1.next = next;
    ks1.key = key;

    Data dinfo;
    dinfo.pos = file->first_free_pos;
    dinfo.size = strlen(info) * sizeof(char);
    ks1.info = dinfo;

    fseek(file->f, dinfo.pos, 0);
    fwrite(info, dinfo.size, 1, file->f);

    file->first_free_pos = ftell(file->f);


    Data d;
    d.pos = file->first_free_pos;
    d.size = sizeof(ks1);

    fseek(file->f, d.pos, 0);
    fwrite(&ks1, d.size, 1, file->f);
}

int insert_ks1(Table *table, finfo *file, int key, char *info) {
    Data next = table->ks1;
    // if (table->ks1 != (Data)NULL) {
    //     // if (key_exists_ks1(table, key)) {
    //     //     printf("KeySpace1 key already exists\n");
    //     //     return 1;
    //     // }
    // }
    table->ks1 = malloc_ks1(file, key, info, next);

    return 0;
}

int insert_ks2(Table *table, finfo *file, int key, char *info) {
    int pos = hash(key), start_pos = pos;
    while (read_elem_ks2(file, table->ks2, pos).busy != 0) {
        pos = (pos + 1) % table->msize2;
        if (pos == start_pos) {
            printf("Table full");
            return 1;
        }
    }

    update_ks2(file, table->ks2, pos, 1, key, info);

    return 0;
}

int insert(Table *table, finfo *file, int key1, int key2, char *info) {
    int status;
    status = insert_ks1(table, file, key1, info);
    if (status == 1) return 1;

    status = insert_ks2(table, file, key2, info);
    if (status == 1) return 1;

    return 0;
}

// KeySpace1 *get_elem_ks1(KeySpace1 *ks, char *info) {
//     KeySpace1 *cur_elem = ks;
//     while (cur_elem != NULL) {
//         if (!strcmp(info, cur_elem->info)) return cur_elem;
//         cur_elem = cur_elem->next;
//     }
//     return NULL;
// }

// int get_elem_ks2(KeySpace2 *ks, int msize2, char *info) {
//     for (int i = 0; i < msize2; ++i) {
//         if (ks[i].busy == 1 && !strcmp(ks[i].info, info)) return i;
//     }
//     return -1;
// }

// void print_table(Table *table) {
//     for (int i = 0; i < table->msize2; ++i) {
//         if (table->ks2[i].busy == 1) {
//             KeySpace1 *ks1 = get_elem_ks1(table->ks1, table->ks2[i].info);
//             printf("(%d, %d) -> %s\n", ks1->key, table->ks2[i].key, ks1->info);
//         }
//     }
// }

// char *find(Table *table, int key1, int key2) {
//     KeySpace1 *cur_elem = table->ks1;
//     while (cur_elem != NULL) {
//         if (cur_elem->key == key1) return cur_elem->info;
//         cur_elem = cur_elem->next;
//     }
//     return NULL;
// }

// char *find_ks1(Table *table, int key) {
//     KeySpace1 *cur_elem = table->ks1;
//     while (cur_elem != NULL) {
//         if (cur_elem->key == key) return cur_elem->info;
//         cur_elem = cur_elem->next;
//     }
//     return NULL;
// }

// List *find_ks2(Table *table, int key) {
//     List *lst = (List *)malloc(sizeof(List));
//     lst->head = NULL;

//     Node *cur_elem;
//     int pos = hash(key), start_pos = pos;
//     while (table->ks2[pos].busy == 1) {
//         if (table->ks2[pos].key == key) {
//             Node *new_node = (Node *)malloc(sizeof(Node));
//             new_node->info = table->ks2[pos].info;
//             new_node->next = NULL;
//             if (lst->head == NULL) {
//                 lst->head = new_node;
//                 cur_elem = new_node;
//             } else {
//                 cur_elem->next = new_node;
//                 cur_elem = cur_elem->next;
//             }
//         }

//         pos = (pos + 1) % table->msize2;
//         if (pos == start_pos) break;
//     }

//     return lst;
// }

// int delete(Table *table, int key1, int key2) {
//     char *info = NULL;
//     KeySpace1 *parent = NULL;
//     KeySpace1 *cur_elem = table->ks1;
//     while (cur_elem != NULL) {
//         if (cur_elem->key == key1) {
//             info = cur_elem->info;
//             break;
//         }
//         parent = cur_elem;
//         cur_elem = cur_elem->next;
//     }

//     if (info == NULL) {
//         printf("No such key in KeySpace1");
//         return 1;
//     }

//     int index = get_elem_ks2(table->ks2, table->msize2, info);
//     if (index == -1) {
//         printf("No such key in KeySpace2");
//         return 1;
//     }

//     table->ks2[index].busy = 0;
//     if (parent != NULL) {
//         parent->next = cur_elem->next;
//     } else {
//         table->ks1 = cur_elem->next;
//     }
//     free(cur_elem);
//     return 0;
// }

// int delete_ks2(Table *table, int key) {
//     int pos = hash(key), start_pos = pos, found = 0;
//     while (table->ks2[pos].busy == 1) {
//         if (table->ks2[pos].key == key) {
//             found = 1;
//             table->ks2[pos].busy = 0;

//             KeySpace1 *parent = NULL;
//             KeySpace1 *cur_elem = table->ks1;
//             while (cur_elem != NULL) {
//                 if (!strcmp(table->ks2[pos].info, cur_elem->info)) {
//                     KeySpace1 *cur_elem_copy = cur_elem;
//                     if (parent != NULL) {
//                         parent->next = cur_elem->next;
//                     } else {
//                         table->ks1 = cur_elem->next;
//                     }
//                     cur_elem = cur_elem->next;
//                     free(cur_elem_copy);
//                 } else {
//                     parent = cur_elem;
//                     cur_elem = cur_elem->next;
//                 }
                
//             }
            
//         }

//         pos = (pos + 1) % table->msize2;
//         if (pos == start_pos) break;
//     }

//     if (!found) {
//         printf("No such key in KeySpace2");
//         return 1;
//     }

//     return 0;
// }