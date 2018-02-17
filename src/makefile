CXX = g++
CXXFLAGS = -Wall -g -std=c++11

OBJS = main.o settings.o network.o data_set.o
HEADERS =


ann : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJS) : settings.h

clean :
	@rm -f *o ann
