#include "calculator.h"

//  Перевод инфиксной нотации в обратную польскую
int PolishTranslator(char *string, char *result) {
  int error = 0;
  int res_index = 0;
  result[res_index] = '\0';
  for (int i = 0; i < MAX_INPUT_SYM; i++) result[i] = '\0';
  StackUnits stack;
  StackInit(&stack);
  for (int i = 0; string[i] != '\0' && !error; i++) {
    if (IsNumber(string[i]) ||
        ((string[i] == '+' || string[i] == '-') && (i > 0) &&
         (string[i - 1] == 'e'))) {  // числа помещаем на выход в строку result
      IsNumberPolish(string, result, &res_index, &i);
    } else {
      error = IsNotANumberPolish(string, &stack, result, &res_index, &i);
    }
  }
  result[res_index] = '\0';
  while (stack.size) {
    strncat(result, Pop(&stack), MAX_INPUT_SYM);
  }
  return error;
}

void IsNumberPolish(char *string, char *result, int *res_index, int *i) {
  char temp_str[MAX_INPUT_SYM * 2];
  int dot_counter = 0;
  DotToComma(string, *i);
  int j = 0;
  temp_str[j] = string[*i];
  while (string[*i + 1] != '\0' &&
         (IsNumber(string[*i + 1]) ||
          (string[*i] == 'e' &&
           (string[*i + 1] == '+' || string[*i + 1] == '-')))) {
    if ((string[*i + 1] == '.' || string[*i + 1] == ',') && dot_counter > 0) {
      *i = *i + 1;
      string[*i] = ',';
    } else {
      *i = *i + 1;
      j++;
      temp_str[j] = string[*i];
    }
  }
  while (string[*i + 1] != '\0' &&
         (IsNumber(string[*i]) ||
          (string[*i] == 'e' &&
           (string[*i + 1] == '+' ||
            string[*i + 1] ==
                '-')))) {  //  пропуск цифр после запятой исходной строки
    if (IsNumber(string[*i + 1]) ||
        (string[*i] == 'e' &&
         (string[*i + 1] == '+' || string[*i + 1] == '-'))) {
      *i = *i + 1;
    } else {
      break;
    }
  }
  temp_str[j + 1] = ' ';
  temp_str[j + 2] = '\0';
  j = 0;
  while (temp_str[j] != '\0') {
    result[*res_index] = temp_str[j];
    j++;
    *res_index = *res_index + 1;
  }
  result[*res_index] = '\0';
}

void DotToComma(char *string, int i) {
  if (string[i] == '.' || string[i] == ',') {
    string[i] = ',';
  }
}

int IsNotANumberPolish(char *string, StackUnits *stack, char *result,
                       int *res_index, int *i) {
  int error = 0;
  char temp_func_str[4];
  int parsed_symbols = IsFunction(string, *i, temp_func_str);
  if (parsed_symbols) {
    error = FuncTranslation(parsed_symbols, temp_func_str, string, stack,
                            result, i);
  } else {
    if (IsOperator(string[*i]))
      error = OperatorTranslation(temp_func_str, string, stack, result,
                                  res_index, i);
  }
  return error;
}

int FuncTranslation(int symbols_num, char *temp_func_str, char *string,
                    StackUnits *stack, char *result, int *i) {
  int error = 0;
  if ((symbols_num == 2 &&
       (!IsNumber(string[*i + 2]) && string[*i + 2] != '(' &&
        string[*i + 2] != '-' && string[*i + 2] != '+')) ||
      (symbols_num == 3 &&
       (!IsNumber(string[*i + 3]) && string[*i + 3] != '(' &&
        string[*i + 3] != '-' && string[*i + 3] != '+')) ||
      (symbols_num == 4 &&
       (!IsNumber(string[*i + 4]) && string[*i + 4] != '(' &&
        string[*i + 4] != '-' && string[*i + 4] != '+')))
    error = 6;
  if (!error) {
    if (stack->priority[stack->size - 1] >= Priority(temp_func_str[0]) &&
        (stack->priority[stack->size - 1] != 5) &&
        stack->data[stack->size - 1][0] != '^') {  //  для случая со скобками
      if (stack->size) strncat(result, Pop(stack), MAX_INPUT_SYM);
    }
    error = Push(stack, temp_func_str, Priority(temp_func_str[0]));
    *i = *i + symbols_num - 1;
  }
  return error;
}

