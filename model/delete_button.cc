#include "calculator.h"

//  Функция удаляет с конца строки символы по лексемам, либо один символ из
//  result->res_str
void DeleteButton(InputString *result) {
  int success = 0;
  int len = strlen(result->res_str);
  if (len >= 2) {
    char pattern[4] = "ln$";
    if (CRegExpSearch(pattern, result->res_str))
      DeleteChars(result, 2, &success);
  }
  if (len >= 4 && !success) {
    char pattern[4][7];
    int search = 0;
    strncpy(pattern[0], "asin$", 6);
    strncpy(pattern[1], "acos$", 6);
    strncpy(pattern[2], "atan$", 6);
    strncpy(pattern[3], "sqrt$", 6);
    for (int i = 0; i < 4; i++) {
      search = search + CRegExpSearch(pattern[i], result->res_str);
    }
    if (search) DeleteChars(result, 4, &success);
  }
  if (len >= 3 && !success) {
    char pattern[5][6];
    int search = 0;
    strncpy(pattern[0], "sin$", 5);
    strncpy(pattern[1], "cos$", 5);
    strncpy(pattern[2], "tan$", 5);
    strncpy(pattern[3], "mod$", 5);
    strncpy(pattern[4], "log$", 5);
    for (int i = 0; i < 5; i++) {
      search = search + CRegExpSearch(pattern[i], result->res_str);
    }
    if (search) DeleteChars(result, 3, &success);
  }
  if (!success) {
    result->res_str[result->char_counter - 1] = '\0';
    result->char_counter--;
  }
}

int CRegExpSearch(char *pattern, char *string) {
  int result = 0;
  regex_t preg;
  int regerr;
  regerr = regcomp(&preg, pattern, REG_EXTENDED);
  regmatch_t pm;
  regerr = regexec(&preg, string, 0, &pm, 0);
  if (!regerr) result = 1;
  regfree(&preg);
  return result;
}

void DeleteChars(InputString *string, int amount, int *success) {
  for (int i = 1; i < (amount + 1); i++)
    string->res_str[string->char_counter - i] = '\0';
  string->char_counter -= amount;
  *success = *success + 1;
}
