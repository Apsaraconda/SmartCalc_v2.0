# SmartCalc_v2.0

SmartCalc is an ingeneer calculator app.

v2.0 provides type XeY exponential notation and fixes some bugs.

The program structure has been changed in accordance with the MVC design pattern and Google Style requirements.

![](https://github.com/Apsaraconda/SmartCalc_v2.0/blob/main/assets/preview.gif)

## Requirements:
- Ubuntu or MacOS operating system;
- Qt version 6+ (e.g. qt-6-base-dev for Ubuntu);

## Basic properties:
- Both integers and real numbers with a dot can be input into the program.
- Calculating arbitrary bracketed arithmetic expressions in infix notation;
- Calculate arbitrary bracketed arithmetic expressions in infix notation with substitution of the value of the variable _x_ as a number;
- Plotting a graph of a function given by an expression in infix notation with the variable _x_ (with coordinate axes, mark of the used scale and an adaptive grid);
- Domain and codomain of a function are limited to at least numbers from -1000000 to 1000000;
- Verifiable accuracy of the fractional part is at least to 7 decimal places;
- Users able to enter up to 300 characters;
  
    - **Arithmetic operators**:

      | Operator name | Infix notation <br /> (Classic) |
      | --------- | ------ |
      | Brackets | (a + b) |
      | Addition | a + b |
      | Subtraction | a - b |
      | Multiplication | a * b |
      | Division | a / b |
      | Power | a ^ b |
      | Modulus | a mod b |
      | Unary plus | +a |
      | Unary minus | -a |


    - **Functions**:
  
      | Function description | Function |
      | ------ | ------ |
      | Computes cosine | cos(x) |
      | Computes sine | sin(x) |
      | Computes tangent | tan(x) |
      | Computes arc cosine | acos(x) |
      | Computes arc sine | asin(x) |
      | Computes arc tangent | atan(x) |
      | Computes square root | sqrt(x) |
      | Computes natural logarithm | ln(x) |
      | Computes common logarithm | log(x) |
      
## Compilation:

Ubuntu or MacOS and Qmake v.6+ required.

Use "make" command:
```
make install
```
## Uninstall:
```
make uninstall
```
Or delete app's directory.

## Run:
```
make run
```
Or manually open "3D_Viewer" file.

## Zip compiled program:
```
make dist
```
It makes "dist_3DViewer.tar.gz" file.

## Compile and open readme.dvi:
```
make dvi
```
If you have not installed "latex" command:
```
make latex_install
```
