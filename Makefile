SRC = main.c

OBJ = $(SRC:.c=.o)

NAME = minirt

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3 -std=c99

LIBFTDIR = libs/libft
LIBFT = $(LIBFTDIR)/libft.a

MLXDIR = libs/minilibx-linux
MINILIBX = $(MLXDIR)/libmlx.a

LDFLAGS = -lm -lX11 -lXext \
		  -L$(MLXDIR) -lmlx \
		  -L$(LIBFTDIR) -lft

all: $(NAME)

$(NAME): $(OBJ) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(MINILIBX):
	make -C $(MLXDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	@rm -f $(OBJ)
	make -C $(MLXDIR) clean
	make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
