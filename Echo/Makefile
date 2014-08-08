.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=libecho.a
INCLUDE=echo
OBJS=Socket.o Rio.o TcpConnection.o PollPoller.o InetAddress.o TcpServer.o Thread.o Condition.o ThreadPool.o Exception.o Timer.o TimerThread.o
STARD=-std=c++0x -rdynamic
$(BIN):$(OBJS)
	ar -crv $@ -o $^
	chmod 0777 $@
	rm -f *.o
	rm -rf $(INCLUDE)
	mkdir $(INCLUDE)
	cp *.h $(INCLUDE)/
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD)
install:
	sudo cp $(BIN) /usr/lib/
	sudo cp $(INCLUDE) /usr/include/ -r
clean:
	rm -rf *.o $(BIN) echo