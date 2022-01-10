NAME = libftprintf.a
SRCS = ft_printf.c ft_atoi.c ft_putnbr_fd.c ft_libft.c ft_utils.c\
		ft_struct.c ft_print_int.c ft_print_str.c ft_print_hex.c

SRCS_B = $(SRCS:.c=_bonus.c) 

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

HEADER = ft_printf.h

FLAGS = -Wall -Werror -Wextra
CC = cc
RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)

.c.o: ${HEADER}
	$(CC) $(FLAGS) -c $< -o $@ -I ${HEADER}

bonus: $(OBJS_B)
	ar rcs $(NAME) $(OBJS_B)

clean:
	$(RM) $(OBJS) $(OBJS_B) 

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY : all clean fclean re