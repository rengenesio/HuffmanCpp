CC = gcc
LINK = g++
OPTIMIZATION = -O3
CFLAGS = -Wall -std=c++11 $(OPTIMIZATION)
RM = rm -rf

PATH_SRC = src
PATH_OBJ = src
TARGET = release/huffmanCpp$(OPTIMIZATION)

OBJ =   $(PATH_OBJ)/Main$(OPTIMIZATION).o \
	$(PATH_OBJ)/Decoder$(OPTIMIZATION).o \
	$(PATH_OBJ)/Encoder$(OPTIMIZATION).o \
	$(PATH_OBJ)/Codification$(OPTIMIZATION).o \
	$(PATH_OBJ)/CodificationArrayElement$(OPTIMIZATION).o \
	$(PATH_OBJ)/File$(OPTIMIZATION).o \
	$(PATH_OBJ)/Node$(OPTIMIZATION).o \
	$(PATH_OBJ)/NodeArray$(OPTIMIZATION).o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LINK) $(OBJ) -o $@

$(PATH_OBJ)/Main$(OPTIMIZATION).o : $(PATH_SRC)/Main.cpp $(PATH_SRC)/Decoder.cpp $(PATH_SRC)/Encoder.cpp \
		     $(PATH_SRC)/Decoder.h $(PATH_SRC)/Encoder.h
	$(CC) -c $(CFLAGS) $(PATH_SRC)/Main.cpp -o $@

$(PATH_OBJ)/Decoder$(OPTIMIZATION).o: $(PATH_SRC)/Decoder.cpp $(PATH_SRC)/Decoder.h $(PATH_SRC)/Defines.h \
		$(PATH_OBJ)/Codification$(OPTIMIZATION).o $(PATH_OBJ)/CodificationArrayElement$(OPTIMIZATION).o $(PATH_OBJ)/File$(OPTIMIZATION).o
	$(CC) -c $(CFLAGS) $(PATH_SRC)/Decoder.cpp -o $@

$(PATH_OBJ)/Encoder$(OPTIMIZATION).o: $(PATH_SRC)/Encoder.cpp $(PATH_SRC)/Encoder.h $(PATH_SRC)/Defines.h \
		$(PATH_OBJ)/Codification$(OPTIMIZATION).o $(PATH_OBJ)/File$(OPTIMIZATION).o $(PATH_OBJ)/Node$(OPTIMIZATION).o $(PATH_OBJ)/NodeArray$(OPTIMIZATION).o
	$(CC) -c $(CFLAGS) $(PATH_SRC)/Encoder.cpp -o $@

$(PATH_OBJ)/Codification$(OPTIMIZATION).o: $(PATH_SRC)/Codification.cpp $(PATH_SRC)/Codification.h $(PATH_SRC)/Defines.h
	$(CC) -c $(CFLAGS) $(PATH_SRC)/Codification.cpp -o $@

$(PATH_OBJ)/CodificationArrayElement$(OPTIMIZATION).o: $(PATH_SRC)/CodificationArrayElement.cpp $(PATH_SRC)/CodificationArrayElement.h $(PATH_SRC)/Defines.h
	$(CC) -c $(CFLAGS) $(PATH_SRC)/CodificationArrayElement.cpp -o $@

$(PATH_OBJ)/File$(OPTIMIZATION).o: $(PATH_SRC)/File.cpp $(PATH_SRC)/File.h $(PATH_SRC)/Defines.h
	$(CC) -c $(CFLAGS) $(PATH_SRC)/File.cpp -o $@

$(PATH_OBJ)/Node$(OPTIMIZATION).o: $(PATH_SRC)/Node.cpp $(PATH_SRC)/Node.h $(PATH_SRC)/Defines.h
	$(CC) -c $(CFLAGS) $(PATH_SRC)/Node.cpp -o $@

$(PATH_OBJ)/NodeArray$(OPTIMIZATION).o: $(PATH_SRC)/NodeArray.cpp $(PATH_SRC)/NodeArray.h $(PATH_SRC)/Defines.h
	$(CC) -c $(CFLAGS) $(PATH_SRC)/NodeArray.cpp -o $@

clean:
	$(RM) $(OBJ)

clean_all: clean
	$(RM) $(TARGET)

