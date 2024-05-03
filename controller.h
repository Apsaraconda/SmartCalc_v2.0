#ifndef CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_H

#include <QVector>

#include "model.h"

namespace s21 {

class Controller {
 public:
  Controller();
  Controller(Model *m) : model_(m){};
  void ButtonsCommands(const char *str_digit, char *str_res);
  void ClearInputStr();
  bool ButtonDelClicked(char *str_res);
  void ButtonEqClicked(bool grad, char *str_x, char *str_input, char *str_res);
  void PlotSetup(char *input_copy, double x_begin, double x_end, double h,
                 QVector<double> *x, QVector<double> *y, bool grad,
                 char *str_res, int *error);
  void ErrorStr(int error, char *str_res);

 private:
  Model *model_;
};
}  // namespace s21

#endif  //  CPP3_SMARTCALC_V2_0_2_SRC_CONTROLLER_H
