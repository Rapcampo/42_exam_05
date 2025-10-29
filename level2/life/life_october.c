#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct vec{
	int x;
	int y;
	int pen;
};

void life(int x, int y, int iter);

int main(int ac, char **av){
	if (ac != 4)
		return 1;
	life(atoi(av[1]), atoi(av[2]), atoi(av[3]));
	return 0;
}

void life(int w, int h, int iter){
	struct vec v = {0};
	int board[h][w];
	int cp[h][w];
	char c = 0;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			board[y][x] = 0, cp[y][x] = 0;
	while (read(0, &c, 1)){
		if (c == 'w' && v.y > 0)
			v.y--;
		else if (c == 's' && v.y < h)
			v.y++;
		else if (c == 'a' && v.x > 0)
			v.x--;
		else if (c == 'd' && v.x < w)
			v.x++;
		else if (c == 'x' && v.pen == 1)
			v.pen--;
		else if (c == 'x' && !v.pen)
			v.pen++;
		if (v.pen)
			board[v.y][v.x] = 1;
	}
	int n = 0;
	while (iter--){
		for (int y = 0; y < h; y++){
			for (int x = 0; x < w; x++){
				n = 0;
				for (int yy = -1; yy <= 1; yy++){
					for (int xx = -1; xx <= 1; xx++){
						if ((xx || yy) 
							&& yy + y < h
							&& yy + y >= 0
							&& xx + x < w
							&& xx + x >= 0)
							n += board[yy + y][xx + x];
					}
				}
				if (board[y][x] == 1 && (n == 2 || n == 3))
					cp[y][x] = 1;
				else if (!board[y][x] && n == 3)
					cp[y][x] = 1;
				else
					cp[y][x] = 0;
			}
		}
		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++)
				board[y][x] = cp[y][x];
	}
	for (int y = 0; y < h; y++){
		for (int x = 0; x < w; x++)
			board[y][x] ? putchar('0') : putchar(' ');
		putchar('\n');
	}
}
