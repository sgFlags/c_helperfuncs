#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int HashKeyType;
typedef char * HashValueType;

typedef struct {
	HashKeyType realKey;
	HashValueType value;
	int valid;
} HashNode;

typedef struct {
	HashNode *nodes;
	int maxSize;
	int size;
} HashMap;

HashMap *hashMapCreate(int size)
{
	int i;
	HashMap *map = (HashMap *)malloc(sizeof(HashMap));
	map->maxSize = size;
	map->size = 0;
	map->nodes = (HashNode *)malloc(sizeof(HashNode) * map->maxSize);
	for (i = 0; i < map->maxSize; i++) {
		map->nodes[i].valid = 0;
	}
	return map;
}

static inline int _hash(HashMap *map, HashKeyType key)
{
	return (key > 0 ? key : -key) % map->maxSize;
}

static inline int _keyEqual(HashKeyType key1, HashKeyType key2)
{
	return key1 == key2 ? 1 : 0;
}

static inline void _keyCopy(HashNode *node, HashKeyType *src)
{
	node->realKey = *src;
}

static inline void hashMapPut(HashMap *map, HashKeyType key, HashValueType value)
{
	int index = _hash(map, key);
	while (map->nodes[index].valid &&
		!_keyEqual(key, map->nodes[index].realKey)) {
		index = (index + 1) % map->maxSize;
	}
	if (!map->nodes[index].valid) {
		_keyCopy(&map->nodes[index], &key);
		map->size++;
	}
	map->nodes[index].value = value;
	map->nodes[index].valid = 1;
}

static inline int hashMapGetIndex(HashMap *map, HashKeyType key)
{
	int index = _hash(map, key);
	int times = 0;
	while (times < map->maxSize) {
		if (map->nodes[index].valid && _keyEqual(map->nodes[index].realKey, key))
			break;
		index = (index + 1) % map->maxSize;
		times++;
	}
	if (times >= map->maxSize)
		return -1;
	return index;
}

static inline HashValueType *hashMapGet(HashMap *map, HashKeyType key)
{
	int index = hashMapGetIndex(map, key);
	if (index < 0)
		return NULL;
	return &map->nodes[index].value;
}

static inline void hashMapRemove(HashMap *map, HashKeyType key)
{
	if (map->size <= 0)
		return;
	int index = hashMapGetIndex(map, key);
	if (index >= 0) {
		map->nodes[index].valid = 0;
		map->size--;
	}
}

static inline int getSize(HashMap *map)
{
	return map->size;
}
