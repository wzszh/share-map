#include <stdio.h>
#include <string.h>
#include "hashmap.h"

struct user {
    char *name;
    int len;
    int age;
};

int user_compare(const void *a, const void *b, void *udata) {
    const struct user *ua = a;
    const struct user *ub = b;

    if(ua->len == ub->len) {
    	return strncmp(ua->name, ub->name, ua->len);
    }
    return -1;
}

bool user_iter(const void *item, void *udata) {
    const struct user *user = item;
    printf("%s:%d (age=%d)\n", user->name, user->len, user->age);
    return true;
}

uint64_t user_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const struct user *user = item;
    return hashmap_sip(user->name, user->len, seed0, seed1);
}

int sharemap_test() {
    // create a new hash map where each item is a `struct user`. The second
    // argument is the initial capacity. The third and fourth arguments are 
    // optional seeds that are passed to the following hash function.
    struct hashmap *map = hashmap_new(sizeof(struct user), 0, 0, 0, 
                                     user_hash, user_compare, NULL, NULL);

    // Here we'll load some users into the hash map. Each set operation
    // performs a copy of the data that is pointed to in the second argument.
    hashmap_set(map, &(struct user){ .name="Dale", .len=4, .age=44 });
    hashmap_set(map, &(struct user){ .name="Roger", .len=5, .age=68 });
    hashmap_set(map, &(struct user){ .name="Jane", .len=4, .age=47 });

    struct user *user; 
    
    printf("\n-- get some users --\n");
    user = hashmap_get(map, &(struct user){ .name="Jane", .len=4});
    printf("%s age=%d\n", user->name, user->age);

    user = hashmap_get(map, &(struct user){ .name="Roger", .len=5});
    printf("%s age=%d\n", user->name, user->age);

    user = hashmap_get(map, &(struct user){ .name="Dale", .len=4});
    printf("%s age=%d\n", user->name, user->age);

    user = hashmap_get(map, &(struct user){ .name="Tom", .len=3});
    printf("%s\n", user?"exists":"not exists");

    printf("\n-- iterate over all users (hashmap_scan) --\n");
    hashmap_scan(map, user_iter, NULL);

    printf("\n-- iterate over all users (hashmap_iter) --\n");
    size_t iter = 0;
    void *item;
    while (hashmap_iter(map, &iter, &item)) {
        const struct user *user = item;
        printf("%s (age=%d)\n", user->name, user->age);
    }

    hashmap_free(map);
}
