GCC = g++ -std=c++17 -g -Wall -Werror -Wextra
TEST = tests/*.cc
GCOV =--coverage
LIBA = *.a
LIBO = *.o

OS = $(shell uname)

ifeq ($(OS), Darwin)
LIBFLAGS = -lm -lgtest -lstdc++ -lgtest_main
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest  --libs gtest_main`
endif

all: clean test

test: clean
	$(GCC) $(TEST) $(LIBFLAGS)  -o test
	./test

clean:
	rm -rf *.o *.a  *.out test *.dSYM  report coverage.info *.gcda *.gcno *.txt

s21_containers.a: clean
	$(GCC) -c $(TEST)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

gcov_report: s21_containers.a
	$(GCC) $(GCOV) $(TEST) $(LIBA) -L. $(LIBA)  $(LIBFLAGS) -o test
	./test
	lcov -t "test" -c -d  ./ --no-external --output-file ./coverage.info
	genhtml ./coverage.info --output-directory ./report/
	open ./report/index.html

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config library/headers/*.h library/headers/part-1/*.h library/headers/part-2/*.h tests/*.cc
	clang-format -i library/headers/*.h library/headers/part-1/*.h library/headers/part-2/*.h tests/*.cc
	clang-format -n library/headers/*.h library/headers/part-1/*.h library/headers/part-2/*.h tests/*.cc

ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif