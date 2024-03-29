#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;
typedef	int HashType;
typedef int KeyType;

typedef struct hashnode_t {
    HashType val;
    struct hashnode_t *next;
    KeyType key;
} HashNode;

typedef struct hashhead_t {
    HashNode *first;
    int size;
} HashHead;

typedef struct hashmap_t {
    HashHead *values;
    int length;
    int size;
} HashMap;

void hashmapForEach(HashMap *map)
{
    int i;
    HashNode *node;
    HashType *value;
    for (i = 0; i < map->size; i++) {
        node = map->values[i].first;
        while (node) {
            printf("key = %d val = %d\n", node->key, node->val);
            node = node->next;
        }
    }
}

/*static inline uint _hashmapHash(KeyType key)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*key)
        hash = hash * seed + (*key++);

    return (hash & 0x7FFFFFFF);
}

static inline int _hashmapKeyEqual(KeyType key1, KeyType key2)
{
    return !strcmp(key1, key2);
}

static inline void _hashmapKeyCopy(HashNode *node, KeyType key)
{
    int size;
    size = strlen(key) + 1;
    node->key = (char *)malloc(size);
    strcpy(node->key, key);
}*/

static inline uint _hashmapHash(KeyType key)
{
	return key > 0 ? key : -key;
}

static inline int _hashmapKeyEqual(KeyType key1, KeyType key2)
{
	return key1 == key2;
}

static inline void _hashmapKeyCopy(HashNode *node, KeyType key)
{
	node->key = key;
}

HashMap *hashmapCreate(int size)
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    int i;
    map->length = size;
    map->values = (HashHead *)malloc(sizeof(HashHead) * map->length);
    for (i = 0; i < size; i++) {
        map->values[i].first = NULL;
        map->values[i].size = 0;
    }
    map->size = 0;
    return map;
}

void hashmapPut(HashMap *map, KeyType key, HashType val)
{
    uint index = _hashmapHash(key) % map->length;
    HashNode *node, *curr, *last;
    if (map->values[index].size == 0) {
        node = (HashNode *)malloc(sizeof(HashNode));
        node->next = NULL;
        node->val = val;
        _hashmapKeyCopy(node, key);
        map->values[index].first = node;
    } else {
        curr = map->values[index].first;
        while (curr->next) {
            if (_hashmapKeyEqual(key, curr->key)) {
                curr->val = val;
                return;
            }
            curr = curr->next;
        }
        if (_hashmapKeyEqual(key, curr->key)) {
            curr->val = val;
            return;
        }
        node = (HashNode *)malloc(sizeof(HashNode));
        node->next = NULL;
        node->val = val;
        _hashmapKeyCopy(node, key);
        curr->next = node;
    }
    map->values[index].size++;
    map->size++;
}

int getSize(HashMap *map)
{
    return map->size;
}

void hashmapRemove(HashMap *map, KeyType key)
{
    uint index = _hashmapHash(key) % map->length;
    HashNode *node;
    HashNode *temp;
    if (!map->values[index].size) {
        return;
    }
    if (_hashmapKeyEqual(map->values[index].first->key, key)) {
        temp = map->values[index].first;
        map->values[index].first = temp->next;
        free(temp);
        map->values[index].size--;
        map->size--;
        return;
    }
    node = map->values[index].first;
    while (node->next) {
        if (_hashmapKeyEqual(node->next->key, key)) {
            temp = node->next;
            node->next = temp->next;
            free(temp);
            map->values[index].size--;
            map->size--;
            return;
        }
        node = node->next;
    }
}

HashType *hashmapGet(HashMap *map, KeyType key)
{
    uint index = _hashmapHash(key) % map->length;
    HashNode *node = map->values[index].first;
    while (node) {
        if (_hashmapKeyEqual(node->key, key))
            return &node->val;
        node = node->next;
    }
    return NULL;
}
