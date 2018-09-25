.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++14 -Wall -O2 -I../include

SAMPLES = 00 01
TESTDATA = 02 03 04 05 06 07 08 09 10 11 12 13 14 15
TESTSUB = ac-1

INPUTS = $(TESTDATA:%=inputs/%.txt)
OUTPUTS = $(SAMPLES:%=outputs/%-sample.txt) $(TESTDATA:%=outputs/%.txt)
EXTRAS = $(TESTSUB:%=extras/%)

all: $(EXTRAS) validator solution $(OUTPUTS)

validator generator solution $(EXTRAS): %: %.cpp

$(INPUTS): validator generator
inputs/02.txt:
	./generator 0 1 > $@
	./validator < $@
inputs/03.txt:
	./generator 0 1000000 > $@
	./validator < $@
inputs/04.txt:
	./generator 99999 2 > $@
	./validator < $@
inputs/05.txt:
	./generator 99999 1 > $@
	./validator < $@
inputs/06.txt:
	./generator 1000000 1  > $@
	./validator < $@
inputs/07.txt:
	./generator 100 2 > $@
	./validator < $@
inputs/08.txt:
	./generator 99999 123 > $@
	./validator < $@
inputs/09.txt:
	./generator 98763 323 > $@
	./validator < $@
inputs/10.txt:
	./generator 82827 7 > $@
	./validator < $@
inputs/11.txt:
	./generator 8831 8829 > $@
	./validator < $@
inputs/12.txt:
	./generator 77777 77 > $@
	./validator < $@
inputs/13.txt:
	./generator 9487 87 > $@
	./validator < $@
inputs/14.txt:
	./generator 0 1000 > $@
	./validator < $@
inputs/15.txt:
	./generator 1000000 1000000 > $@
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator generator solution $(INPUTS) $(OUTPUTS) $(EXTRAS)

