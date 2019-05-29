//
// Created by caballeto on 29.05.19.
//

#include "array.h"

Array* array_new(size_t capacity) {
  if (capacity < DEFAULT_CAPACITY) capacity = DEFAULT_CAPACITY;

  Array* array = malloc(sizeof(Array));
  check_address(array);

  array->size = 0;
  array->capacity = capacity;
  array->data = (int*) malloc(capacity * sizeof(int));

  return array;
}

void array_free(Array* array) {
  free(array->data);
  free(array);
}

size_t array_size(Array *array) {
  return array->size;
}

size_t array_capacity(Array *array) {
  return array->capacity;
}

bool array_is_empty(Array *array) {
  return array->size == 0;
}

int array_at(Array *array, size_t index) {
  return *(array->data + index);
}

void array_push(Array *array, int value) {
  if (array->data == NULL) {
    array_resize(array, DEFAULT_CAPACITY);
    array->data[array->size++] = value;
  } else {
    if (array->size == array->capacity)
      array_resize(array, 2*array->capacity);
    array->data[array->size++] = value;
  }
}

void array_insert(Array *array, size_t index, int value) {
  if (array->size == array->capacity) {
    array_resize(array, 2*array->capacity);
  }

  for (size_t i = index; i < array->size; i++)
    *(array->data + (i + 1)) = *(array->data + i);

  *(array->data + index) = value;
  array->size++;
}

void array_prepend(Array *array, int value) {
  if (array->data == NULL) {
    array_resize(array, DEFAULT_CAPACITY);
    array->data[array->size++] = value;
  } else {
    if (array->size == array->capacity)
      array_resize(array, 2*array->capacity);
    for (size_t i = 0; i < array->size; i++)
      *(array->data + i + 1) = *(array->data + i);
    *array->data = value;
  }
}

int array_pop(Array *array) {
  if (array_is_empty(array)) exit(EXIT_FAILURE);
  int value = array->data[array->size--];
  if (array->size < array->capacity/4) {
    array_resize(array, array->capacity/2);
  }

  return value;
}

int array_delete(Array *array, size_t index) {
  if (index > array->size) exit(EXIT_FAILURE);
  int value = *(array->data + index);
  for (size_t i = index; i < array->size - 1; i++) {
    *(array->data + i) = *(array->data + i + 1);
  }
  array->data[--array->size] = 0;
  if (array->size < array->capacity/4) {
    array_resize(array, array->capacity/2);
  }

  return value;
}

void array_remove(Array *array, int value) {
  for (size_t i = 0; i < array->size; i++) {
    int v = *(array->data + i);
    if (v == value) {
      array_delete(array, i);
      i--;
    }
  }
}

int array_find(Array *array, int value) {
  for (int i = 0; i < array->size; i++)
    if (*(array->data + i) == value)
      return i;
  return -1;
}

void array_resize(Array *array, size_t capacity) {
  array->capacity = capacity;
  if (array->data == NULL) {
    array->data = (int*) malloc(capacity * sizeof(int));
    check_address(array->data);
    array->size = 0;
  } else {
    int* new_data = (int*) malloc(capacity * sizeof(int));
    check_address(new_data);
    memcpy(new_data, array->data, sizeof(int) * array->size);
    free(array->data);
    array->data = new_data;
  }
}

void check_address(void* p) {
  if (p == NULL) {
    printf("ERROR: Could not allocate memory.");
    exit(EXIT_FAILURE);
  }
}

// ===== tests =====

void run_tests() {
  test_size_init();
  test_append();
  test_empty();
  test_resize();
  test_at();
  test_insert();
  test_prepend();
  test_pop();
  test_remove();
  test_find_exists();
  test_find_not_exists();
}


void test_size_init() {
  Array* array = array_new(4);
  size_t size = array_size(array);
  assert(size == 0);
  array_free(array);
}

void test_append() {
  Array *aptr = array_new(2);
  array_push(aptr, 2);
  array_push(aptr, 12);
  int new_size = array_size(aptr);
  assert(new_size == 2);
  array_free(aptr);
}

void test_resize() {
  Array *aptr = array_new(2);

  int old_capacity = array_capacity(aptr);
  assert(old_capacity == 16);

  // forces a resize up
  for (int i = 0; i < 18; ++i) {
    array_push(aptr, i + 1);
  }

  assert(array_capacity(aptr) == 32);

  // forces a resize down
  for (int j = 0; j < 15; ++j) {
    array_pop(aptr);
  }

  assert(array_capacity(aptr) == 8);

  array_free(aptr);
}

void test_empty() {
  Array *aptr = array_new(2);
  bool empty = array_is_empty(aptr);
  assert(empty == 1);
  array_push(aptr, 1);
  empty = array_is_empty(aptr);
  assert(empty == 0);
  array_free(aptr);
}

void test_at() {
  Array *aptr = array_new(12);
  for (int i = 0; i < 12; ++i) {
    array_push(aptr, i + 3);
  }
  assert(array_at(aptr, 6) == 9);
  array_free(aptr);
}

void test_insert() {
  Array *aptr = array_new(5);
  for (int i = 0; i < 5; ++i) {
    array_push(aptr, i + 5);
  }
  array_insert(aptr, 2, 47);
  assert(array_at(aptr, 2) == 47);
  assert(array_at(aptr, 3) == 7);
  array_free(aptr);
}

void test_pop() {
  Array *aptr = array_new(5);
  for (int i = 0; i < 3; ++i) {
    array_push(aptr, i + 1);
  }
  assert(aptr->size == 3);
  for (int j = 0; j < 3; ++j) {
    array_pop(aptr);
  }
  assert(array_is_empty(aptr) == 1);
  array_free(aptr);
}

void test_remove() {
  Array *aptr = array_new(5);
  array_push(aptr, 12);
  array_push(aptr, 3);
  array_push(aptr, 41);
  array_push(aptr, 12);
  array_push(aptr, 12);
  array_remove(aptr, 12);
  assert(array_size(aptr) == 2);
  array_free(aptr);
}

void test_find_exists() {
  Array *aptr = array_new(5);
  array_push(aptr, 1);
  array_push(aptr, 2);
  array_push(aptr, 3);
  array_push(aptr, 4);
  array_push(aptr, 5);
  assert(array_find(aptr, 1) == 0);
  assert(array_find(aptr, 4) == 3);
  assert(array_find(aptr, 5) == 4);
  array_free(aptr);
}

void test_find_not_exists() {
  Array *aptr = array_new(3);
  array_push(aptr, 1);
  array_push(aptr, 2);
  array_push(aptr, 3);
  assert(array_find(aptr, 7) == -1);
  array_free(aptr);
}

void test_prepend() {
  Array *aptr = array_new(5);
  for (int i = 0; i < 3; ++i) {
    array_push(aptr, i + 1);
  }
  array_prepend(aptr, 15);
  assert(array_at(aptr, 0) == 15);
  assert(array_at(aptr, 1) == 1);
  array_free(aptr);
}
