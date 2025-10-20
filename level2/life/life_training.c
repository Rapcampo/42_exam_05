#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct vec{
	int x;
	int y;
	int pen;
};

void	life(int w, int h, int iter);

int main(int ac, char **av){
	if (ac != 4)
		return 1;
	life(atoi(av[1]), atoi(av[2]), atoi(av[3]));
	return 0;
}

void	life(int w, int h, int iter){
	int board[h][w];
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			board[y][x] = 0;
	struct vec b = {0};
	char c;
	while (read(0, &c, 1)){
		if (c == 'w' && b.y > 0)
			b.y--;
		else if (c == 's' && b.y < h - 1)
			b.y++;
		else if (c == 'a' && b.x > 0)
			b.x--;
		else if (c == 'd' && b.x < w - 1)
			b.x++;
		else if (c == 'x' && b.pen)
			b.pen = 0;
		else if (c == 'x' && !b.pen)
			b.pen = 1;
		if (b.pen)
			board[b.y][b.x] = 1;
	}
	int n = 0;
	int n_board[h][w];
	struct vec v = {0};
	for (int i = 0; i < iter; i++){
		for (int y = 0; y < h; y++){
			for (int x = 0; x < w; x++){
				n = 0;
				for (v.y = -1; v.y <= 1; v.y++){
					for (v.x = -1; v.x <= 1; v.x++)
						if ((v.y || v.x)
								&& x + v.x >= 0
								&& y + v.y >= 0
								&& x + v.x < w
								&& y + v.y < h)
							n += board[y + v.y][x + v.x];
				}
				if (board[y][x] && (n == 2 || n == 3))
					n_board[y][x] = 1;
				else if (!board[y][x] && (n == 3))
					n_board[y][x] = 1;
				else
					n_board[y][x] = 0;
			}
		}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				board[i][j] = n_board[i][j];
	}
	for (int y = 0; y < h; y++){
		for (int x = 0; x < w; x++)
			putchar(board[y][x] ? '0' : ' ');
		putchar('\n');
	}
}
