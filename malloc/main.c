#include <assert.h>
#include <stdint.h>
#include <stdio.h>

// Consts
#define STACK_SIZE 32
#define HEAP_SIZE STACK_SIZE * 4
#define HEADER 4
#define LIST_SIZE 40

static uint16_t IN_USE;


// Virtual memory
typedef struct virtual_memory {
  uint8_t stack[STACK_SIZE];
  char** unmapped;
  uint8_t heap[HEAP_SIZE];

  struct {
    char** data;
    char** bss;
    char* text;
  } data_t;
} virtual_memory_t;


// Entity
typedef struct entity {
  uint8_t* ptr;
  size_t size;
} entity_t;

entity_t LIST[LIST_SIZE];

void log_list(const char* func_name) {
  printf("In function `%s`:\n", func_name);
  printf("Entities in use: %d\n", IN_USE);
  for (unsigned i = 0; i < IN_USE; i++) {
    printf("---------------------------------\n");
    printf("Entity #%u\n", i);
    printf("Pointer position: %p.\n", LIST[i].ptr);
    printf("Free space: %zu bytes\n", LIST[i].size);
  }
  printf("\n");
}

#define LOG() log_list(__func__)

entity_t* new_entity(size_t size) {
  if (LIST[0].ptr == NULL && LIST[0].size == 0) {
    static virtual_memory_t vm;
    LIST[0].ptr = vm.heap;
    LIST[0].size = HEAP_SIZE;
    IN_USE++;
    LOG();
  }

  entity_t* best = NULL;
  for (unsigned i = 0; i < IN_USE; i++) {
    if (LIST[i].size >= size) {
      if (best != NULL) {
        if (LIST[i].size < best->size) {
          best = &LIST[i];
        }
      } else {
        best = &LIST[i];
      }
    }
  }

  if (best == NULL) {
    printf("Error! Not enough memory to allocate %zu bytes", size);
  }

  assert(best != NULL);

  return best;
}


// Malloc
void* n_malloc(size_t size) {
  size += HEADER;

  assert(size <= HEAP_SIZE);

  entity_t* e = new_entity(size);

  uint8_t* start = e->ptr;
  uint8_t* user_ptr = start + HEADER;

  *start = size;

  e->ptr += size;
  e->size -= size;

  LOG();

  return user_ptr;
}


// Free
void n_free(void* ptr) {
  uint8_t* start = (uint8_t*)ptr - HEADER;

  entity_t* segm = &LIST[IN_USE];
  segm->ptr = start;
  segm->size = *start;
  IN_USE++;

  int can_merge = 1;
  while (can_merge) {
    can_merge = 0;
    entity_t* last_segm = &LIST[IN_USE - 1];
    for (int i = IN_USE - 2; i >= 0; i--) {
      if (last_segm->ptr + last_segm->size == LIST[i].ptr) {
        LIST[i].ptr = last_segm->ptr;
        LIST[i].size += last_segm->size;
        last_segm->ptr = NULL;
        last_segm->size = 0;
        IN_USE--;
        can_merge = 1;
        break;
      }
    }
  }

  LOG();
}


// Execute
void test() {
  typedef struct foo {
    int i;
    float f; 
  } foo_t;

  int* a = n_malloc(sizeof(int));
  float* b = n_malloc(sizeof(float));
  n_free(a);
  foo_t* c = n_malloc(sizeof(foo_t));
  n_free(b);
  n_free(c);
}

int main(int argc, char** argv) {
  test();

  return 0;
}
