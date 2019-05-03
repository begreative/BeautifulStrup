CC  = g++
CXX = g++

INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++17

LDFLAGS = -g
LDLIBS  = -lboost_filesystem

executables = test_soup
# objects = test_soup.o

.PHONY: default
default: $(executables)

test_soup: BeautifulStrup.cpp

.PHONY: clean
clean:
	rm -f *~ a.out core $(objects) $(executables)

.PHONY: all
all: clean default