CC=g++
EXE=-o tut
INCLUDE=-Iinclude
LIBS=-Llib -ltcod -ltcodxx
OPTS=-Wall

all: $(CC) $(EXE) $(INCLUDE) $(LIBS) $(OPTS)
