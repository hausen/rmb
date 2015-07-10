include ../Makefile.defs
BINARIES=testrmb testrmbparam testperm testpsa

all: $(BINARIES)

testperm: testperm.cpp ../PermutationArray.o ../Permutation.o
	$(CXX) $^ -o $@

testrmb: testrmb.cpp ../KRMBParam.o ../KRMB.o
	$(CXX) $^ -o $@

testrmbparam: testrmbparam.cpp ../KRMBParam.o
	$(CXX) $^ -o $@

testpsa: testpsa.cpp ../PermutationStatus.o
	$(CXX) $^ -o $@

clean:
	rm -f gmon.out $(BINARIES)
	make -C .. clean
