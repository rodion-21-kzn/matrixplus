#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags


SRCS        := s21_matrix_oop.cc
TEST_SRCS	:= matrix_tests.cc
OBJS        := $(SRCS:.cc=.o)
TEST_OBJS	:= $(TEST_SRCS:.cc=.o)
EXE			:= s21_matrix_oop
LIB			:= s21_matrix_oop.a

CC          := gcc
CFLAGS      := -lstdc++ -std=c++17 -Wall -Werror -Wextra
TEST_FLAGS 	:= -lgtest -lgmock -pthread

all: test

$(LIB): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rcs $(LIB) $(OBJS)

test: $(LIB)
	$(CC) $(CFLAGS) -lgtest $(LIB) $(TEST_SRCS) -o test
	./test

clean:
	rm -rf *.o *.a $(EXE)
	rm -rf *.gcno *gcda *.gcov *.info
	rm -rf test ./report
