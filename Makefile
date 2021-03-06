
#Compiler
CC=g++

INCLUDES=-I../gameenginetools/ -I/usr/include/libxml2/
CFLAGS=-c -g -Wall -std=c++11 $(INCLUDES) -MMD -MP -MF 
LFLAGS=-Wall -g -lSDL2 -lSDL2_image -lSDL2_ttf -lxml2 -lglog

TOOLSOURCES=../gameenginetools/Time/Timer.cpp \
			../gameenginetools/Time/CarryTimer.cpp

SOURCES=main.cpp \
		Game.cpp \
		Graphics/Drawer.cpp \
		Controls.cpp \
		GameTime.cpp \
		GameEngine/Tile.cpp \
		GameEngine/Map.cpp \
		GameEngine/World.cpp \
		GameEngine/Entities/Entity.cpp \
		GameEngine/Entities/PlayerEntity.cpp \
		GameEngine/GameEngine.cpp \
		$(TOOLSOURCES)

OBJECTS=$(SOURCES:.cpp=.o)

all: game

game: $(OBJECTS)
	$(CC) -o Debug/game $(OBJECTS) $(LFLAGS)

$(OBJECTS): %.o: %.cpp
	$(CC) $(CFLAGS) $@.d -o $@ $<

clean:
	rm -f Debug/game
	rm -f *.o *.o.d
	rm -f */*.o */*.o.d
	rm -f */*/*.o */*/*.o.d
