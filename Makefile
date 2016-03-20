ROOT_PATH=$(shell pwd)

CLIENT_BIN=chat_client
SERVER_BIN=chat_server

CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
CONF=$(ROOT_PATH)/conf
LIB=$(ROOT_PATH)/lib
LOG=$(ROOT_PATH)/log
PLUGIN=$(ROOT_PATH)/plugin
SERVER=$(ROOT_PATH)/server
WINDOW=$(ROOT_PATH)/window
DATA_POOL=$(ROOT_PATH)/data_pool

INCLUDE=-I$(ROOT_PATH)/comm
LIB_A_SO=

CC=g++
FLAGS=$(INCLUDE) -g -Wall -D__DEBUG_
LDFLAGS=


SRC=$(shell ls -R | egrep '.cpp' | sed 's/libjsoncp.a//g')
OBJ=$(SRC:.cpp=.o)

SER_OBJ=$(shell echo $(OBJ) | sed 's/chat_client.o\|udp_client.o\|window.o//g')
CLI_OBJ=$(shell echo $(OBJ) | sed 's/chat_server.o\|udp_server.o//g')


.PHONY:debug
.PHONY:all
all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SER_OBJ)
	@echo "Linking [ $^ ] to [ $@ ] ... done"
	@$(CC) -o $@ $^ $(LDFLAGS)
$(CLIENT_BIN):$(CLI_OBJ)
	@echo "Linking [ $^ ] to [ $@ ] ... done"
	@$(CC) -o $@ $^ $(LDFLAGS)


%.o:$(COMM)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(FLAGS)   

%.o:$(CLIENT)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(FLAGS)             
%.o:$(SERVER)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(FLAGS)   
%.o:$(WINDOW)/%.cpp
	@echo "Compiling [ $< ] to [ $@ ] ... done"
	@$(CC) -c $< $(FLAGS)  

.PHONY:clean
clean:
	rm -rf *.o $(SERVER_BIN) $(CLIENT_BIN)


#COMM=$(ROOT_PATH)/comm
#CONF=$(ROOT_PATH)/conf
#LIB=$(ROOT_PATH)/lib
#LOG=$(ROOT_PATH)/log
#PLUGIN=$(ROOT_PATH)/plugin
#SERVER=$(ROOT_PATH)/server
#WINDOW=$(ROOT_PATH)/window



#debug:
#	@echo $(SRC)
#	@echo $(OBJ)
#	@echo $(SER_OBJ)
#	@echo $(CLI_OBJ)




