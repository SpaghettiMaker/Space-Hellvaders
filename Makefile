all:
	g++ -o space_invaders ./src/*.cpp -std=c++17 -I/opt/homebrew/Cellar/raylib/5.5/include -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib
	
run: 
	./space_invaders