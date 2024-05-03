#ifndef CPP3_SMARTCALC_V2_0_2_SRC_VIEW_PLOT_WINDOW_H
#define CPP3_SMARTCALC_V2_0_2_SRC_VIEW_PLOT_WINDOW_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <iostream>

#define MAX_INPUT_SYM 300

QT_BEGIN_NAMESPACE
namespace Ui {
class PlotWindow;
}
QT_END_NAMESPACE

class PlotWindow : public QDialog {
  Q_OBJECT
 public:
  explicit PlotWindow(QWidget *parent = nullptr);
  ~PlotWindow();
 signals:
  void PlotSetup(double x_Begin, double x_End, double h, QVector<double> *x,
                 QVector<double> *y, char *err_str, int *error);
 public slots:
  void MainWindowClosed();
 private slots:
  void on_pushButton_Draw_clicked();
  void on_radioButton_Adaptive_clicked();
  void on_radioButton_Fixed_clicked();

 private:
  bool QStringToDouble(QString text, double *result);
  int StepCheck(bool *dbl_ok);
  int GraphPaint(int *error);
  Ui::PlotWindow *ui_;
  double x_begin_, x_end_, y_min_, y_max_, h_;
  QVector<double> x_vector_, y_vector_;
};

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_VIEW_PLOT_WINDOW_H
