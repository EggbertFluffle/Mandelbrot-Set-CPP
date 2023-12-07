main: main.cpp ./source/GameManager.cpp ./source/Imaginary.cpp
	g++ -o ./bin/main -w main.cpp ./source/GameManager.cpp ./source/Imaginary.cpp -lSDL2
