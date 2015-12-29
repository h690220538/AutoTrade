CC = g++
TARGET = AutoTrade.exe
SOURCES = $(wildcard ./AutoTrade/*.cpp)
HEADERS = $(wildcard ./AutoTrade/*.h)
OBJECTS = $(SOURCES:%.h=%.o)


all:$(TARGET)
	@echo $(SOURCES)
	
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJECTS): $(SOURCES)
	$(CC) -c $^
