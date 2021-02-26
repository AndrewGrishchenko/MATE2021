CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lpigpio
SOURCES=BrushlessMotor.cpp LevelMotor.cpp main.cpp Motor.cpp RotaryCamera.cpp Rov.cpp ThrustersSubsystem.cpp Timer.cpp UDPConnection.cpp additionalfunctions.cpp Manipulator.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rov

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clear:
	rm ${OBJECTS} ${EXECUTABLE}
run: $(EXECUTABLE)
	./rov

