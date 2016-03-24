BIN=my_json
SRC=my_json.cpp
INCLUDE=-I /usr/include
LINK=-L /usr/lib -ljson
CC=g++

$(BIN):$(SRC)
	$(CC) -o $@ $^  $(INCLUDE) $(LINK) -g -lpthread 
.PHONY:clean
clean:
	rm -rf $(BIN)
