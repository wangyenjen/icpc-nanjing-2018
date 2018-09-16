.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/tree

EXTRAS += extras/wa-1
EXTRAS += extras/wa-2

INPUTS += inputs/02.txt
INPUTS += inputs/03.txt
INPUTS += inputs/04.txt
INPUTS += inputs/06.txt
INPUTS += inputs/07.txt

OUTPUTS += outputs/01-sample.txt
OUTPUTS += outputs/02.txt
OUTPUTS += outputs/03.txt
OUTPUTS += outputs/04.txt
OUTPUTS += outputs/05-wa-1.txt
OUTPUTS += outputs/06.txt
OUTPUTS += outputs/07.txt

all: validator solution $(INPUTS) $(OUTPUTS) $(EXTRAS)

solution: CXXFLAGS += -O2

validator solution $(GENERATORS) $(EXTRAS): %: %.cpp

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
inputs/06.txt: generators/tree
	generators/tree linear 33333 star 22222 random 44444 > $@
	./validator < $@
inputs/07.txt: generators/tree
	generators/tree linear 35000 parent 0 linear 9999 parent 0 linear 9999 parent 0 linear 9999 random 34999 > $@
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	prlimit -s-1 ./solution < $< > $@

clean:
	$(RM) validator solution $(GENERATORS) $(EXTRAS) $(INPUTS) $(OUTPUTS)
