SRC = main.c\
	  parse_scene.c\
	  parse_vec.c\
	  parse_type.c\
	  parse_arrays.c\
	  arrays.c\
	  error.c\
	  image.c\
	  intersections.c\
	  intersections_scene.c\
	  v3math.c\
	  color.c\
	  v3.c

OBJ = $(SRC:.c=.o)

NAME = miniRT

CC = cc
CFLAGS = -std=gnu11 -Wall -Wextra -Werror -g3 # -fsanitize=address

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
