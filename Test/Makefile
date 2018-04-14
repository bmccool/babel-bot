CC = g++
CFLAGS = -std=c++11 -c -g -Wall
LDFLAGS = -lm
SOURCES = ./../Button.cpp Button.test.cpp ./../Controller.cpp Controller.test.cpp ./../FM2.cpp FM2.test.cpp ./../GPIO.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = UnitTest

all: $(SOURCES) $(EXECUTABLE) run
	

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(EXECUTABLE) *.o *~

.PHONY : run
run: $(EXECUTABLE)
	./$(EXECUTABLE) 
