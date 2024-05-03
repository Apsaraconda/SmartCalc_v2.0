#include "plot_window.h"

#include "ui_plot_window.h"

PlotWindow::PlotWindow(QWidget *parent)
    : QDialog(parent), ui_(new Ui::PlotWindow) {
  ui_->setupUi(this);
  if (ui_->radioButton_Fixed->isChecked()) {
    ui_->lineEdit_step->setEnabled(1);
  } else if (ui_->radioButton_Adaptive->isChecked()) {
    ui_->lineEdit_step->setDisabled(1);
  }
}

PlotWindow::~PlotWindow() { delete ui_; }

void PlotWindow::on_pushButton_Draw_clicked() {
  ui_->label_errors->setText("\0");
  bool dbl_ok = QStringToDouble(ui_->lineEdit_xMin->text(), &x_begin_);
  if (dbl_ok) dbl_ok = QStringToDouble(ui_->lineEdit_xMax->text(), &x_end_);
  if (dbl_ok) dbl_ok = QStringToDouble(ui_->lineEdit_yMin->text(), &y_min_);
  if (dbl_ok) dbl_ok = QStringToDouble(ui_->lineEdit_yMax->text(), &y_max_);
  if (!dbl_ok) {
    ui_->label_errors->setText("Error: Incorrect number format");
  } else if (x_begin_ >= x_end_ || y_min_ >= y_max_) {
    ui_->label_errors->setText("Error: Incorrect range");
  } else {
    int error = StepCheck(&dbl_ok);
    if (!error && dbl_ok) {
      GraphPaint(&error);
    } else {
      if (!dbl_ok) {
        ui_->label_errors->setText("Error: Incorrect number format");
      } else if (error == 1) {
        ui_->label_errors->setText("Error: Incorrect step");
      } else if (error == 2) {
        ui_->label_errors->setText("Error: Step is too small");
      }
    }
  }
}

int PlotWindow::StepCheck(bool *dbl_ok) {
  int error = 0;
  if (ui_->radioButton_Fixed->isChecked()) {
    ui_->lineEdit_step->setEnabled(1);
    *dbl_ok = QStringToDouble(ui_->lineEdit_step->text(), &h_);
    if (h_ <= 0 || !*dbl_ok) {
      error = 1;
    } else if ((h_ > 0 && h_ < 0.01) || (h_ < 0 && h_ > -0.01) ||
               (h_ < (abs(x_begin_) + abs(x_end_)) / 10000)) {
      error = 2;
    }
  } else if (ui_->radioButton_Adaptive->isChecked()) {
    ui_->lineEdit_step->setEnabled(0);
    h_ = (abs(x_begin_) + abs(x_end_)) / 1000;
  }
  return error;
}

int PlotWindow::GraphPaint(int *error) {
  char err_str[34] = "\0";
  PlotSetup(x_begin_, x_end_, h_, &x_vector_, &y_vector_, err_str, error);
  if (!*error) {
    ui_->widget_plot->clearGraphs();
    ui_->widget_plot->xAxis->setLabel("x");
    ui_->widget_plot->yAxis->setLabel("f(x)");
    ui_->widget_plot->xAxis->setRange(x_begin_, x_end_);
    ui_->widget_plot->yAxis->setRange(y_min_, y_max_);
    ui_->widget_plot->addGraph();
    ui_->widget_plot->graph(0)->addData(x_vector_, y_vector_);
    ui_->widget_plot->replot();
    ui_->widget_plot->setInteraction(QCP::iRangeZoom, true);
    ui_->widget_plot->setInteraction(QCP::iRangeDrag, true);
    x_vector_.clear();
    y_vector_.clear();
  } else {
    ui_->label_errors->setText(err_str);
  }
  return *error;
}

bool PlotWindow::QStringToDouble(QString text, double *result) {
  bool result_ok = 0;
  QString temp = text;
  temp.replace(",", ".");
  *result = temp.toDouble(&result_ok);
  return result_ok;
}

void PlotWindow::on_radioButton_Adaptive_clicked() {
  ui_->lineEdit_step->setEnabled(0);
}

void PlotWindow::on_radioButton_Fixed_clicked() {
  ui_->lineEdit_step->setEnabled(1);
}

//  Закрывает окно, если поступает сигнал о том, что закрывается главное окно
void PlotWindow::MainWindowClosed() { close(); }
