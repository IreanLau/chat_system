ROOT_PATH=$(shell pwd)

SERVER_BIN=chat_server
CLIENT_BIN=chat_client

CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
CONF=$(ROOT_PATH)conf
DATA_POOL=$(ROOT_PATH)/data_pool
LIB=$(ROOT_PATH)/lib
LOG=$(ROOT_PATH)/log
PLUGIN=$(ROOT_PATH)/plugin
SERVER=$(ROOT_PATH)/server
WINDOW=$(ROOT_PATH)/window



CC=g++
INCLUDE= -I$(SERVER) -I$(CLIENT) -I$(COMM) -I$(DATA_POOL) -I$(LIB)/include 
LIB_A_SO=-L $(LIB)/libs  
FLAGS=  -g -Wall -D__DEBUG__ -D_STLE_
LDFLAGS=-ljson_linux-gcc-4.4.7_libmt -lpthread  
SRC=$(shell ls -R | egrep '.cpp' | egrep -v 'libjson_linux-gcc-4.4.7_libmt.a')
OBJ=$(SRC:.cpp=.o)

SER_OBJ=$(shell echo $(OBJ) | sed -E 's/chat_client.o|udp_client.o|window.o//g')
CLI_OBJ=$(shell echo $(OBJ) | sed -E 's/chat_server.o|udp_server.o|data_pool.o//g')

.PHONY:all
all: $(SERVER_BIN) $(CLIENT_BIN) 

$(SERVER_BIN):$(SER_OBJ)
	@echo "Linking [$^] to [$@]"
	@$(CC) -o $@ $^ $(INCLUDE) $(LIB_A_SO) $(FLAGS) $(LDFLAGS)
	@echo "done.."
$(CLIENT_BIN):$(CLI_OBJ)
	@echo "Linking [$^] to [$@]"
	@$(CC) -o $@ $^  $(FLAGS) $(LDFLAGS) 
	@echo "done.."

%.o:$(COMM)/%.cpp
	@echo "Compiling [$^] to [$@]"
	@$(CC) -c $< $(INCLUDE) $(LIB_A_SO) $(LDFLAGS) -g 
	@echo "done.."
%.o:$(CLIENT)/%.cpp
	@echo "Compiling [$^] to [$@]"
	@$(CC) -c $<  $(INCLUDE) $(LIB_A_SO) $(LDFLAGS) -g
	@echo "done.."
%.o:$(SERVER)/%.cpp
	@echo "Compiling [$^] to [$@]"
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "done.."
%.o:$(WINDOW)/%.cpp
	@echo "Compiling [$^] to [$@]"
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "done.."
%.o:$(DATA_POOL)/%.cpp
	@echo "Compiling [$^] to [$@]"
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "done.."


.PHONY:debug
debug:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(SER_OBJ)
	@echo $(CLI_OBJ)

.PHONY:clean
clean:
	rm -rf *.o output
	rm -rf $(SERVER_BIN) $(CLIENT_BIN)

.PHONY:output
output:
	mkdir output
	cp $(SERVER_BIN) output
	cp $(CLIENT_BIN) output
	cp $(PLUGIN)/start.sh output
