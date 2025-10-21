#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct bsq{
	char empt;
	char obst;
	char fill;
	int height;
	int width;
	char **map;
};

struct vec{
	int x;
	int y;
};

#define ERR_MAP "Error: invalid map\n"

void	error_quit(struct bsq *bsq, char *av, FILE *file, int i);//done
void	resolve(struct bsq *bsq);//to do
void	parse(struct bsq *bsq, char *av);//done
void	print_bsq(struct bsq *bsq);//done
void	free_map(struct bsq *bsq, int height);//done
int		min3(int a, int b, int c);//done
int		ft_strlen(char *str);//done
void	check_map(struct bsq *bsq);//done

int min3(int a, int b, int c){
	int min = a < b ? a : b;
	return min < c ? min : c;
}

int ft_strlen(char *str){
	int i;
	for(i = 0; str[i]; i++);
	return i;
}

void	free_map(struct bsq *bsq, int height){
	for(int i = 0; i < height; i++)
		free(bsq->map[i]);
	free(bsq->map);
}

void	error_quit(struct bsq *bsq, char *av, FILE *file, int height){
	if (av)
		fclose(file);
	if (height >= 0)
		free_map(bsq, height);
	exit(1);
}

void	parse(struct bsq *bsq, char *av){
	FILE *file;
	if (av)
		file = fopen(av, "r"); 
	else
		file = stdin;
	if (!file)
		printf("file error"),fputs(ERR_MAP, stdout), exit(1);
	if (fscanf(file, "%d%c%c%c\n", &bsq->height, &bsq->empt, &bsq->obst, &bsq->fill) != 4)
		printf("fscanf error"),fputs(ERR_MAP, stdout), error_quit(bsq, av, file, -1);
	else if (bsq->empt == bsq->obst || bsq->empt == bsq->fill
			|| bsq->obst == bsq->fill)
		fputs(ERR_MAP, stdout), error_quit(bsq, av, file, -1);
	if (bsq->height <= 0)
		fputs(ERR_MAP, stdout), error_quit(bsq, av, file, -1);

	bsq->map = malloc(sizeof(char *) * bsq->height);
	for (int i = 0; i < bsq->height; i++){
		char *nline = NULL;
		size_t len = 0;
		int new_len;

		if (getline(&nline, &len, file) == -1)
			fputs(ERR_MAP, stdout), error_quit(bsq, av, file, -1);
		new_len = ft_strlen(nline);
		if (new_len > 0 && nline[new_len - 1] == '\n')
			nline[new_len - 1] = '\0';
		else if (i < bsq->height - 1 && nline[new_len - 1] != '\n')
			fputs(ERR_MAP, stdout), error_quit(bsq, av, file, i);
		new_len = ft_strlen(nline);
		if (i == 0)
			bsq->width = new_len;
		if (i != 0 && i < bsq->height - 1 && bsq->width != new_len)
			fputs(ERR_MAP, stdout), error_quit(bsq, av, file, i);
		bsq->map[i] = nline;
	}
	fclose(file);
	check_map(bsq);
}

void	check_map(struct bsq *bsq){
	for (int y = 0; y < bsq->height; y++){
		for (int x = 0; x < bsq->height; x++)
			if (bsq->map[y][x] != bsq->empt && bsq->map[y][x] != bsq->obst)
				free_map(bsq, bsq->height), fputs(ERR_MAP, stdout), exit(1);
	}
}

void	print_bsq(struct bsq *bsq){
	for (int i = 0; i < bsq->height; i++)
		printf("%s\n", bsq->map[i]);
}

void	resolve(struct bsq *bsq){
	int board[bsq->height][bsq->width];
	int max = 0;
	struct vec v = {0};
	for (int y = 0; y < bsq->height; y++){
		for (int x = 0; x < bsq->width; x++){
			if (bsq->map[y][x] == bsq->obst)
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
			fputs(ERR_MAP, stdout), error_quit(bsq, NULL, NULL, bsq->height);
	struct vec st = {0};
	struct vec f = {0};
	st.y = v.y - max + 1;
	st.x = v.x - max + 1;
	f.y = st.y + max;
	f.x = st.x + max;
	for (int y = st.y; y < f.y; y++)
		for (int x = st.x; x < f.x; x++)
			bsq->map[y][x] = bsq->fill;
}

int main(int ac, char **av){
	struct bsq bsq = {0};
	if (ac == 1)
		parse(&bsq, NULL);
	else if (ac == 2)
		parse(&bsq, av[1]);
	else
		return fputs("Error: Too many args", stdout), 1;
	resolve(&bsq);
	print_bsq(&bsq);
	free_map(&bsq, bsq.height);
	return 0;
}
