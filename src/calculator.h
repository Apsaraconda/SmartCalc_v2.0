#ifndef CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CALCULATOR_H
#define CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CALCULATOR_H
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SYM 300
#define PI 3.14159265358980

struct InputString {
  char res_str[MAX_INPUT_SYM];
  int char_counter;
};

struct StackUnits {
  char data[MAX_INPUT_SYM][MAX_INPUT_SYM * 2];
  size_t size;
  int priority[MAX_INPUT_SYM];
};

struct StackNumber {
  double data[MAX_INPUT_SYM];
  int size;
};

int InputTranslator(char string, InputString *result);
int WriteFunc3(InputString *result);
int WriteFunc4(char string, InputString *result);
int WriteFunc5(char string, InputString *result);
int WriteExponent(InputString *result);
void InputStringInit(InputString *result);
void WriteLex(char *str, InputString *result);
void WriteChar(char str, InputString *result);
void WriteOperNotBrackets(char string, InputString *result);
void WriteBrackets(char string, InputString *result);
int PolishTranslator(char *string, char *result);
int InsertX(char *string, char *source);
void CopySourceToBuffer(int len_src, int position, int *position_copy,
                        char *source, char *buffer);
void InsertXToSource(int *position_copy, char *source, char *string);
void DeleteButton(InputString *result);
void DeleteChars(InputString *string, int amount, int *success);
void StackInit(StackUnits *stack);
int Push(StackUnits *stack, char *value, int priority);
char *Pop(StackUnits *stack);
void StackDeleteUnit(StackUnits *stack);
int Priority(char a);
int IsNumber(char str);
int IsFunction(char *str, int position, char *result);
int IsOperator(char str);
int Calculate(char *source, double *result, unsigned Grad);
void StackNumInit(StackNumber *stack);
int PushNum(StackNumber *stack, double value);
double PopNum(StackNumber *stack);
int CalcLex(char a, StackNumber *StackNumber, double *result, unsigned Grad);
int UnarOperation(double operand_2, char a, StackNumber *stack_num,
                  double *result, unsigned Grad);
int BinarOperation(double operand_2, char a, StackNumber *stack_num,
                   double *result);
int IsFuncShort(char str);
int BracketsCheck(char *str);
void IsNumberPolish(char *string, char *result, int *res_index, int *i);
int IsNotANumberPolish(char *string, StackUnits *stack, char *result,
                       int *res_index, int *i);
int FuncTranslation(int symbols_num, char *temp_func_str, char *string,
                    StackUnits *stack, char *result, int *i);
int OperatorTranslation(char *temp_func_str, char *string, StackUnits *stack,
                        char *result, int *res_index, int *i);
void DotToComma(char *string, int i);
void DotChange(char *string, char symb_src, char symb_dest);
int CRegExpSearch(char *pattern, char *string);

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_MODEL_CALCULATOR_H
