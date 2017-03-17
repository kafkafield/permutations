all: huang wang

CXX=g++
CXXFLAG=-O3
HEADERS=timer.hpp

huang: main_huang.cpp $(HEADERS)
	$(CXX) $(CXXFLAG) -o $@ $<

wang: main_wang.cpp $(HEADERS)
	$(CXX) $(CXXFLAG) -o $@ $<

clean:
	rm huang wang
