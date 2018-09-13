.PHONY: all clean

CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Werror -fsanitize=undefined

all: validator solution

validator: CXXFLAGS += -O0 -isystem ../include
validator: validator.cpp

solution: solution.cpp

clean:
	$(RM) validator solution
