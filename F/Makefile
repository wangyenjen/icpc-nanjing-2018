.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++14 -Wall -O2

SAMPLES = 00
TESTDATA = 01 02 03 04 05 06 07 08 09 10 11 12
TESTSUB = wa-1 tle-1 ac-1

INPUTS = $(TESTDATA:%=inputs/%.txt)
OUTPUTS = $(SAMPLES:%=outputs/%-sample.txt) $(TESTDATA:%=outputs/%.txt)
EXTRAS = $(TESTSUB:%=extras/%)

all: validator checker solution $(OUTPUTS) $(EXTRAS)

solution: CXXFLAGS += -DN3

validator generator checker solution $(EXTRAS): %: %.cpp

$(INPUTS): validator generator
inputs/01.txt:
	./generator 30 10 6 20 random 70 27 > $@
	./validator < $@
inputs/02.txt:
	./generator 50 10 2 50 > $@
	./validator < $@
inputs/03.txt:
	./generator 50 30 2 50 tree 20 loop 15 > $@
	./validator < $@
inputs/04.txt:
	./generator 60 60 2 50 rtree 40 random 100 40 loop 10 > $@
	./validator < $@
inputs/05.txt:
	./generator 200 200 11 300 > $@
	./validator < $@
inputs/06.txt:
	./generator 400 200 17 400 random 9 30 loop 300 > $@
	./validator < $@
inputs/07.txt:
	./generator 400 60 17 400 tree 400 rtree 350 loop 300 > $@
	./validator < $@
inputs/08.txt:
	./generator 400 400 6 400 random 3 200 > $@
	./validator < $@
inputs/09.txt:
	./generator 400 27 17 400 tree 175 random 8000 360 loop 50 > $@
	./validator < $@
inputs/10.txt:
	./generator 400 400 4 400 random 160000 397 loop 600 > $@
	./validator < $@
inputs/11.txt:
	./generator 400 279 207 400 tree 400 rtree 400 loop 400 > $@
	./validator < $@
inputs/12.txt:
	./generator 400 7 139 400 tree 30 random 15 6 loop 150 > $@
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator generator checker solution $(INPUTS) $(OUTPUTS) $(EXTRAS)
