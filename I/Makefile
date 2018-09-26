.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/gen
GENERATORS += generators/allrand

INPUTS += inputs/03.txt
INPUTS += inputs/04.txt
INPUTS += inputs/05.txt
INPUTS += inputs/06.txt
INPUTS += inputs/07.txt
INPUTS += inputs/08.txt
INPUTS += inputs/09.txt
INPUTS += inputs/10.txt
INPUTS += inputs/11.txt
INPUTS += inputs/12.txt
INPUTS += inputs/13.txt
INPUTS += inputs/14.txt
INPUTS += inputs/15.txt
INPUTS += inputs/16.txt
INPUTS += inputs/17.txt

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
OUTPUTS += outputs/11.txt
OUTPUTS += outputs/12.txt
OUTPUTS += outputs/13.txt
OUTPUTS += outputs/14.txt
OUTPUTS += outputs/15.txt
OUTPUTS += outputs/16.txt
OUTPUTS += outputs/17.txt

all: validator solution wa1 wa2 wa3 $(INPUTS) $(OUTPUTS)

validator: validator.cpp

solution: CXXFLAGS += -O2
solution: solution.cpp
wa1: wa1.cpp
wa2: wa2.cpp
wa3: wa3.cpp

$(GENERATORS): %: %.cpp

$(INPUTS): validator

inputs/03.txt: generators/gen
	generators/gen 500 500 20 > $@ && ./validator < $@
inputs/04.txt: generators/gen
	generators/gen 400 500 40 > $@ && ./validator < $@
inputs/05.txt: generators/gen
	generators/gen 300 500 60 > $@ && ./validator < $@
inputs/06.txt: generators/gen
	generators/gen 200 500 80 > $@ && ./validator < $@
inputs/07.txt: generators/gen
	generators/gen 100 500 100 > $@ && ./validator < $@

inputs/08.txt: generators/gen
	generators/gen 40 480 4 > $@ && ./validator < $@
inputs/09.txt: generators/gen
	generators/gen 80 480 8 > $@ && ./validator < $@
inputs/10.txt: generators/gen
	generators/gen 120 480 12 > $@ && ./validator < $@
inputs/11.txt: generators/gen
	generators/gen 200 480 16 > $@ && ./validator < $@
inputs/12.txt: generators/gen
	generators/gen 420 480 1 > $@ && ./validator < $@

inputs/13.txt: generators/allrand
	generators/allrand 1 > $@ && ./validator < $@
inputs/14.txt: generators/allrand
	generators/allrand 2 > $@ && ./validator < $@
inputs/15.txt: generators/allrand
	generators/allrand 3 > $@ && ./validator < $@
inputs/16.txt: generators/allrand
	generators/allrand 4 > $@ && ./validator < $@
inputs/17.txt: generators/allrand
	generators/allrand 5 > $@ && ./validator < $@



$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator solution wa1 wa2 wa3 $(GENERATORS) $(INPUTS) $(OUTPUTS)
