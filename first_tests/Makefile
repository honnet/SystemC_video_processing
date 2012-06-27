export SYSTEMC=/comelec/softs/opt/systemc-2.2.0

CXX=g++
CXXFLAGS = -Wno-deprecated -I $(SYSTEMC)/include
LDFLAGS = -L $(SYSTEMC)/lib-linux64 
LDLIBS = -lsystemc


# permet de compiler en fonction de l'argument :
TARGET = $(CMDGOAL)

$(TARGET).o : $(TARGET).h $(TARGET).cpp



clean :
	-rm -f *.o *~ *.gch
