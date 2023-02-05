#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags


SRCS        := s21_matrix.c
TEST_SRCS	:= test.c
OBJS        := $(SRCS:.c=.o)
TEST_OBJS	:= $(TEST_SRCS:.c=.o)
EXE			:= s21_matrix

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -c -std=c11
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
TST_LIBS = -lcheck -lm -lpthread
COV_LIBS = -lgcov -coverage


#------------------------------------------------#
#   VERTER                                       #
#------------------------------------------------#

s21_matrix.o:
	$(CC) $(CFLAGS) $(SRCS) -o $@

s21_matrix.a: s21_matrix.o
	ar rc $@ $(OBJS)
	ranlib s21_matrix.a

#------------------------------------------------#
#   PEERS                                        #
#------------------------------------------------#

s21_matrix_peer:
	$(CC) $(CFLAGS) $(SRCS) $(PROFILE_FLAGS)  -o s21_matrix.o
	ar rc s21_matrix.a $(OBJS)
	ranlib s21_matrix.a

test: s21_matrix_peer
	$(CC) $(CFLAGS) $(TEST_SRCS) -o test.o
	$(CC) $(TEST_OBJS) -L. s21_matrix.a $(TST_LIBS) $(COV_LIBS) -o $@
	ranlib s21_matrix.a
	./test

gcov_report: test
	lcov -t "matrix" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf *.o *.a $(EXE)
	rm -rf *.gcno *gcda *.gcov *.info
	rm -rf test ./report