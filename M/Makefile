.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/sgen
GENERATORS += generators/ctz

INPUTS += $(shell seq -f 'inputs/%02g.txt' 3 11)

OUTPUTS += outputs/01-sample.txt
OUTPUTS += outputs/02-sample.txt
OUTPUTS += $(shell seq -f 'outputs/%02g.txt' 3 11)

all: validator solution $(INPUTS) $(OUTPUTS)

validator: validator.cpp

solution: CXXFLAGS += -O2
solution: solution.cpp

$(GENERATORS): %: %.cpp

$(INPUTS): validator

inputs/03.txt: generators/sgen validator
	generators/sgen 1000000 999999 a 1 > $@
	./validator < $@
inputs/04.txt: generators/sgen validator
	generators/sgen 999999 999996 bcb 1 > $@
	./validator < $@
inputs/05.txt: generators/sgen validator
	generators/sgen 999999 999996 deed 1 > $@
	./validator < $@
inputs/06.txt: generators/sgen validator
	generators/sgen 1000000 999999 f 1 g 1 > $@
	./validator < $@
inputs/07.txt: generators/sgen validator
	generators/sgen 1000000 999999 h 100 i 1 > $@
	./validator < $@
inputs/08.txt: generators/sgen validator
	generators/sgen 1000000 999999 j 10000 k 1 > $@
	./validator < $@
inputs/09.txt: generators/sgen validator
	generators/sgen 1000000 999999 \
		a 1 b 1 c 1 d 1 e 1 f 1 g 1 h 1 \
                i 1 j 1 k 1 l 1 m 1 n 1 o 1 p 1 \
                q 1 r 1 s 1 t 1 u 1 v 1 w 1 x 1 \
                y 1 z 1 > $@
	./validator < $@
inputs/10.txt: generators/sgen validator
	generators/sgen 1000000 999999 \
		a 1 b 1 c 1 d 1 e 1 f 1 g 1 h 1 \
                i 1 j 1 k 1 l 1 m 1 n 1 o 1 p 1 \
                q 1 r 1 s 1 t 1 u 1 v 1 w 1 x 1 \
                y 10000 z 1 > $@
	./validator < $@
inputs/11.txt: generators/ctz validator
	generators/ctz 1000000 999999 1 1 > $@
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator solution $(GENERATORS) $(INPUTS) $(OUTPUTS)
