NO_SFML = 0
ifeq ($(NO_SFML), 0)
main: main.cpp
	g++ -o main main.cpp -lsfml-audio
else
main: main.cpp
	g++ -o main main.cpp -DNO_SFML=1
endif
