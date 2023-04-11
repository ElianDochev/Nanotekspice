##
## EPITECH PROJECT, 2022
## Nanotekspice Makefile
## File description:
## compiles and builds lib and the source files runs unit tests
##

NAME	=	nanotekspice

CC = g++

SRC_MAIN = Main.cpp

SRC	=	Utils/Opps.cpp 									\
		Utils/FileReader.cpp							\
		Circut/Circut.cpp								\
		Circut/Factory.cpp								\
		Parcer/Parcer.cpp								\
		Components/Interface-Abstract/AComponent.cpp	\
		Components/And.cpp								\
		Components/Or.cpp								\
		Components/Xor.cpp								\
		Components/False.cpp							\
		Components/True.cpp								\
		Components/Not.cpp								\
		Components/Input.cpp							\
		Components/Output.cpp							\
		Components/Clock.cpp							\
		Components/Nor.cpp								\
		Components/Nand.cpp								\
		Components/Inverter.cpp							\
		Components/Adder.cpp							\
		Components/Counter.cpp							\

TESTS = Tests/Utilities/TestFileReader.cpp

CXXFLAGS =   -std=c++20 -Wall -Wextra -Werror

OBJ_MAIN = $(SRC_MAIN:.cpp=.o)

OBJ = $(SRC:.cpp=.o)

TEST_OBJ = $(TESTS:.cpp=.o)

LIB_TEST = libutest.a

TEST_INCLUDE = --coverage -lcriterion -L. -lutest

TEST_NAME = unit_test

all: $(OBJ_MAIN) $(OBJ)
	$(CC) -o $(NAME) $(OBJ_MAIN) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_MAIN) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(LIB_TEST) $(TEST_NAME)

re: fclean all

unit_tests: fclean $(OBJ) $(TEST_OBJ)
		ar rc $(LIB_TEST) $(OBJ)
		$(CC) -o $(TEST_NAME) $(TEST_OBJ) $(TEST_INCLUDE) $(CFLAGS)

tests_run: unit_tests
			./$(TEST_NAME)

unit_clean: fclean
			rm -f unit_test*

.PHONY: all makelib clean fclean re
