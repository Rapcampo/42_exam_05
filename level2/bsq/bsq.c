#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct bsq{
	int lines;
	char empt;
	char obstacle;
	char fill;
	int w;
	char **map;
};

void	parse(struct bsq *bsq, char *av);
void	resolve(struct bsq *bsq);
void	print_bsq(struct bsq *bsq);
void	free_map(struct bsq *bsq, int lines);

int aborc(int a, int b, int c){
	if (a < b && a < c)
		return a;
	if (b < c)
		return b;
	return c;
}

void	resolve(struct bsq *bsq){
	int board[bsq->lines][bsq->w];
	int max = 0, by = 0, bx = 0;
	for (int i = 0; i < bsq->lines; i++){
		for (int j = 0; j < bsq->w; j++){
			if (bsq->map[i][j] == bsq->obstacle)
				board[i][j] = 0;
			else if (i == 0 || j == 0)
				board[i][j] = 1;
			else
				board[i][j] = aborc(board[i - 1][j], board[i][j - 1], board[i - 1][j - 1]) + 1;
			if (board[i][j] > max){
				max = board[i][j];
				by = i;
				bx = j;
			}
		}
	}
	int st_y = by - max + 1;
	int st_x = bx - max + 1;
	int fy = st_y + max;
	int fx = st_x + max;
	for(int i = st_y; i < fy; i++)
		for(int j = st_x; j < fx; j++)
			bsq->map[i][j] = bsq->fill;
}

void	check_map(struct bsq *bsq){
	for(int i = 0; i < bsq->lines; i++)
		for(int j = 0; j < bsq->lines; j++)
			if (bsq->map[i][j] != bsq->empt && bsq->map[i][j] != bsq->obstacle)
				free_map(bsq, bsq->lines), fputs("map error\n", stdout), exit(1);
}

void	free_map(struct bsq *bsq, int lines){
	for (int j = 0; j < lines; j++){
		free(bsq->map[j]);
	}
	free(bsq->map);
}

void	print_bsq(struct bsq *bsq){
	for (int i = 0; i < bsq->lines; i++)
		printf("%s\n", bsq->map[i]);
}

int ft_strlen(char *str){
	int i;
	for(i = 0; str[i]; i++);
	return i;
}

void error_quit(struct bsq *bsq, char *av, FILE *file, int i){
	if (av)
		fclose(file);
	fputs("map error\n", stdout);
	if (i >= 0)
		free_map(bsq, i);
	exit(1);
}

void parse(struct bsq *bsq, char *av){
	FILE *file;
	if (av)
		file = fopen(av, "r");
	else
		file = stdin;
	if (!file)
		fputs("Map error\n", stdout), exit(1);
	if (fscanf(file, "%d%c%c%c\n", &bsq->lines, &bsq->empt, &bsq->obstacle, &bsq->fill) != 4)
		error_quit(bsq, av, file, -1);
	if (bsq->lines <= 0)
		error_quit(bsq, av, file, -1);
	if (bsq->empt == bsq->fill || bsq->empt == bsq->obstacle || bsq->obstacle == bsq->fill)
		error_quit(bsq, av, file, -1);
	bsq->map = malloc(sizeof(char *) * bsq->lines);	
	for (int i = 0; i < bsq->lines; i++){
		char *new = NULL;
		size_t len = 0;
		int new_len;

		if (getline(&new, &len, file) == -1)
			error_quit(bsq, av, file, -1);
		new_len = ft_strlen(new);
		if (i == 0)
			bsq->w = new_len;
		if (i != 0 && i < bsq->lines - 1 && bsq->w != new_len)
			error_quit(bsq, av, file, -1);
		bsq->map[i] = new;
	}
	fclose(file);
	check_map(bsq);
}

int main(int ac, char **av){
	struct bsq bsq = {0};
	if (ac == 1)
		parse(&bsq, NULL);
	else if (ac == 2)
		parse(&bsq, av[1]);
	else
		return (printf("Error: wrong number of args"), 1);
	resolve(&bsq);
	print_bsq(&bsq);
	free_map(&bsq, bsq.lines);
}
