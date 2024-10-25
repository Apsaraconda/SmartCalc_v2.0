#include "../model.h"

namespace s21 {

int Model::CmdTranslator(const char string, char *result) {
  int error = InputTranslator(string, &this->str_res_);
  strncpy(result, this->str_res_.res_str, MAX_INPUT_SYM - 1);
  return error;
};

bool Model::DeleteLex(char *result) {
  bool del_char = 0;
  if (str_res_.char_counter > 0) {
    DeleteButton(&str_res_);
    del_char = 1;
    strncpy(result, str_res_.res_str, MAX_INPUT_SYM - 1);
  }
  return del_char;
}

int Model::CalcRes(int grad, char *str_x, char *str_input, char *result) {
  double d_result;
  int error = CalcMain(grad, str_x, str_input, &d_result);
  if (!error) {
    char res_str[MAX_INPUT_SYM + 1];
    double temp = (int)d_result - d_result;
    if (d_result <= 1.000000000000e-13 && d_result >= -1.000000000000e-13) {
      if (d_result <= 1.000000000000e-315 && d_result >= -1.000000000000e-315) {
        sprintf(res_str, "%d", (int)d_result);
      } else {
        sprintf(res_str, "%.8e", d_result);
      }
    } else {
      if (temp > 1.000000000000e18 || temp < -1.000000000000e18) {
        sprintf(res_str, "%.8e", d_result);
      } else {
        sprintf(res_str, "%.8lf", d_result);
        int i = strlen(res_str) - 1;
        while (res_str[i] == '0' && i > 0) {
          res_str[i] = '\0';
          i--;
        }
        if (res_str[i] == '.') res_str[i] = '\0';
      }
    }
    strncpy(result, res_str, MAX_INPUT_SYM - 1);
  }
  return error;
};

int Model::CalcMain(int grad, char *str_x, char *str_input, double *result) {
  char polish[MAX_INPUT_SYM];
  int error = BracketsCheck(str_input);
  const char validate_pattern[19] = "[sdtgne*\\/^+\\-(,]$";
  const char validate_pattern_dot[19] = "[\\D][,][\\D]";
  if (ModelRegExpSearch(str_input, validate_pattern) ||
      ModelRegExpSearch(str_input, validate_pattern_dot))
    error = 6;
  if (!error) {
    const char validate_x[45] = "^[+-]{0,1}[\\d]{0,150}[.,]{0,1}[\\d]{0,150}$";
    if (!ModelRegExpSearch(str_x, validate_x)) error = 3;
  }
  if (!error) error = InsertX(str_x, str_input);
  if (!error) error = PolishTranslator(str_input, polish);
  if (!error) error = Calculate(polish, result, grad);
  return error;
}

int Model::PlotSetup(char *input_copy, double x_begin, double x_end, double h,
                     std::vector<double> *x_vector,
                     std::vector<double> *y_vector, bool grad) {
  int error = 0;
  double result = 0;
  char buffer[MAX_INPUT_SYM];
  strncpy(buffer, input_copy, MAX_INPUT_SYM - 1);
  for (x_ = x_begin; x_ <= x_end; x_ += h) {
    char str_x[MAX_INPUT_SYM];
    sprintf(str_x, "%lf", x_);
    error = CalcMain(grad, str_x, buffer, &result);
    if (error) break;
    strncpy(buffer, input_copy, MAX_INPUT_SYM - 1);
    x_vector->push_back(x_);
    y_vector->push_back(result);
  }
  return error;
}

int Model::ModelRegExpSearch(char *str, const char *input_pattern) {
  int result = 0;
  std::string source_string(str);
  const std::regex pattern(input_pattern);
  std::smatch m;
  result = std::regex_search(source_string, m, pattern);
  return result;
}

}  // namespace s21
