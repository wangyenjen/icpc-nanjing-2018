.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++14 -Wall -O2 -I../include

SAMPLES = 00 01
TESTDATA = 02 03 04 05 06 07 08 09 10
TESTSUB = ac-1

INPUTS = $(TESTDATA:%=inputs/%.txt)
OUTPUTS = $(SAMPLES:%=outputs/%-sample.txt) $(TESTDATA:%=outputs/%.txt)
EXTRAS = $(TESTSUB:%=extras/%)

all: $(EXTRAS) validator checker solution $(OUTPUTS)

validator generator checker solution $(EXTRAS): %: %.cpp

$(INPUTS): validator generator
inputs/02.txt:
	./generator 1 2 > $@
	./validator < $@
inputs/03.txt:
	./generator 100 3 > $@
	./validator < $@
inputs/04.txt:
	./generator 100 4 > $@
	./validator < $@
inputs/05.txt:
	./generator 100 5 > $@
	./validator < $@
inputs/06.txt:
	./generator 100 6  > $@
	./validator < $@
inputs/07.txt:
	./generator 4 7 > $@
	./validator < $@
inputs/08.txt:
	./generator 20 8 > $@
	./validator < $@
inputs/09.txt:
	./generator 87 9 > $@
	./validator < $@
inputs/10.txt:
	./generator 99 10 > $@
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator generator checker solution $(INPUTS) $(OUTPUTS) $(EXTRAS)

