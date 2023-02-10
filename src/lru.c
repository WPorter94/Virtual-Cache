#include "lru.h"
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

void lru_init_queue(Set *set) {
  LRUNode *s = NULL;
  LRUNode **pp = &s;  // place to chain in the next node
  for (int i = 0; i < set->line_count; i++) {
    Line *line = &set->lines[i];
    LRUNode *node = (LRUNode *)(malloc(sizeof(LRUNode)));
    node->line = line;
    node->next = NULL;
    (*pp) = node;
    pp = &((*pp)->next);
  }
  set->lru_queue = s;
}

void lru_init(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    lru_init_queue(&sets[i]);
  }
}

void lru_destroy(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    LRUNode *p = sets[i].lru_queue;
    LRUNode *n = p;
    while (p != NULL) {
      p = p->next;
      free(n);
      n = p;
    }
    sets[i].lru_queue = NULL;
  }
}

void lru_fetch(Set *set, unsigned int tag, LRUResult *result) {
  
  // TODO:
  // Implement the LRU algorithm to determine which line in
  // the cache should be accessed.
  //

  LRUNode* node1 = set->lru_queue;
  LRUNode* node2 = node1;
  int flag = 0;

  while(node1 != NULL){
    flag = 0;
    if((node1->line->valid == 1)&&(tag == node1->line->tag)){
      flag = 1;
    }else if(node1->line->valid == 0){
      node1->line->valid = 1;
      node1->line->tag = tag;
      flag = 2;
    }else if(node1->next ==NULL){
      node1->line->tag = tag;
      flag = 3;
    }
    if(flag != 0){
      if(node1 != set->lru_queue){
          node2->next = node1->next;
          node1->next = set->lru_queue;
          set->lru_queue = node1;
      }
      if(flag == 1){
        result->access = HIT;
      }else if(flag == 2){
        result->access = COLD_MISS;
      }else if(flag == 3){
        result->access = CONFLICT_MISS;
      }
      result->line = node1->line;
      break;
    }
    node2 = node1;
    node1 = node1->next;
  }
}
