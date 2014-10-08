CC = gcc
LINK = g++
OPTIMIZATION = O3
CFLAGS = -Wall -std=c++11 -$(OPTIMIZATION)
DEST_DIR = ../release

TARGET = huffmanCpp
FULL_TARGET = $(DEST_DIR)/$(TARGET)$(OPTIMIZATION)

MAIN_O = $(DEST_DIR)/Main$(OPTIMIZATION).o
DECODER_O = $(DEST_DIR)/Decoder$(OPTIMIZATION).o
ENCODER_O = $(DEST_DIR)/Encoder$(OPTIMIZATION).o
CODIFICATION_O = $(DEST_DIR)/Codification$(OPTIMIZATION).o
CODIFICATIONARRAYELEMENT_O = $(DEST_DIR)/CodificationArrayElement$(OPTIMIZATION).o
FILE_O = $(DEST_DIR)/File$(OPTIMIZATION).o
NODE_O = $(DEST_DIR)/Node$(OPTIMIZATION).o
NODEARRAY_O = $(DEST_DIR)/NodeArray$(OPTIMIZATION).o

OBJECTS = $(MAIN_O) \
	  $(DECODER_O) \
	  $(ENCODER_O) \
	  $(CODIFICATION_O) \
	  $(CODIFICATIONARRAYELEMENT_O) \
	  $(FILE_O) \
	  $(NODE_O) \
	  $(NODEARRAY_O)

all: $(TARGET)

$(TARGET): $(FULL_TARGET)

$(FULL_TARGET): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $@

$(MAIN_O): Main.cpp Decoder.cpp Encoder.cpp Codification.cpp CodificationArrayElement.cpp File.cpp Node.cpp NodeArray.cpp \
				Decoder.h Encoder.h Codification.h CodificationArrayElement.h File.h Node.h NodeArray.h
	$(CC) -c $(CFLAGS) Main.cpp -o $@

$(DECODER_O): Decoder.cpp Decoder.h	Defines.h \
		$(CODIFICATION_O) $(CODIFICATIONARRAYELEMENT_O) $(FILE_O)
	$(CC) -c $(CFLAGS) Decoder.cpp -o $@

$(ENCODER_O): Encoder.cpp Encoder.h	Defines.h \
		$(CODIFICATION_O) $(FILE_O) $(NODE_O) $(NODEARRAY_O)
	$(CC) -c $(CFLAGS) Encoder.cpp -o $@

$(CODIFICATION_O): Codification.cpp Codification.h	Defines.h
	$(CC) -c $(CFLAGS) Codification.cpp -o $@

$(CODIFICATIONARRAYELEMENT_O): CodificationArrayElement.cpp CodificationArrayElement.h	Defines.h
	$(CC) -c $(CFLAGS) CodificationArrayElement.cpp -o $@

$(FILE_O): File.cpp File.h	Defines.h
	$(CC) -c $(CFLAGS) File.cpp -o $@

$(NODE_O): Node.cpp Node.h	Defines.h
	$(CC) -c $(CFLAGS) Node.cpp -o $@

$(NODEARRAY_O): NodeArray.cpp NodeArray.h	Defines.h
	$(CC) -c $(CFLAGS) NodeArray.cpp -o $@

clean:
	- rm $(OBJECTS)

clean_all: clean
	- rm $(FULL_TARGET)
