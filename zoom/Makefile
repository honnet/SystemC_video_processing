SYSTEMC		= /comelec/softs/opt/systemc-2.2.0
TARGET_ARCH	= linux64

CXX         = g++
LD	    = g++
CXXFLAGS    = -Wall  -I. -I$(SYSTEMC)/include  -Wno-deprecated -O2 -g
LDFLAGS	    =  -L$(SYSTEMC)/lib-$(TARGET_ARCH) 

SOURCES_CPP = $(wildcard *.cpp)
SOURCES_C   = $(wildcard *.c)
OBJS        = $(SOURCES_CPP:.cpp=.o)
OBJS       += $(SOURCES_C:.c=.o)
EXE	    = simulation.x

all: $(EXE) 

$(EXE) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@  -lsystemc -lpng 2>&1 | c++filt

.cpp.o: .deps
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.c.o: .deps
	$(CC) $(CFLAGS) -c -o $@ $<

.deps : $(SOURCES_CPP) $(SOURCES_C)
	$(CXX) $(CXXFLAGS) -MM $(SOURCES_CPP) $(SOURCES_C) > $@

-include .deps

clean :
	-rm -f *.o *~ *_old $(EXE)
	-rm -f simulation.x 
	-rm -f core
	-rm -f *.vcd
	-rm -f .deps

