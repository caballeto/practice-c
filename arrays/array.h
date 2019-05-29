//
// Created by caballeto on 29.05.19.
//

#ifndef PRACTICE_C_ARRAY_H
#define PRACTICE_C_ARRAY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#define DEFAULT_CAPACITY 16

typedef struct {
  int* data;
  size_t size;
  size_t capacity;
} Array;

Array* array_new(size_t capacity);

void array_free(Array* array);

size_t array_size(Array *array);

size_t array_capacity(Array *array);

bool array_is_empty(Array *array);

int array_at(Array *array, size_t index);

void array_push(Array *array, int value);

void array_insert(Array *array, size_t index, int value);

void array_prepend(Array *array, int value);

int array_pop(Array *array);

int array_delete(Array *array, size_t index);

void array_remove(Array *array, int value);

int array_find(Array *array, int value);

void array_resize(Array *array, size_t capacity);

void check_address(void*);

// ===== tests =====

void run_tests();

void test_append();
void test_size_init();
void test_empty();
void test_resize();
void test_at();
void test_insert();
void test_prepend();
void test_pop();
void test_remove();
void test_find_exists();
void test_find_not_exists();


#endif //PRACTICE_C_ARRAY_H
