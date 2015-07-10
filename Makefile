include Makefile.defs
OBJS=KRMBParam.o KRMB.o PermutationArray.o PermutationStatus.o Permutation.o

all: krmbsorter.exe krmbdiam.exe

%.exe: $(OBJS) %.o
	$(CXX) $^ -o $@

%.o: %.cpp %.h
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o gmon.out krmbsorter.exe krmbdiam.exe


