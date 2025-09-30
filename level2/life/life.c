#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	game_of_life(int x, int y, int iter){
	int board[y][x];
	for(int i = 0; i < y; i++)
		for(int j = 0; j < x; j++)
			board[i][j] = 0;
	int by = 0, bx = 0, pen = 0;
	char c;
	while (read(0, &c, 1)){
		if (c == 'w' && by > 0)
			by--;
		else if (c == 's' && by < y - 1)
			by++;
		else if (c == 'a' && bx > 0)
			bx--;
		else if (c == 'd' && bx < x - 1)
			bx++;
		else if (c == 'x' && pen)
			pen = 0;
		else if (c == 'x' && !pen)
			pen = 1;
		if (pen)
			board[by][bx] = 1;
	}
	int n = 0;
	int newb[y][x];
	for(int it = 0; it < iter; it++){
		for (int yb = 0; yb < y; yb++){
			for(int xb = 0; xb < x; xb++){
				n = 0;
				for(int yy = -1; yy <= 1; yy++){
					for(int xx = -1; xx <= 1; xx++){
						if ((xx || yy) && xb + xx >= 0 
								&& yb + yy >= 0
								&& xb + xx < x
								&& yb + yy < y)
							n += board[yb + yy][xb + xx];
					}
				}
				if (board[yb][xb] && (n == 2 || n == 3))
					newb[yb][xb] = 1;
				else if (!(board[yb][xb]) && n == 3)
					newb[yb][xb] = 1;
				else
					newb[yb][xb] = 0;
			}
		}
		for(int i = 0; i < y; i++)
			for(int j = 0; j < x; j++)
				board[i][j] = newb[i][j];
	}
	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++){
			putchar(board[i][j] ? '0' : ' ');
		}
		putchar('\n');
	}
}

int main(int argc, char **argv){
	if (argc != 4)
		return 1;
	game_of_life(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
}
