#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	game_of_life(int x, int y, int i);

int main(int argc, char **argv){
	if (argc != 4)
		return 1;
	game_of_life(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
}