int OperatorTranslation(char *temp_func_str, char *string, StackUnits *stack,
                        char *result, int *res_index, int *i) {
  int error = 0;
  if (string[*i] == '-' || string[*i] == '+') {  //  проверка на унарный + и -
    if (*i == 0 ||
        (string[*i - 1] && !IsNumber(string[*i - 1]) &&
         (string[*i - 1]) != ')')) {  //  string должен быть без пробелов
      strcat(result, "0 ");  //  записываем 0 перед унарным + или -
      *res_index = *res_index + 2;
      if (string[*i] == '-')
        string[*i] = '~';  //  минус меняем на знак унарного минуса
    }
  } else if (string[*i] == 'm') {
    if (((*i > 0) &&
         (((!IsNumber(string[*i - 1]) &&
            string[*i - 1] != ')'))  //  если перед mod нет числа или )
          || (!IsNumber(string[*i + 3]) && string[*i + 3] != '(' &&
              string[*i + 3] != '-' && string[*i + 3] != '+'))) ||
        (!*i))
      error = 6;
  }
  if (!error) {
    temp_func_str[0] = string[*i];
    temp_func_str[1] = ' ';
    temp_func_str[2] = '\0';
    if (stack->priority[stack->size - 1] >= Priority(string[*i]) &&
        (stack->priority[stack->size - 1] != 5) &&
        string[*i] != ')') {  //  для случая со скобками
      while (stack->size &&
             stack->priority[stack->size - 1] >= Priority(string[*i]) &&
             stack->priority[stack->size - 1] < 5) {
        strncat(result, Pop(stack), MAX_INPUT_SYM);
        *res_index = *res_index + 2;
      }
      error = Push(stack, temp_func_str, Priority(temp_func_str[0]));
    } else if (string[*i] ==
               ')') {  //  если попалась ), записываем на выход все до (
      if (stack->size > 0) {
        while (stack->size && stack->data[stack->size - 1][0] != '(') {
          strncat(result, Pop(stack), MAX_INPUT_SYM);
          *res_index = *res_index + 2;
        }
        StackDeleteUnit(stack);  //  очищаем ( из стека
      } else {
        error = 6;
      }
    } else {
      error = Push(stack, temp_func_str, Priority(temp_func_str[0]));
    }
    if (string[*i] == 'm') *i = *i + 2;
  }
  return error;
}

int IsNumber(char str) {
  int res = 0;
  if ((str >= '0' && str <= '9') || str == '.' || str == ',' || str == 'e') {
    res = 1;
  } else if (str == 'x') {
    res = 2;
  }
  return res;
}

int IsFunction(char *str, int pos, char *result) {
  int flag = 0;
  if (str[pos] == 'c' && str[pos + 1] == 'o' && str[pos + 2] == 's') {
    flag = 3;
    memcpy(result, "c ", 2);
    result[2] = '\0';
  } else if (str[pos] == 's' && str[pos + 1] == 'i' && str[pos + 2] == 'n') {
    flag = 3;
    memcpy(result, "s ", 2);
    result[2] = '\0';
  } else if (str[pos] == 't' && str[pos + 1] == 'a' && str[pos + 2] == 'n') {
    flag = 3;
    memcpy(result, "t ", 2);
    result[2] = '\0';
  } else if (str[pos] == 'a' && str[pos + 1] == 'c' && str[pos + 2] == 'o' &&
             str[pos + 3] == 's') {
    flag = 4;
    memcpy(result, "o ", 2);
    result[2] = '\0';
  } else if (str[pos] == 'a' && str[pos + 1] == 's' && str[pos + 2] == 'i' &&
             str[pos + 3] == 'n') {
    flag = 4;
    memcpy(result, "a ", 2);
    result[2] = '\0';
  } else if (str[pos] == 'a' && str[pos + 1] == 't' && str[pos + 2] == 'a' &&
             str[pos + 3] == 'n') {
    flag = 4;
    memcpy(result, "n ", 2);
    result[2] = '\0';
  } else if (str[pos] == 's' && str[pos + 1] == 'q' && str[pos + 2] == 'r' &&
             str[pos + 3] == 't') {
    flag = 4;
    memcpy(result, "q ", 2);
    result[2] = '\0';
  } else if (str[pos] == 'l' && str[pos + 1] == 'n') {
    flag = 2;
    memcpy(result, "l ", 2);
    result[2] = '\0';
  } else if (str[pos] == 'l' && str[pos + 1] == 'o' && str[pos + 2] == 'g') {
    flag = 3;
    memcpy(result, "g ", 2);
    result[2] = '\0';
  } else {
    flag = 0;
  }
  return flag;
}

int IsOperator(char str) {
  int result = 0;
  if (str == '^' || str == '+' || str == '-' || str == '~' || str == '*' ||
      str == '/' || str == 'm') {
    result = 1;
  } else if (str == '(' || str == ')') {
    result = 2;
  }
  return result;
}

void StackInit(StackUnits *stack) {
  for (int i = 0; i < MAX_INPUT_SYM; i++) {
    for (int j = 0; j < MAX_INPUT_SYM * 2; j++) {
      stack->data[i][j] = '\0';
    }
    stack->priority[i] = 0;
  }
  stack->size = 0;
}

int Push(StackUnits *stack, char *value, int priority) {
  int error = 0;
  if (stack->size >= MAX_INPUT_SYM) {
    error = 1;
  } else {
    for (int i = 0; value[i] != '\0'; i++) {
      stack->data[stack->size][i] = value[i];
    }
    stack->priority[stack->size] = priority;
    stack->size++;
  }
  return error;
}

char *Pop(StackUnits *stack) {
  stack->size--;
  char *pop_str = stack->data[stack->size];
  stack->priority[stack->size] = 0;
  return pop_str;
}

void StackDeleteUnit(StackUnits *stack) {
  stack->size--;
  stack->priority[stack->size] = 0;
  for (int i = 0; i < MAX_INPUT_SYM; i++) {
    stack->data[stack->size][i] = '\0';
  }
}

int Priority(char a) {
  int result = 0;
  switch (a) {
    case '(':
    case ')':
      result = 5;
      break;
    case '~':
      result = 4;
      break;
    case 'l':
    case 's':
    case 'c':
    case 't':
    case 'g':
    case 'a':
    case 'o':
    case 'n':
    case 'q':
      result = 3;
      break;
    case '^':
      result = 3;
      break;
    case '*':
    case '/':
    case 'm':
      result = 2;
      break;
    case '-':
    case '+':
      result = 1;
      break;
  }
  return result;
}
