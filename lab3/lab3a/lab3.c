#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "table.h"

int main() {
    int status;

    Table *table = init_table(100);
    status = insert(table, 13, 27, "cat");
    status = insert(table, 12, 27, "dog");
    status = insert(table, 36, 17, "sheep");
    status = insert(table, 57, 46, "fish");

    printf("Table printing:\n");
    print_table(table);

    int key1 = 13, key2 = 27;
    printf("\nFind by 2 keys(%d, %d):\n", key1, key2);
    char *info = find(table, key1, key2);
    printf("(13, 27) -> %s\n", info);

    int key = 57;
    printf("\nFind by KeySpace1 key %d:\n", key);
    info = find_ks1(table, key);
    printf("%d -> %s\n", key, info);

    key = 27;
    printf("\nFind by KeySpace2 key %d:\n", key);
    List *lst = find_ks2(table, key);
    while (lst->head != NULL) {
        printf("%d -> %s\n", key, lst->head->info);
        Node *tmp = lst->head;
        lst->head = lst->head->next;
        free(tmp);
    }
    free(lst);

    key1 = 36;
    key2 = 17;
    printf("\nDelete by 2 keys(%d, %d):\n", key1, key2);
    delete(table, key1, key2);
    print_table(table);

    key = 27;
    printf("\nDelete by KeySpace2 key %d:\n", key);
    delete_ks2(table, key);
    print_table(table);

    clear_table_mem(table);
    return 0;
}