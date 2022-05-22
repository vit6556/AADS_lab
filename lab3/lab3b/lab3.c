#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "table.h"

int main() {
    int status;
    finfo *file = malloc(sizeof(finfo));
    file->f = fopen("data.bin", "wb+");
    file->first_free_pos = 0;

    Table *table = init_table(file, 10);


    status = insert(table, file, 13, 27, "cat", 1);
    status = insert(table, file, 12, 27, "dog", 0);
    status = insert(table, file, 36, 17, "sheep", 0);
    status = insert(table, file, 57, 46, "fish", 0);

    printf("Table printing:\n");
    print_table(file, table);

    int key1 = 13, key2 = 27;
    printf("\nFind by 2 keys(%d, %d):\n", key1, key2);
    char *info = find(file, table, key1, key2);
    printf("(%d, %d) -> %s\n", key1, key2, info);
    free(info);

    int key = 57;
    printf("\nFind by KeySpace1 key %d:\n", key);
    info = find_ks1(file, table, key);
    printf("%d -> %s\n", key, info);
    free(info);

    key = 27;
    printf("\nFind by KeySpace2 key %d:\n", key);
    List *lst = find_ks2(file, table, key);
    while (lst->head != NULL) {
        printf("%d -> %s\n", key, lst->head->info);
        Node *tmp = lst->head;
        lst->head = lst->head->next;
        free(tmp->info);
        free(tmp);
    }
    free(lst);

    key1 = 36;
    key2 = 17;
    printf("\nDelete by 2 keys(%d, %d):\n", key1, key2);
    delete(file, table, key1, key2);
    print_table(file, table);



    key = 27;
    printf("\nDelete by KeySpace2 key %d:\n", key);
    delete_ks2(file, table, key);
    print_table(file, table);

    fclose(file->f);
    free(table);
    free(file);
    return 0;
}