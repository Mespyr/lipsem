CPP = g++
CPPFLAGS = -c -g
LDFLAGS = -g 
SRC = $(wildcard src/*.cpp)
HDR = $(wildcard include/*.h)
OBJ = $(SRC:.cpp=.o)
EXEC = lipsem

all: $(SRC) $(OBJ) $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(LDFLAGS) $^ -o $@

%.o: %.cpp $(HDR)
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm src/*.o $(EXEC)

clean-obj:
	rm src/*.o

clean-exec:
	rm $(EXEC)
