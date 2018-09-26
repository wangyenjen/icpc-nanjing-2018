.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/gen

INPUTS += inputs/02.txt
INPUTS += inputs/03.txt
INPUTS += inputs/04.txt
INPUTS += inputs/05.txt

OUTPUTS += outputs/01-sample.txt
OUTPUTS += outputs/02.txt
OUTPUTS += outputs/03.txt
OUTPUTS += outputs/04.txt
OUTPUTS += outputs/05.txt

all: validator solution tle $(INPUTS) $(OUTPUTS)

validator: validator.cpp

solution: CXXFLAGS += -O2
solution: solution.cpp
tle: tle.cpp

$(GENERATORS): %: %.cpp

$(INPUTS): validator

inputs/02.txt: generators/gen
	generators/gen 10 20 > $@ && ./validator < $@
inputs/03.txt: generators/gen
	generators/gen 1000000 1000000 > $@ && ./validator < $@
inputs/04.txt: generators/gen
	generators/gen 1000000 1000000000 > $@ && ./validator < $@
inputs/05.txt: generators/gen
	generators/gen 1000000 999999999 > $@ && ./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator solution tle $(GENERATORS) $(INPUTS) $(OUTPUTS)
