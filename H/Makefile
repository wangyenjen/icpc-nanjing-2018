.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/swgen

EXTRAS += extras/wa-1
EXTRAS += extras/tle-1
EXTRAS += extras/tle-2
EXTRAS += extras/tle-3

INPUTS += inputs/03.txt
INPUTS += inputs/04.txt
INPUTS += inputs/05.txt
INPUTS += inputs/06.txt
INPUTS += inputs/07.txt

OUTPUTS += outputs/01-sample.txt
OUTPUTS += outputs/02-sample.txt
OUTPUTS += outputs/03.txt
OUTPUTS += outputs/04.txt
OUTPUTS += outputs/05.txt
OUTPUTS += outputs/06.txt
OUTPUTS += outputs/07.txt

all: validator solution $(INPUTS) $(OUTPUTS) $(EXTRAS)

solution: CXXFLAGS += -O2
validator solution $(GENERATORS) $(EXTRAS): %: %.cpp

$(INPUTS): validator
inputs/03.txt:
	python3 -c "print(100000, '2' * 100000, sep='\n')" > $@
	./validator < $@
inputs/04.txt:
	python3 -c "print(99996, '110202' * 16666, sep='\n')" > $@
	./validator < $@
inputs/05.txt: generators/swgen
	generators/swgen "[012]{100000}" > $@
	./validator < $@
inputs/06.txt: generators/swgen
	generators/swgen "[01222]{100000}" > $@
	./validator < $@
inputs/07.txt: generators/swgen
	generators/swgen "1{50000}0{25000}2{25000}" > $@
	./validator < $@

$(OUTPUTS): outputs/%: inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator solution $(GENERATORS) $(EXTRAS) $(INPUTS) $(OUTPUTS)
