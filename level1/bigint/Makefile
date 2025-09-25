NAME = bigint
FILES = *.cpp
OBJS = *.o

all: $(NAME)


$(NAME): $(OBJS)
	c++ -Wall -Wextra -Werror -g -fsanitize=address $(OBJS) -o $(NAME)

$(OBJS):
	c++ -Wall -Wextra -Werror -g -fsanitize=address -c $(FILES) bigint.hpp
