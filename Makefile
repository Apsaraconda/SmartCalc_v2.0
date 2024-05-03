.PHONY: all clean install uninstall dvi dist test gcov_report
CC=g++ 
STDFLAGS=-Wall -Wextra -Werror -std=c++17
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
LINUX_FLAGS=-lpthread -lm -lsubunit
LIBS=-lgtest -lstdc++
DIST = $$(pwd)/../dist
DIR=../SmartCalc_v2.0#  путь установки
INSTALL_PATH = $(DIR)/opt/SmartCalc/bin/

TARGET=smartcalc.a

SRC=model/*.cc
OBJ=$(patsubst %.cc,%.o, ${SRC})

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
	QTDIR = /usr/include/x86_64-linux-gnu/qt6
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
	QTDIR = /usr/local/Qt-6.6.2/include
endif

QT_TEST_FLAGS=-DQT_NO_VERSION_TAGGING -fPIC -I$(QTDIR) -I$(QTDIR)/QtCore -I$(QTDIR)/QtGui -I$(QTDIR)/QtWidgets

all : 
	rm -rf $(DIR)
	mkdir $(DIR) && cd $(DIR) && qmake6 -o Makefile ../view/"SmartCalc.pro" && make first

install:
	rm -rf $(DIR)
	mkdir $(DIR) && cd $(DIR) && qmake6 -o Makefile ../src/view/"SmartCalc.pro" && make install INSTALL_ROOT=$(DIR)

uninstall:
	cd $(DIR) && make uninstall INSTALL_ROOT=$(DIR)
	rm -rf $(DIR)

run: 
	cd $(INSTALL_PATH) && ./SmartCalc

latex_install:
ifeq ($(OS),Linux)
	sudo apt install texlive-latex-base
	sudo apt install texlive-lang-cyrillic
	sudo fmtutil-sys --all
endif

dvi:
	latex ./readme.tex
	$(OPEN_CMD) ./readme.dvi

dist : clean
	mkdir dist
	chmod 777 dist
	rm -rf $(DIR)
	mkdir $(DIR) && cd $(DIR) && qmake6 -o Makefile ../view/"SmartCalc.pro" && make install INSTALL_ROOT=$(DIST)
	tar -czf SmartCalc.tar.gz dist


$(TARGET): ${SRC}
	$(CC) -c $(STDFLAGS) $(SRC)
	ar rc $@ *.o
	ranlib $@

clean_obj:
	rm -rf *.o
	rm -rf view/*.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report

clean: clean_lib clean_lib clean_test clean_obj
	rm -rf unit_test
	rm -rf dist/ 
	rm -rf $(DIR) 
	rm -rf SmartCalc.tar.gz
	rm -rf *.aux
	rm -rf *.dvi
	rm -rf *.log