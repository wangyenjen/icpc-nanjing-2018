.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/tree

INPUTS += inputs/02.txt
INPUTS += inputs/03.txt
INPUTS += inputs/04.txt

OUTPUTS += outputs/01-sample.txt
OUTPUTS += outputs/02.txt
OUTPUTS += outputs/03.txt
OUTPUTS += outputs/04.txt

all: validator solution $(INPUTS) $(OUTPUTS)

validator: validator.cpp

solution: CXXFLAGS += -O2
solution: solution.cpp

$(GENERATORS): %: %.cpp

$(INPUTS): validator
inputs/02.txt: generators/tree
	generators/tree random 99999 > $@
	./validator < $@
inputs/03.txt: generators/tree
	generators/tree linear 33333 random 66666 > $@
	./validator < $@
inputs/04.txt: generators/tree
	generators/tree star 33333 random 66666 > $@
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	prlimit -s-1 ./solution < $< > $@

clean:
	$(RM) validator solution $(GENERATORS) $(INPUTS) $(OUTPUTS)
