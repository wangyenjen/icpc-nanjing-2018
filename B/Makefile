.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++14 -Wall -O2 -I../include

SAMPLES = 00 01
TESTDATA = 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20
TESTSUB = tle-1 re-1 wa-1 ac-1

INPUTS = $(TESTDATA:%=inputs/%.txt)
OUTPUTS = $(SAMPLES:%=outputs/%-sample.txt) $(TESTDATA:%=outputs/%.txt)
EXTRAS = $(TESTSUB:%=extras/%)

all: $(EXTRAS) validator solution $(OUTPUTS)

validator generator solution $(EXTRAS): %: %.cpp

$(INPUTS): validator generator
inputs/02.txt:
	./generator 100 0 1 > $@
	./validator < $@
inputs/03.txt:
	./generator 300 1 0 > $@
	./validator < $@
inputs/04.txt:
	./generator 1000 2 0 > $@
	./validator < $@
inputs/05.txt:
	./generator 3000 0 6 > $@
	./validator < $@
inputs/06.txt:
	./generator 10000 2 1  > $@
	./validator < $@
inputs/07.txt:
	./generator 30000 0 5 > $@
	./validator < $@
inputs/08.txt:
	./generator 100000 0 3 > $@
	./validator < $@
inputs/09.txt:
	./generator 300000 0 0 > $@
	./validator < $@
inputs/10.txt:
	./generator 300000 0 1 > $@
	./validator < $@
inputs/11.txt:
	./generator 300000 0 2 > $@
	./validator < $@
inputs/12.txt:
	./generator 300000 0 3 > $@
	./validator < $@
inputs/13.txt:
	./generator 300000 0 4 > $@
	./validator < $@
inputs/14.txt:
	./generator 300000 0 5 > $@
	./validator < $@
inputs/15.txt:
	./generator 300000 0 6 > $@
	./validator < $@
inputs/16.txt:
	./generator 300000 1 0 > $@
	./validator < $@
inputs/17.txt:
	./generator 300000 2 0 > $@
	./validator < $@
inputs/18.txt:
	./generator 300000 2 1 > $@
	./validator < $@
inputs/19.txt:
	./generator 2 1 0 > $@
	./validator < $@
inputs/20.txt:
	./generator 30 0 4 > $@
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator generator solution $(INPUTS) $(OUTPUTS) $(EXTRAS)
