SRC = ft_bzero.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isspace.c\
	ft_isprint.c\
	ft_isnum.c\
	ft_isint.c\
	ft_max.c\
	ft_min.c\
	ft_abs.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memset.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_strlen.c\
	ft_strnstr.c\
	ft_strchr.c\
	ft_strncmp.c\
	ft_strrchr.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putunbr_fd.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_strjoin.c\
	ft_strsjoin.c\
	ft_substr.c\
	ft_strtrim.c\
	ft_itoa.c\
	ft_atoi.c\
	ft_atoi_base.c\
	ft_strtol.c\
	ft_striteri.c\
	ft_strmapi.c\
	ft_split.c\
	ft_lstnew.c\
	ft_lstadd_front.c\
	ft_lstlast.c\
	ft_lstsize.c\
	ft_lstadd_back.c\
	ft_lstdelone.c\
	ft_lstclear.c\
	ft_lstiter.c\
	ft_lstfind.c\
	ft_lstmap.c\
	ft_lstmax.c\
	ft_printf/print_args/print_char.c\
	ft_printf/print_args/print_hex.c\
	ft_printf/print_args/print_num.c\
	ft_printf/print_args/print_str.c\
	ft_printf/ft_printf.c\
	get_next_line/get_next_line.c\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	@echo "built $(NAME)"

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ 

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
