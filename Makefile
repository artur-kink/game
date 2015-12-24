
#Compiler
CC=g++

INCLUDES=-I../gameenginetools/
CFLAGS=-c -g -Wall -std=c++11 $(INCLUDES) -MMD -MP -MF 
LFLAGS=-Wall -g -lSDL2 -lSDL2_image -lSDL2_ttf

TOOLSOURCES=../gameenginetools/Time/Timer.cpp \
			../gameenginetools/Time/CarryTimer.cpp

SOURCES=main.cpp \
		Game.cpp \
		Drawer.cpp \
		GameTime.cpp \
		Map.cpp \
		World.cpp \
		$(TOOLSOURCES)

OBJECTS=$(SOURCES:.cpp=.o)

all: game

game: $(OBJECTS)
	$(CC) -o Debug/game $(OBJECTS) $(LFLAGS)

$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) $@.d -o $@ $<

clean:
	rm -f Debug/game
	rm *.o *.o.d
