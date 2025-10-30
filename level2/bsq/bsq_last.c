#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct bsq{
	int w;
	int h;
	char e;
	char o;
	char f;
	char **map;
};

struct vec{
	int x;
	int y;
};

#define ERR_MAP "Error: invalid map\n"

void	parse(struct bsq *bsq, char *av);
void	resolve(struct bsq *bsq);
void	freemap(struct bsq *bsq, int lines);
void	print_bsq(struct bsq *bsq);
void	err_quit(struct bsq *bsq, char *av, FILE *file, int i);
void	check(struct bsq *bsq);
int		ft_strlen(char *str);
int		min3(int a, int b, int c);

void	parse(struct bsq *bsq, char *av){
	FILE *file;
	if (av)
		file = fopen(av, "r");
	else
		file = stdin;
	if (!file)
		fputs(ERR_MAP, stdout), exit(1);
	if (fscanf(file, "%d%c%c%c\n", &bsq->h, &bsq->e, &bsq->o, &bsq->f) != 4)
		fputs(ERR_MAP, stdout), err_quit(bsq, av, file, -1);
	if (bsq->h <= 0)
		fputs(ERR_MAP, stdout), err_quit(bsq, av, file, -1);
	else if (bsq->e == bsq->o || bsq->e == bsq->f || bsq->f == bsq->o)
		fputs(ERR_MAP, stdout), err_quit(bsq, av, file, -1);
	bsq->map = malloc(sizeof(char *) * bsq->h);
	if (!bsq->map)
		fputs("Error: malloc error", stdout), err_quit(bsq, av, file, -1);
	for (int i = 0; i < bsq->h; i++){
		char *line = NULL;
		size_t len = 0;
		int nlen = 0;
		if (getline(&line, &len, file) == -1)
			fputs("Error: malloc error", stdout), err_quit(bsq, av, file, i);
		nlen = ft_strlen(line);
		if (i < bsq->h - 1 && line[nlen - 1] == '\n')
			line[nlen - 1] = '\0';
		else if (line[nlen - 1] != '\n')
			fputs(ERR_MAP, stdout), free(line), err_quit(bsq, av, file, i);
		nlen = ft_strlen(line);
		if (i == 0)
			bsq->w = nlen;
		else if (i < bsq->h - 1 && bsq->w != nlen)
			fputs(ERR_MAP, stdout), free(line), err_quit(bsq, av, file, i);
		bsq->map[i] = line;
	}
	fclose(file);
	check(bsq);
}

void	resolve(struct bsq *bsq){
	int board[bsq->h][bsq->w];
	struct vec v = {0};
	struct vec st = {0};
	struct vec f = {0};
	int max = 0;
	for (int y = 0; y < bsq->h; y++){
		for (int x = 0; x < bsq->w; x++){
			if (bsq->map[y][x] == bsq->o)
				board[y][x] = 0;
			else if (y == 0 || x == 0)
				board[y][x] = 1;
			else
				board[y][x] = min3(board[y - 1][x], board[y][x - 1], board[y - 1][x - 1]) + 1;
			if (board[y][x] > max){
				max = board[y][x];
				v.y = y;
				v.x = x;
			}
		}
	}
	if (max == 0)
		fputs(ERR_MAP,stdout), err_quit(bsq, NULL, NULL, bsq->h);
	st.y = v.y - max + 1;
	st.x = v.x - max + 1;
	f.y = st.y + max;
	f.x = st.x + max;
	for (int y = st.y; y < f.y; y++)
		for (int x = st.x; x < f.x; x++)
			bsq->map[y][x] = bsq->f;
}

int main(int ac, char **av){
	struct bsq bsq = {0};
	if (ac == 1)
		parse(&bsq, NULL);
	else if (ac == 2)
		parse(&bsq, av[1]);
	else
		return (fputs("Error: too many arguments\n", stdout), 1);
	resolve(&bsq);
	print_bsq(&bsq);
	freemap(&bsq, bsq.h);
	return 0;
}

int min3(int a, int b, int c){
	int min = a < b ? a : b;
	return min < c ? min : c;
}

int ft_strlen(char *str){
	int i;
	for (i = 0; str[i]; i++);
	return i;
}

void	check(struct bsq *bsq){
	for (int y = 0; y < bsq->h; y++){
		for (int x = 0; x < bsq->w; x++){
			if (bsq->map[y][x] != bsq->e && bsq->map[y][x] != bsq->o){
				fputs(ERR_MAP, stdout),err_quit(bsq, NULL, NULL, bsq->h);
			}
		}
	}
}

void	err_quit(struct bsq *bsq, char *av, FILE *file, int i){
	if (av)
		fclose(file);
	if (i >= 0)
		freemap(bsq, i);
	exit(1);
}

void	print_bsq(struct bsq *bsq){
	for (int i = 0; i < bsq->h; i++)
		printf("%s\n", bsq->map[i]);
	printf("\n");
}

void	freemap(struct bsq *bsq, int lines){
	if (lines){
		for (int i = 0; i < lines; i++)
			free(bsq->map[i]);
		free(bsq->map);
	}
}
