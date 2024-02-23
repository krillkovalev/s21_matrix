CC= gcc
CFLAGS= -Wall -Werror -Wextra -g -std=c11
MATRIX= s21_*.c
OBJECTS= *.o
TEST= unit_tests/s21_*.c
CLANG= clang-format

OS = $(shell uname)

ifeq ($(OS), Darwin)
 TEST_LIBS=-lcheck
else
 TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

.PHONY: all clean test rebuild

all: s21_matrix.a test gcov_report

s21_matrix.a:
	$(CC) $(CFLAGS) -c $(MATRIX)
	ar rcs ../src/s21_matrix.a $(OBJECTS)

test: s21_matrix.a
	$(CC) $(CFLAGS) $(MATRIX) $(TEST) ../src/s21_matrix.a $(TEST_LIBS) -lm -o test
	./test

build:
	$(CC) $(CFLAGS) s21_matrix.h *.c

clean:
	rm -rf *.o *.a test *.gch *.gcno *.gcda *.info report

rebuild:
	make clean
	make all



gcov_report: s21_matrix.a
	$(CC) $(CFLAGS) --coverage $(MATRIX) $(TEST) $(TEST_LIBS) -lm -o test
	./test
	lcov -t "test" -o test_report.info -c -d . #--rc lcov_branch_coverage=1
	genhtml -o report test_report.info #--rc lcov_branch_coverage=1
	rm -rf *.o *.a  *.gch *.gcno test
	open ./report/index.html


clang_n:
	$(CLANG) -style=Google -n *.[ch]

clang_i:
	$(CLANG) -style=Google -i *.[ch]
