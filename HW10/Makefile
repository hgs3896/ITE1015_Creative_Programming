CC = g++
CXXFLAGS = -std=c++11
LDFLAGS = -lpthread

OBJ1 = monti01.o
OBJ2 = monti02.o

TARGET1 = monti01
TARGET2 = monti02

all : $(TARGET1) $(TARGET2)

$(TARGET1) : $(OBJ1)
			   $(CC) -o $@ $(OBJ1) $(LDFLAGS)

$(TARGET2) : $(OBJ2)
			   $(CC) -o $@ $(OBJ2) $(LDFLAGS)

clean :
	rm -rf $(OBJ1) $(OBJ2) $(TARGET1) $(TARGET2) core
