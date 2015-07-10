include ../Makefile.defs
BINARIES=testbi testrmb testperm testpsa

all: $(BINARIES)

testbi: testbi.cpp
	$(CXX) $< -o $@

testperm: testperm.cpp ../PermutationArray.o ../Permutation.o
	$(CXX) $^ -o $@

testrmb: testrmb.cpp ../BigInteger.o ../KRMB.o
	$(CXX) $^ -o $@

testpsa: testpsa.cpp ../PermutationStatus.o
	$(CXX) $^ -o $@

clean:
	rm -f gmon.out $(BINARIES)
	make -C .. clean
