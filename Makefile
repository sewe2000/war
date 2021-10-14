CXXFLAGS = -std=c++20 -g
war: obj/main.o obj/deck.o
	g++ obj/* -o war
obj/main.o: src/main.cpp
	g++ src/main.cpp ${CXXFLAGS} -c -o obj/main.o
obj/deck.o: src/deck.cpp include/deck.hpp include/card.hpp
	g++ src/deck.cpp ${CXXFLAGS} -c -o obj/deck.o
clean:
	rm -f war
	rm -f obj/*
