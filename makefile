OS := $(shell uname -s)

ifeq ($(OS), Linux)
	INCLUDES = -I/usr/include -L/usr/lib -lrt -lGL -lglut -lGLU -lX11 -Ibullet-2.79/src
else
	INCLUDES = -framework Cocoa -framework OpenGL -framework GLUT -Ibullet-2.79/src
endif


all: Timer.o Ball.o Table.o Cup.o main.o 
	@echo 'linking executable'
	@g++ Timer.o Ball.o Table.o Cup.o main.o ./bullet-2.79/src/*.o $(INCLUDES) -o pool.exe
main.o: main.cpp
	@echo 'building main.o'
	@g++ -c main.cpp $(INCLUDES)
Timer.o: Timer.h Timer.cpp
	@echo 'building Timer.o'
	@g++ -c Timer.cpp $(INCLUDES)
Ball.o: Ball.h Ball.cpp
	@echo 'building Ball.o'
	@g++ -c Ball.cpp $(INCLUDES)
Table.o: Table.h Table.cpp
	@echo 'building Table.o'
	@g++ -c Table.cpp $(INCLUDES)
Cup.o: Cup.h Cup.cpp
	@echo 'building Cup.o'
	@g++ -c Cup.cpp $(INCLUDES)
clean:
	@echo 'cleaning up files'
	rm -f *.o
	rm -f pool
