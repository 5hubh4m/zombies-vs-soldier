CC = gcc
CXX = g++
CXXFLAGS = -std=c++11 -Wall
INCLUDES =
LFLAGS =
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
SRCS = main.cpp SDL_Class.cpp soldier.cpp zombie.cpp bullet.cpp menu.cpp game.cpp scores.cpp zombies_vs_soldier.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = zombies_vs_soldier

.PHONY : depend clean

all : $(MAIN)
	@echo zombies_vs_soldier compiled and linked

$(MAIN) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

clean :
	$(RM) *.o *~ $(MAIN) *db

run :
	./$(MAIN)

depend : $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
