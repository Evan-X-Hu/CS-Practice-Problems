#ifndef DICT_H
#define DICT_H

struct dnode;
struct pydict;

struct pydict* pydict_new();
void pydict_del(struct pydict* self);
int pydict_len(const struct pydict* self);
void pydict_print(struct pydict* self);
struct dnode* pydict_find(struct pydict* self, char *key);
int pydict_get(struct pydict* self, char *key);
struct pydict* pydict_put(struct pydict* self, char* key, int value);


#endif