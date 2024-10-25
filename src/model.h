#ifndef CPP3_SMARTCALC_V2_0_2_SRC_MODEL_H
#define CPP3_SMARTCALC_V2_0_2_SRC_MODEL_H

#include <cstring>
#include <regex>
#include <vector>

#include "model/calculator.h"

namespace s21 {

class Model {
 public:
  Model() { InputStringInit(&str_res_); }
  int CmdTranslator(const char string, char *result);
  void InitializeInString() { InputStringInit(&this->str_res_); }
  bool DeleteLex(char *result);
  int CalcRes(int grad, char *str_x, char *str_input, char *result);
  int PlotSetup(char *input_copy, double x_begin, double x_end, double h,
                std::vector<double> *x_vector, std::vector<double> *y_vector,
                bool grad);

 private:
  int CalcMain(int grad, char *str_x, char *str_input, double *result);
  int ModelRegExpSearch(char *str, const char *input_pattern);
  InputString str_res_;
  double x_;
};

}  // namespace s21

#endif  //  CPP3_SMARTCALC_V2_0_2_SRC_MODEL_H
