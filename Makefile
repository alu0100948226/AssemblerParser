CFLAGS = -std=c++11
CLINKER_FLAGS =

TARGET = sim
SRC = lib/sources
OBJ = lib/obj
BIN = bin


OBJECTS = $(patsubst %,$(OBJ)/%,$(notdir $(SOURCE:.cpp=.o)))
SOURCE = $(wildcard $(SRC)/*.cpp)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(CLINKER_FLAGS) -o $@ $^

help :
	@echo "src = $(SOURCE)"
	@echo "obj = $(OBJECTS)"

clean :
	rm -rf $(OBJ)/*.o $(BIN)/*.exe
clean_bin:
	rm -rf $(BIN)/*.exe
clean_obj:
	rm -rf $(OBJ)/*.o
