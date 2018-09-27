.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/gen

INPUTS += inputs/03.txt
INPUTS += inputs/04.txt
INPUTS += inputs/05.txt
INPUTS += inputs/06.txt
INPUTS += inputs/07.txt
INPUTS += inputs/08.txt
INPUTS += inputs/09.txt
INPUTS += inputs/10.txt

OUTPUTS += outputs/01-sample.txt
OUTPUTS += outputs/02-sample.txt
OUTPUTS += outputs/03.txt
OUTPUTS += outputs/04.txt
OUTPUTS += outputs/05.txt
OUTPUTS += outputs/06.txt
OUTPUTS += outputs/07.txt
OUTPUTS += outputs/08.txt
OUTPUTS += outputs/09.txt
OUTPUTS += outputs/10.txt

all: validator solution tle $(INPUTS) $(OUTPUTS)

validator: validator.cpp

solution: CXXFLAGS += -O2
solution: solution.cpp
tle: CXXFLAGS += -O2
tle: tle.cpp

$(GENERATORS): %: %.cpp

$(INPUTS): validator

inputs/03.txt: generators/gen
	generators/gen 10 100 > $@ && ./validator < $@
inputs/04.txt: generators/gen
	generators/gen 10 999999 > $@ && ./validator < $@
inputs/05.txt: generators/gen
	generators/gen 100 1000000 > $@ && ./validator < $@
inputs/06.txt: generators/gen
	generators/gen 100 999999 > $@ && ./validator < $@
inputs/07.txt: generators/gen
	generators/gen 1000000 1000000 > $@ && ./validator < $@
inputs/08.txt: generators/gen
	generators/gen 1000000 999999 > $@ && ./validator < $@
inputs/09.txt: generators/gen
	generators/gen 1000000 999998 > $@ && ./validator < $@
inputs/10.txt: generators/gen
	generators/gen 1000000 999997 > $@ && ./validator < $@

$(error)

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator solution tle $(GENERATORS) $(INPUTS) $(OUTPUTS)
