.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++14 -Wall -O2 -I../include

SAMPLES = 00 01
TESTDATA = 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16
TESTSUB = wa-1 wa-2 ac-1

INPUTS = $(TESTDATA:%=inputs/%.txt)
OUTPUTS = $(SAMPLES:%=outputs/%-sample.txt) $(TESTDATA:%=outputs/%.txt)
EXTRAS = $(TESTSUB:%=extras/%)

all: $(EXTRAS) validator solution $(OUTPUTS)

validator generator solution $(EXTRAS): %: %.cpp

$(INPUTS): validator generator
inputs/02.txt:
	./generator 1 0 0 0 > $@
	./validator < $@
inputs/03.txt:
	./generator 1 1 0 0 > $@
	./validator < $@
inputs/04.txt:
	./generator 1 0 1 0 > $@
	./validator < $@
inputs/05.txt:
	./generator 2 0 0 0 > $@
	./validator < $@
inputs/06.txt:
	./generator 2 1 0 0  > $@
	./validator < $@
inputs/07.txt:
	./generator 2 0 1 0 > $@
	./validator < $@
inputs/08.txt:
	./generator 2 1 1 0 > $@
	./validator < $@
inputs/09.txt:
	./generator 5000 1000 1000 0 > $@
	./validator < $@
inputs/10.txt:
	./generator 5000 2500 2499 0 > $@
	./validator < $@
inputs/11.txt:
	./generator 5000 987 4000 0 > $@
	./validator < $@
inputs/12.txt:
	./generator 5000 1234 1234 0 > $@
	./validator < $@
inputs/13.txt:
	./generator 5000 3129 1487 0 > $@
	./validator < $@
inputs/14.txt:
	./generator 5000 1024 768 0 > $@
	./validator < $@
inputs/15.txt:
	./generator 833 -1 -1 1 > $@
	./validator < $@
inputs/16.txt:
	./generator 1639 -1 -1 2 > $@
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator generator solution $(INPUTS) $(OUTPUTS) $(EXTRAS)

