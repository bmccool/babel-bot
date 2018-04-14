CC = g++
CFLAGS = -c -g -Wall -pthread
LDFLAGS = -lm -pthread
SOURCES = main.cpp Controller.cpp CS_time.cpp Button.cpp FM2.cpp GPIO.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = BeaglePlayer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) *.o *~

docs:
	doxygen ./Docs/Doxyfile-build
