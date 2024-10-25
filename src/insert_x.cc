#include "calculator.h"

//  Функция находит x в тексте source и вставляет вместо него произвольную
//  строку string Копирует получившийся текст в массив src_struct->input_res_str
//  Присваивает src_struct->char_counter длину строки source
int InsertX(char *string, char *source) {
  int error = 0;
  int len_str = strlen(string);
  int len_src = strlen(source);
  int position = strcspn(source, "x");
  if ((string[0] == '\0' || !len_str) && position < len_src) error = 4;
  if (len_str + len_src <= MAX_INPUT_SYM) {
    while (position < len_src && !error) {
      char buffer[MAX_INPUT_SYM];
      for (int i = 0; i < MAX_INPUT_SYM; i++) buffer[i] = '\0';
      int position_copy = position;
      CopySourceToBuffer(len_src, position, &position_copy, source, buffer);
      InsertXToSource(&position_copy, source, string);
      if ((position_copy + strlen(buffer)) <= MAX_INPUT_SYM) {
        strncat(source, buffer,
                MAX_INPUT_SYM);  //  Вставляем остаток в source из buffer
      } else {
        error = 1;
      }
      position = strcspn(source, "x");
    }
  } else {
    error = 1;
  }
  return error;
}

//  Копирует остаток source в buffer
void CopySourceToBuffer(int len_src, int position, int *position_copy,
                        char *source, char *buffer) {
  int buf_index = 0;
  while (*position_copy + 1 != len_src && source[*position_copy + 1] != '\0') {
    buffer[buf_index] = source[*position_copy + 1];
    buf_index++;
    *position_copy = *position_copy + 1;
  }
  buffer[buf_index] = '\0';
  *position_copy = position;
  source[*position_copy] = '(';
  *position_copy = *position_copy + 1;
}

//  Вставляет string вместо x
void InsertXToSource(int *position_copy, char *source, char *string) {
  for (int i = 0; string[i] != '\0'; i++) {
    source[*position_copy] = string[i];
    *position_copy = *position_copy + 1;
  }
  source[*position_copy] = ')';
  *position_copy = *position_copy + 1;
  source[*position_copy] = '\0';
}
