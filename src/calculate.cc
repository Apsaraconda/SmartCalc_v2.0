#include "calculator.h"

int Calculate(char *source, double *result, unsigned Grad) {
  int error = 0;
  double temp = 0;
  int len = strlen(source);
  char buffer[MAX_INPUT_SYM];
  StackNumber stack_num;
  StackNumInit(&stack_num);
  DotChange(source, ',', '.');
  memcpy(buffer, source, len);
  buffer[len] = '\0';
  int position;
  position = strcspn(buffer, " ");
  int src_position = position;
  while (src_position < len && !error) {
    if (IsNumber(buffer[position - 1])) {
      sscanf(buffer, "%lf", &temp);
      error = PushNum(&stack_num, temp);
      int j = 0;
      int src_pos_temp = src_position;
      while (source[src_pos_temp + 1] != '\0') {
        buffer[j] = source[src_pos_temp + 1];
        j++;
        src_pos_temp++;
      }
      buffer[j] = '\0';
    } else if (IsOperator(buffer[position - 1]) ||
               IsFuncShort(buffer[position - 1])) {
      error = CalcLex(buffer[position - 1], &stack_num, &temp, Grad);
      int k = 0;
      int src_pos_temp = src_position;
      while (source[src_pos_temp + 1] != '\0') {
        buffer[k] = source[src_pos_temp + 1];
        k++;
        src_pos_temp++;
      }
      buffer[k] = '\0';
    }
    position = strcspn(buffer, " ");
    src_position += position + 1;
  }
  *result = temp;
  return error;
}

void DotChange(char *string, char symb_src, char symb_dest) {
  int k = 0;
  while ((string[k] != '\0')) {
    if (string[k] == symb_src) {
      (string[k]) = symb_dest;
    }
    k++;
  }
}

void StackNumInit(StackNumber *stack) {
  for (int i = 0; i < MAX_INPUT_SYM; i++) {
    stack->data[i] = 0;
  }
  stack->size = 0;
}

int PushNum(StackNumber *stack, double value) {
  int error = 0;
  if (stack->size >= MAX_INPUT_SYM) {
    error = 1;
  } else {
    stack->data[stack->size] = value;
    stack->size++;
  }
  return error;
}

double PopNum(StackNumber *stack) {
  stack->size--;
  double number = stack->data[stack->size];
  return number;
}

int CalcLex(char a, StackNumber *stack_num, double *result, unsigned Grad) {
  int error = 0;
  double operand_2 = PopNum(stack_num);
  error = UnarOperation(operand_2, a, stack_num, result, Grad);
  error = BinarOperation(operand_2, a, stack_num, result);
  return error;
}

int UnarOperation(double operand_2, char a, StackNumber *stack_num,
                  double *result, unsigned Grad) {
  int error = 0;
  switch (a) {
    case 'l':
      *result = log(operand_2);
      error = PushNum(stack_num, *result);
      break;
    case 's':
      if (Grad) operand_2 = operand_2 * PI / 180;
      *result = sin(operand_2);
      if (*result <= 1e-13 && *result >= -1e-13) *result = round(*result);
      error = PushNum(stack_num, *result);
      break;
    case 'c':
      if (Grad) operand_2 = operand_2 * PI / 180;
      *result = cos(operand_2);
      if (*result <= 1e-13 && *result >= -1e-13) *result = round(*result);
      error = PushNum(stack_num, *result);
      break;
    case 't':
      if (Grad) operand_2 = operand_2 * PI / 180;
      *result = tan(operand_2);
      if (*result > 286411383e5 || (*result < -286411383e5))
        *result = INFINITY;
      else if (*result <= 1e-13 && *result >= -1e-13)
        *result = round(*result);
      error = PushNum(stack_num, *result);
      break;
    case 'g':
      *result = log10(operand_2);
      error = PushNum(stack_num, *result);
      break;
    case 'a':
      if (Grad) operand_2 = operand_2 * PI / 180;
      *result = asin(operand_2);
      error = PushNum(stack_num, *result);
      break;
    case 'o':
      if (Grad) operand_2 = operand_2 * PI / 180;
      *result = acos(operand_2);
      error = PushNum(stack_num, *result);
      break;
    case 'n':
      if (Grad) operand_2 = operand_2 * PI / 180;
      *result = atan(operand_2);
      error = PushNum(stack_num, *result);
      break;
    case 'q':
      *result = sqrt(operand_2);
      error = PushNum(stack_num, *result);
      break;
  }
  return error;
}

int BinarOperation(double operand_2, char a, StackNumber *stack_num,
                   double *result) {
  int error = 0;
  double operand_1;
  switch (a) {
    case '^':
      operand_1 = PopNum(stack_num);
      *result = pow(operand_1, operand_2);
      error = PushNum(stack_num, *result);
      break;
    case '*':
      operand_1 = PopNum(stack_num);
      *result = operand_1 * operand_2;
      error = PushNum(stack_num, *result);
      break;
    case '/':
      if (operand_2 >= 0.0000001 ||
          operand_2 <= -0.0000001) {  //  деление на нуль
        operand_1 = PopNum(stack_num);
        *result = operand_1 / operand_2;
        error = PushNum(stack_num, *result);
      } else {
        error = 2;
      }
      break;
    case 'm':
      operand_1 = PopNum(stack_num);
      *result = fmod(operand_1, operand_2);
      error = PushNum(stack_num, *result);
      break;
    case '+':
      operand_1 = PopNum(stack_num);
      *result = operand_1 + operand_2;
      error = PushNum(stack_num, *result);
      break;
    case '-':
      operand_1 = PopNum(stack_num);
      *result = operand_1 - operand_2;
      error = PushNum(stack_num, *result);
      break;
    case '~':
      operand_1 = PopNum(stack_num);
      *result = operand_1 - operand_2;
      error = PushNum(stack_num, *result);
      break;
  }
  return error;
}

int IsFuncShort(char str) {
  int result = 0;
  if (str == 's' || str == 'c' || str == 't' || str == 'a' || str == 'o' ||
      str == 'n' || str == 'q' || str == 'l' || str == 'g' || str == 'm') {
    result = 1;
  }
  return result;
}
