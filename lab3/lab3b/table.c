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

KeySpace1 read_elem_ks1(finfo *file, Data d) {
    KeySpace1 ks1;
    fseek(file->f, d.pos, 0);
    fread(&ks1, d.size, 1, file->f);

    return ks1;
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
    char *info = (char *)calloc(d.size + 1, sizeof(char));
    fread(info, d.size, 1, file->f);
    return info;
}

int hash(int pos) {
    return pos % 10;
}


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
    file->first_free_pos = ftell(file->f);
 
    return d;
}

int insert_ks1(Table *table, finfo *file, int key, char *info, int first) {
    Data next;
    if (first) {
        next.pos = -1;
        next.size = -1;
    } else {
        next = table->ks1;
    }

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

int insert(Table *table, finfo *file, int key1, int key2, char *info, int first) {
    int status;
    status = insert_ks1(table, file, key1, info, first);
    if (status == 1) return 1;

    status = insert_ks2(table, file, key2, info);
    if (status == 1) return 1;

    return 0;
}

KeySpace1 get_elem_ks1(finfo *file, Data ks, char *str_info) {
    KeySpace1 ks1;
    Data next = ks, in;
    do {
        ks1 = read_elem_ks1(file, next);
        in = ks1.info;
        next = ks1.next;
        char *str_in = get_info_from_data(file, in);
        if (!strcmp(str_in, str_info)) {
            free(str_in);
            return ks1;
        }
        free(str_in);
    } while (next.pos != -1);
}

int get_elem_ks2(finfo *file, Data ks, int msize2, char *info) {
    for (int i = 0; i < msize2; ++i) {
        KeySpace2 ks2 = read_elem_ks2(file, ks, i);
        char *str_in = get_info_from_data(file, ks2.info);
        if (ks2.busy == 1 && !strcmp(str_in, info)) {
            free(str_in);
            return i;
        }
        free(str_in);
    }
    return -1;
}

void print_table(finfo *file, Table *table) {
    for (int i = 0; i < table->msize2; ++i) {
        KeySpace2 ks2 = read_elem_ks2(file, table->ks2, i);
        if (ks2.busy == 1) {
            char *str_info = get_info_from_data(file, ks2.info);
            KeySpace1 ks1 = get_elem_ks1(file, table->ks1, str_info);
            Data in = ks1.info;
            char *str_in = get_info_from_data(file, in);
            printf("(%d, %d) -> %s\n", ks1.key, ks2.key, str_in);
            free(str_in);
            free(str_info);
        }
    }
}

char *find(finfo *file, Table *table, int key1, int key2) {
    KeySpace1 ks1;
    Data next = table->ks1;
    do {
        ks1 = read_elem_ks1(file, next);
        next = ks1.next;
        if (ks1.key == key1) {
            char *str_in = get_info_from_data(file, ks1.info);
            return str_in;
        }
    } while (next.pos != -1);
}

char *find_ks1(finfo *file, Table *table, int key) {
    KeySpace1 ks1;
    Data next = table->ks1;
    do {
        ks1 = read_elem_ks1(file, next);
        next = ks1.next;
        if (ks1.key == key) {
            char *str_in = get_info_from_data(file, ks1.info);
            return str_in;
        }
    } while (next.pos != -1);
}

List *find_ks2(finfo *file, Table *table, int key) {
    List *lst = (List *)malloc(sizeof(List));
    lst->head = NULL;

    Node *cur_elem;
    int pos = hash(key), start_pos = pos;
    KeySpace2 ks2 = read_elem_ks2(file, table->ks2, pos);
    while (ks2.busy == 1) {
        if (ks2.key == key) {
            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->info = get_info_from_data(file, ks2.info);
            new_node->next = NULL;
            if (lst->head == NULL) {
                lst->head = new_node;
                cur_elem = new_node;
            } else {
                cur_elem->next = new_node;
                cur_elem = cur_elem->next;
            }
        }

        pos = (pos + 1) % table->msize2;
        if (pos == start_pos) break;
        ks2 = read_elem_ks2(file, table->ks2, pos);
    }
    return lst;
}

int delete(finfo *file, Table *table, int key1, int key2) {
    char *info;
    KeySpace1 cur_elem, parent;
    Data cur_elem_data, parent_data;
    Data next = table->ks1;
    do {
        parent = cur_elem;
        parent_data = cur_elem_data;
        cur_elem = read_elem_ks1(file, next);
        cur_elem_data = next;
        next = cur_elem.next;
        if (cur_elem.key == key1) {
            info = get_info_from_data(file, cur_elem.info);
            break;
        }
    } while (next.pos != -1);

    if (info == NULL) {
        printf("No such key in KeySpace1");
        return 1;
    }

    int index = get_elem_ks2(file, table->ks2, table->msize2, info);
    if (index == -1) {
        printf("No such key in KeySpace2");
        return 1;
    }

    update_ks2(file, table->ks2, index, 0, 0, "");


    fseek(file->f, parent_data.pos, 0);
    KeySpace1 new_ks1 = parent;
    new_ks1 = parent;
    new_ks1.next = cur_elem.next;
    fwrite(&new_ks1, parent_data.size, 1, file->f);

    free(info);
}

int delete_ks2(finfo *file, Table *table, int key) {
    int pos = hash(key), start_pos = pos, found = 0;
    KeySpace2 ks2 = read_elem_ks2(file, table->ks2, pos);
    char *ks2_info;
    char *info;
    while (ks2.busy == 1) {
        ks2_info = get_info_from_data(file, ks2.info);
        if (ks2.key == key) {
            found = 1;
            update_ks2(file, table->ks2, pos, 0, 0, "");

            KeySpace1 cur_elem, parent;
            Data cur_elem_data, parent_data;
            Data next = table->ks1;
            do {
                parent = cur_elem;
                parent_data = cur_elem_data;
                cur_elem = read_elem_ks1(file, next);
                cur_elem_data = next;
                info = get_info_from_data(file, cur_elem.info);
                if (!strcmp(ks2_info, info)) {
                    fseek(file->f, parent_data.pos, 0);
                    KeySpace1 new_ks1 = parent;
                    new_ks1 = parent;
                    new_ks1.next = cur_elem.next;
                    fwrite(&new_ks1, parent_data.size, 1, file->f);
                }
                free(info);
                next = cur_elem.next;
            } while (next.pos != -1);
        }

        pos = (pos + 1) % table->msize2;
        if (pos == start_pos) {
            break;
        }
        ks2 = read_elem_ks2(file, table->ks2, pos);
        free(ks2_info);
    }

    if (!found) {
        printf("No such key in KeySpace2");
        return 1;
    }

    return 0;
}