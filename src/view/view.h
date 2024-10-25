#ifndef CPP3_SMARTCALC_V2_0_2_SRC_VIEW_VIEW_H
#define CPP3_SMARTCALC_V2_0_2_SRC_VIEW_VIEW_H

#include <math.h>

#include <QMainWindow>
#include <QMouseEvent>
#include <QString>
#include <cstdio>

#include "../controller.h"
#include "plot_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT
 public:
  View(Controller *c);
  ~View();
 signals:
  void WindowClosedSignal(QCloseEvent *event);
 private slots:
  void DigitsNumbers();
  void on_pushButton_eq_clicked();
  void on_pushButton_Clear_clicked();
  void on_pushButton_Del_clicked();
  void on_pushButton_All_Clear_clicked();
  void on_pushButton_open_plot_clicked();
  void on_radioButton_Rad_clicked();
  void on_radioButton_Grad_clicked();
  void PlotSetup(double x_begin, double x_end, double h, QVector<double> *x,
                 QVector<double> *y, char *err_str, int *error);

 private:
  void QStringToChar(QString line_in, char *input_string);
  Ui::View *ui_;
  PlotWindow plot_;
  bool grad_ = 1;
  Controller *controller_;
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_2_SRC_VIEW_VIEW_H
