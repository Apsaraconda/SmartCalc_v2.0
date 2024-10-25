#include "calculator.h"

//  Функция присваивает нули данным в структуре InputString *result
void InputStringInit(InputString *result) {
  for (int i = 0; i < MAX_INPUT_SYM; i++) result->res_str[i] = '\0';
  result->char_counter = 0;
}

//  Функция добавляет в массив result->res_str символы по лексемам
//  которые выбираются в соответствии с поступаемым символам string
int InputTranslator(char string, InputString *result) {
  int error = 0;
  if (result->char_counter < MAX_INPUT_SYM - 1) {
    char pattern_e[39] = "[0-9,]+[e][-+]?[0-9]*$";
    char pattern_dot[20] = "[,]+[[:digit:]]*$";
    int ExpoExpression = CRegExpSearch(pattern_e, result->res_str);
    if ((string == 's' || string == 'c' || string == 't' || string == 'm' ||
         string == 'g') &&
        !ExpoExpression) {
      error = WriteFunc4(string, result);
    } else if ((string == 'a' || string == 'o' || string == 'n' ||
                string == 'q') &&
               !ExpoExpression) {
      error = WriteFunc5(string, result);
    } else if ((string == 'l') && !ExpoExpression) {
      error = WriteFunc3(result);
    } else if ((string == ',' || string == '.') && !ExpoExpression &&
               !CRegExpSearch(pattern_dot, result->res_str)) {
      if ((result->char_counter == 0) ||
          ((result->char_counter > 0) &&
           (result->res_str[result->char_counter - 1] != ')'))) {
        result->res_str[result->char_counter] = ',';
        result->char_counter++;
      }
    } else if (string >= '0' && string <= '9') {
      if (result->char_counter == 0) {
        WriteChar(string, result);
      } else if (result->char_counter > 0) {
        if (result->res_str[result->char_counter - 1] != 'x' &&
            result->res_str[result->char_counter - 1] != ')')
          WriteChar(string, result);
      }
    } else if (string == 'x' && !ExpoExpression) {
      if (result->char_counter == 0) {
        WriteChar(string, result);
      } else if (result->char_counter > 0) {
        if (!IsNumber(result->res_str[result->char_counter - 1]) &&
            result->res_str[result->char_counter - 1] != ')')
          WriteChar(string, result);
      }
    } else if (string == 'e' && !ExpoExpression) {
      error = WriteExponent(result);
    } else if (IsOperator(string) == 1 &&
               string != 'm') {  //  если вводим оператор
      WriteOperNotBrackets(string, result);
    } else if ((string == '(' && !ExpoExpression) ||
               string == ')') {  //  если вводим скобку
      WriteBrackets(string, result);
    }
  } else {
    error = 1;
  }
  return error;
}

int WriteFunc4(char string, InputString *result) {
  int error = 0;
  char write[5] = "sin(";
  if (string == 'c') strcpy(write, "cos(");
  if (string == 't') strcpy(write, "tan(");
  if (string == 'm') strcpy(write, "mod(");
  if (string == 'g') strcpy(write, "log(");
  if (result->char_counter < MAX_INPUT_SYM - 4) {
    if (result->char_counter == 0) {
      WriteLex(write, result);
    } else if (result->char_counter > 0) {
      if ((IsOperator(result->res_str[result->char_counter - 1]) ||
           result->res_str[result->char_counter - 1] == '(') &&
          (result->res_str[result->char_counter - 1] != ')') &&
          (string != 'm') &&
          !IsNumber(result->res_str[result->char_counter - 1])) {
        WriteLex(write, result);
      } else if ((string == 'm') &&
                 ((result->res_str[result->char_counter - 1] == ')') ||
                  IsNumber(result->res_str[result->char_counter - 1]))) {
        WriteLex(write, result);
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int WriteFunc5(char string, InputString *result) {
  int error = 0;
  char write[6] = "asin(";
  if (string == 'o') strcpy(write, "acos(");
  if (string == 'n') strcpy(write, "atan(");
  if (string == 'q') strcpy(write, "sqrt(");
  if (result->char_counter < MAX_INPUT_SYM - 5) {
    if (result->char_counter == 0) {
      WriteLex(write, result);
    } else if (result->char_counter > 0) {
      if ((IsOperator(result->res_str[result->char_counter - 1]) ||
           result->res_str[result->char_counter - 1] == '(') &&
          (result->res_str[result->char_counter - 1] != ')') &&
          !IsNumber(result->res_str[result->char_counter - 1])) {
        WriteLex(write, result);
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int WriteFunc3(InputString *result) {
  int error = 0;
  if (result->char_counter < MAX_INPUT_SYM - 3) {
    char ln[4] = "ln(";
    if (result->char_counter == 0) {
      WriteLex(ln, result);
    } else if (result->char_counter > 0) {
      if ((IsOperator(result->res_str[result->char_counter - 1]) ||
           result->res_str[result->char_counter - 1] == '(') &&
          (result->res_str[result->char_counter - 1] != ')') &&
          (!IsNumber(result->res_str[result->char_counter - 1]))) {
        WriteLex(ln, result);
      }
    }
  } else {
    error = 1;
  }
  return error;
}

int WriteExponent(InputString *result) {
  int error = 0;
  if (result->char_counter < MAX_INPUT_SYM - 2) {
    char ln[2] = "e";
    if (result->char_counter > 0 &&
        IsNumber(result->res_str[result->char_counter - 1])) {
      WriteLex(ln, result);
    }
  } else {
    error = 1;
  }
  return error;
}

void WriteOperNotBrackets(char string, InputString *result) {
  if (result->char_counter > 0) {
    if (IsNumber(result->res_str[result->char_counter - 1]) ||
        result->res_str[result->char_counter - 1] ==
            ')') {  //  если вводим после чисел или скобок
      WriteChar(string, result);
    } else if (IsOperator(result->res_str[result->char_counter - 1]) ==
               1) {  //  если уже вводили оператор - переписываем
      if ((result->char_counter > 1 &&
           (result->res_str[result->char_counter - 2] != '(' &&
            result->res_str[result->char_counter - 2] != 'e' &&
            (string != '+' && string != '-'))) ||
          (result->char_counter > 0 && (string == '+' || string == '-'))) {
        result->char_counter--;
        result->res_str[result->char_counter] = string;
        result->char_counter++;
      }
    } else if (result->res_str[result->char_counter - 1] == '(') {
      if (string == '+' || string == '-')  //  записываем + или -
        WriteChar(string, result);
    }
  } else if (!result->char_counter) {  //  если еще не ввели число
    if (string == '+' || string == '-')  //  записываем + или -
      WriteChar(string, result);
  }
}

void WriteBrackets(char string, InputString *result) {
  if (string == '(') {
    if (!result->char_counter) {
      WriteChar(string, result);
    } else if (!IsNumber(result->res_str[result->char_counter - 1]) &&
               (result->res_str[result->char_counter - 1] != ')')) {
      WriteChar(string, result);
    }
  } else {  // (string == ')')
    if (result->char_counter > 0 &&
        result->res_str[result->char_counter - 1] != '(' &&
        result->res_str[result->char_counter - 1] != 'e' &&
        IsOperator(result->res_str[result->char_counter - 1]) != 1)
      WriteChar(string, result);
  }
}

void WriteLex(char *str, InputString *result) {
  for (int i = 0; str[i] > '\0' && str[i] < '\177'; i++) {
    result->res_str[result->char_counter] = str[i];
    result->char_counter++;
  }
}

void WriteChar(char str, InputString *result) {
  result->res_str[result->char_counter] = str;
  result->char_counter++;
}
