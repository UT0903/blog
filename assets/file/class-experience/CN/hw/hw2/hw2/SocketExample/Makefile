CC = g++
OPENCV =  `pkg-config --cflags --libs opencv`
PTHREAD = -pthread

CLIENT = bonus_client.cpp
SERVER = multi_server.cpp
CVFILE = openCV.cpp
CLI = client
SER = server
CV = open

all:
	g++ multi_server.cpp -o server `pkg-config --cflags --libs opencv` -pthread
	g++ bonus_client.cpp -o client `pkg-config --cflags --libs opencv` -std=c++11 -pthread
server: $(SERVER)
	$(CC) $(SERVER) -o $(SER)  $(OPENCV) $(PTHREAD) 
client: $(CLIENT)
	$(CC) $(CLIENT) -o $(CLI)  $(OPENCV) $(PTHREAD)
opencv:
	$(CC) $(CVFILE) -o $(CV)  $(OPENCV)
.PHONY: clean

clean:
	rm $(CLI) $(SER) $(CV)