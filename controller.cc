#include "controller.h"

namespace s21 {

void Controller::ButtonsCommands(const char *str_digit, char *str_res) {
  int error = 0;
  if (!strcmp(str_digit, "sin")) {
    error = model_->CmdTranslator('s', str_res);
  } else if (!strcmp(str_digit, "cos")) {
    error = model_->CmdTranslator('c', str_res);
  } else if (!strcmp(str_digit, "tan")) {
    error = model_->CmdTranslator('t', str_res);
  } else if (!strcmp(str_digit, "mod")) {
    error = model_->CmdTranslator('m', str_res);
  } else if (!strcmp(str_digit, "log")) {
    error = model_->CmdTranslator('g', str_res);
  } else if (!strcmp(str_digit, "asin")) {
    error = model_->CmdTranslator('a', str_res);
  } else if (!strcmp(str_digit, "acos")) {
    error = model_->CmdTranslator('o', str_res);
  } else if (!strcmp(str_digit, "atan")) {
    error = model_->CmdTranslator('n', str_res);
  } else if (!strcmp(str_digit, "sqrt")) {
    error = model_->CmdTranslator('q', str_res);
  } else if (!strcmp(str_digit, "ln")) {
    error = model_->CmdTranslator('l', str_res);
  } else if (!strcmp(str_digit, "*10^y")) {
    error = model_->CmdTranslator('e', str_res);
  } else {
    error = model_->CmdTranslator(*str_digit, str_res);
  }
  if (error) {
    strncpy(str_res, "Error: Input string is too large", MAX_INPUT_SYM);
  }
}

void Controller::ClearInputStr() { model_->InitializeInString(); }

bool Controller::ButtonDelClicked(char *str_res) {
  bool del_char = 0;
  del_char = model_->DeleteLex(str_res);
  return del_char;
}

void Controller::ButtonEqClicked(bool grad, char *str_x, char *str_input,
                                 char *str_res) {
  int error = 0;
  error = model_->CalcRes(grad, str_x, str_input, str_res);
  if (error) ErrorStr(error, str_res);
}

void Controller::PlotSetup(char *input_copy, double x_begin, double x_end,
                           double h, QVector<double> *x, QVector<double> *y,
                           bool grad, char *str_res, int *error) {
  std::vector<double> x_std;
  std::vector<double> y_std;
  *error =
      model_->PlotSetup(input_copy, x_begin, x_end, h, &x_std, &y_std, grad);
  *x = QVector<double>(x_std.begin(), x_std.end());
  *y = QVector<double>(y_std.begin(), y_std.end());
  if (error) ErrorStr(*error, str_res);
}

void Controller::ErrorStr(int error, char *str_res) {
  if (error == 1) {
    strncpy(str_res, "Error: Input string is too large", MAX_INPUT_SYM);
  } else if (error == 2) {
    strncpy(str_res, "Error: Division by zero", MAX_INPUT_SYM);
  } else if (error == 3) {
    strncpy(str_res, "Error: Incorrect \"x\"", MAX_INPUT_SYM);
  } else if (error == 4) {
    strncpy(str_res, "Please, set \"x\"", MAX_INPUT_SYM);
  } else if (error == 5) {
    strncpy(str_res, "Error: Incorrect brackets number", MAX_INPUT_SYM);
  } else if (error == 6) {
    strncpy(str_res, "Error: Incorrect expression", MAX_INPUT_SYM);
  }
}

}  // namespace s21
