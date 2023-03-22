#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_ {
  int size;
  PElement *array;
  DEL_FUNC del_fun;
  COPY_FUNC cpy_fun;
  PRINT_FUNC print_fun;

} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print) {
  PAdptArray paa = (PAdptArray)malloc(sizeof(AdptArray));
  if (paa == NULL) {
    return NULL;
  }
  paa->cpy_fun = copy;
  paa->del_fun = del;
  paa->print_fun = print;
  paa->size = 0;
  paa->array = NULL;
  return paa;
}
void DeleteAdptArray(PAdptArray paa) {
  if (paa == NULL) {
    return;
  }
  for (int i = 0; i < paa->size; i++) {
    if (paa->array[i] != NULL) {
      paa->del_fun(paa->array[i]);
    }
  }
  if (paa->array != NULL) {
    free(paa->array);
  }
  free(paa);
}

Result SetAdptArrayAt(PAdptArray paa, int index, PElement element) {
  if (paa == NULL) {
    return FAIL;
  }
  PElement *newpElemArr;
  // The case the array is not initialized
  if (paa->size == 0) {
    paa->array = (PElement *)calloc((index + 1) , sizeof(PElement));
    if (paa->array == NULL) {
      paa->size = -1;
      return FAIL;
    }
  }
  // The case that we need to extend Array
  if (index >= paa->size) {
    if ((newpElemArr = (PElement *)calloc((index + 1), sizeof(PElement))) ==
        NULL) {
      paa->size = -1;	
      return FAIL;
    }
    memcpy(newpElemArr, paa->array, (paa->size) * sizeof(PElement));
    free(paa->array);
    paa->array = newpElemArr;
  }
  
  //update size and put the new element
  paa->size = (index >= paa->size) ? (index + 1) : paa->size;
  if (paa->array[index] != NULL) {
    paa->del_fun(paa->array[index]);
  }
  paa->array[index] = paa->cpy_fun(element);
  return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray paa, int index) {
  if(paa->array[index]==NULL){
    return NULL;
  }
  return paa->cpy_fun(paa->array[index]);
}

int GetAdptArraySize(PAdptArray paa) {
	if(paa==NULL){
		return -1;
	}
	return paa->size; }

void PrintDB(PAdptArray paa) {
  for (int i = 0; i < paa->size; i++) {
	if(paa->array[i]!=NULL){
		paa->print_fun(paa->array[i]);
	}
    
  }
}
