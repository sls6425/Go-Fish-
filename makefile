final: go_fish.o player.o deck.o card.o
	g++ -o final go_fish.o player.o deck.o card.o
driver: go_fish.cpp player.h deck.h card.h
	g++ -std=c++11 -c go_fish.cpp
player: player.cpp player.h card.h
	g++ -std=c++11 -c player.cpp
deck.o: deck.cpp deck.h card.h
	g++ -std=c++11 -c deck.cpp
card.o: card.cpp card.h
	g++ -std=c++11 -c card.cpp
