# SmartCalc_v2.0

SmartCalc — это инженерный калькулятор для операционных систем на базе Ubuntu или MacOS.

Структура программы была разработана в соответствии с шаблоном проектирования MVC и требованиями Google Style.

![](https://github.com/Apsaraconda/SmartCalc_v2.0/blob/main/assets/preview.gif)

## Требования для компиляции:
- Операционная система на базе Ubuntu или MacOS;
- Qt версии 6+ (например, qt-6-base-dev для Ubuntu);

## Основные свойства:
- В программу можно вводить как целые, так и числа с плавающей точкой.
- Вычисление произвольных арифметических выражений в скобках в инфиксной нотации;
- Вычисление произвольных арифметических выражений в скобках в инфиксной нотации с подстановкой значения переменной _x_ в качестве числа;
- Построение графика функции, заданной выражением в инфиксной нотации с переменной _x_ (с осями координат, отметкой используемого масштаба и адаптивной сеткой);
- Область определения и область значений функции ограничены как минимум числами от -1000000 до 1000000;
- Проверяемая точность дробной части составляет не менее 7 знаков после запятой;
- Пользователи могут вводить до 300 символов;

- **Арифметические операторы**:

| Имя оператора | Инфиксная нотация <br /> (классическая) |
| --------- | ------ |
| Скобки | (a + b) |
| Сложение | a + b |
| Вычитание | a - b |
| Умножение | a * b |
| Деление | a / b |
| Степень | a ^ b |
| Модуль | a mod b |
| Унарный плюс | +a |
| Унарный минус | -a |

- **Функции**:

| Описание функции | Функция |
| ------ | ------ |
| Вычисляет косинус | cos(x) |
| Вычисляет синус | sin(x) |
| Вычисляет тангенс | tan(x) |
| Вычисляет арккосинус | acos(x) |
| Вычисляет арксинус | asin(x) |
| Вычисляет арктангенс | atan(x) |
| Вычисляет квадратный корень | sqrt(x) |
| Вычисляет натуральный логарифм | ln(x) |
| Вычисляет десятичный логарифм | log(x) |

## Компиляция:

Требуется Ubuntu или MacOS и Qmake v.6+.

Используйте команду "make":
```
make install
```
## Удаление:
```
make uninstall
```
Или удалите каталог приложения.

## Запустить:
```
make run
```
Или вручную запустить файл "3D_Viewer".

## Скомпилированная программа в формате ZIP:
```
make dist
```
Создает файл "dist_3DViewer.tar.gz".

## Скомпилировать и открыть readme.dvi:
```
make dvi
```
Если в системе не установлен "latex", можно использовать команду:
```
make latex_install
```
