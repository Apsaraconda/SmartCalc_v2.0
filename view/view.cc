#include "view.h"

#include "ui_view.h"

namespace s21 {

View::View(Controller *c)
    : QMainWindow(),
      ui_(new Ui::View),
      plot_(new PlotWindow(nullptr)),
      controller_(c) {
  ui_->setupUi(this);
  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_plus, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(DigitsNumbers()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_Br_open, SIGNAL(clicked()), this,
          SLOT(DigitsNumbers()));
  connect(ui_->pushButton_Br_close, SIGNAL(clicked()), this,
          SLOT(DigitsNumbers()));
  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(ui_->pushButton_expo, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
  connect(this, &View::WindowClosedSignal, &plot_,
          &::PlotWindow::MainWindowClosed);
  connect(&plot_, &::PlotWindow::PlotSetup, this, &View::PlotSetup);
}

View::~View() { delete ui_; }

void View::DigitsNumbers() {
  QPushButton *digit_button = (QPushButton *)sender();
  QString line_digit = digit_button->text();
  char set_string[MAX_INPUT_SYM + 1];
  int line_length = line_digit.length();
  char str_digit[line_length + 1];
  QStringToChar(line_digit, str_digit);
  controller_->ButtonsCommands(str_digit, set_string);
  ui_->lineInput->setText(set_string);
}

void View::on_pushButton_eq_clicked() {
  QString line_ok = ui_->lineEdit_X->text();
  int line_ok_length = line_ok.length();
  char str_x[line_ok_length + 1];
  QStringToChar(line_ok, str_x);
  QString line_in = ui_->lineInput->text();
  int line_length = line_in.length();
  char input_copy[line_length + 1];
  QStringToChar(line_in, input_copy);
  char set_string[MAX_INPUT_SYM + 1];
  controller_->ButtonEqClicked(grad_, str_x, input_copy, set_string);
  ui_->lineOutput->setText(set_string);
}

void View::on_pushButton_Clear_clicked() {
  controller_->ClearInputStr();
  ui_->lineInput->setText("");
}

void View::on_pushButton_Del_clicked() {
  char set_string[MAX_INPUT_SYM + 1];
  bool del_char = 0;
  del_char = controller_->ButtonDelClicked(set_string);
  if (del_char) ui_->lineInput->setText(set_string);
}

void View::on_pushButton_All_Clear_clicked() {
  on_pushButton_Clear_clicked();
  ui_->lineOutput->setText("");
  ui_->lineEdit_X->setText("");
}

void View::on_pushButton_open_plot_clicked() { plot_.show(); }

void View::on_radioButton_Rad_clicked() {
  ui_->radioButton_Rad->setChecked(1);
  ui_->radioButton_Grad->setChecked(0);
  grad_ = 0;
}

void View::on_radioButton_Grad_clicked() {
  ui_->radioButton_Rad->setChecked(0);
  ui_->radioButton_Grad->setChecked(1);
  grad_ = 1;
}

void View::PlotSetup(double x_begin, double x_end, double h, QVector<double> *x,
                     QVector<double> *y, char *err_str, int *error) {
  QString line_in = ui_->lineInput->text();
  int line_length = line_in.length();
  char input_string[line_length + 1];
  QStringToChar(line_in, input_string);
  controller_->PlotSetup(input_string, x_begin, x_end, h, x, y, grad_, err_str,
                         error);
  if (error) ui_->lineOutput->setText(err_str);
}

void View::QStringToChar(QString line_in, char *input_string) {
  int line_length = line_in.length();
  if (line_length > 0) {
    QByteArray button_in = line_in.toLocal8Bit();
    char *input_copy = button_in.data();
    strncpy(input_string, input_copy, line_length);
    input_string[line_length] = '\0';
  } else {
    *input_string = '\0';
  }
}

}  // namespace s21
