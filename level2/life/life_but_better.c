#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct t_point{
	int x;
	int y;
	int pen;
};

void	game_of_life(int size_x, int size_y, int loops){
	int board[size_y][size_x];
	for(int y = 0; y < size_y; y++)
		for(int x = 0; x < size_x; x++)
			board[y][x] = 0;

	struct t_point cur = {0};
	char c;
	//iterates through each echo board movement instruction and marks valid initial alive cells
	while (read(0, &c, 1)){
		if (c == 'w' && cur.y > 0)
			cur.y--;
		else if (c == 's' && cur.y < size_y - 1)
			cur.y++;
		else if (c == 'a' && cur.x > 0)
			cur.x--;
		else if (c == 'd' && cur.x < size_x - 1)
			cur.x++;
		else if (c == 'x' && cur.pen)
			cur.pen = 0;
		else if (c == 'x' && !cur.pen)
			cur.pen = 1;
		if (cur.pen)
			board[cur.y][cur.x] = 1;
	}
	
	int neighbours = 0;
	int new_board[size_y][size_x];
	struct t_point b = {0};
	//calculates next alive or dead cells on a new board before copying and priting.
	while (loops--){
		for (b.y = 0; b.y < size_y; b.y++){
			for (b.x = 0; b.x < size_x; b.x++){
				neighbours = 0;
				//verify 9 surrounding blocks to calculate neighbours;
				for(int ny = -1; ny <= 1; ny++){
					for(int nx = -1; nx <= 1; nx++){
						if ((nx || ny) && b.x + nx >= 0
								&& b.y + ny >= 0
								&& b.x + nx < size_x
								&& b.y + ny < size_y)
							neighbours += board[b.y + ny][b.x + nx];
					}
				}
				if (board[b.y][b.x] && (neighbours == 2 || neighbours == 3))
					new_board[b.y][b.x] = 1;
				else if (!(board[b.y][b.x]) && neighbours == 3)
					new_board[b.y][b.x] = 1;
				else
					new_board[b.y][b.x] = 0;
			}
		}
		for (int i = 0; i < size_y; i++)
			for (int j = 0; j < size_x; j++)
				board[i][j] = new_board[i][j];
	}
	for (int i = 0; i < size_y; i++){
		for (int j = 0; j < size_x; j++){
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
