
export SYSTEMC		= /comelec/softs/opt/systemc-2.2.0
TARGET_ARCH	= linux64

CXX         = g++
LD	    = g++
CXXFLAGS    = -Wall  -I. -I$(SYSTEMC)/include  -Wno-deprecated -O2
LDFLAGS	    =  -L$(SYSTEMC)/lib-$(TARGET_ARCH) 

SOURCES     = $(wildcard *.cpp)
OBJS        = $(SOURCES:.cpp=.o)
EXE	    = simulation.x

all: $(EXE) 

$(EXE) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@  -lsystemc  2>&1 | c++filt

.cpp.o: .deps
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.deps : $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM $(SOURCES) > $@

-include .deps

clean :
	-rm -f *.o *~ *_old $(EXE)
	-rm -f simulation.x 
	-rm -f core
	-rm -f *.vcd
	-rm -f .deps

