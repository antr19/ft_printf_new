NAME = libftprintf.a
SRCS = ft_printf.c ft_l.c

OBJS = $(SRCS:.c=.o)
HEADER = ft_printf.h

FLAGS = -Wall -Werror -Wextra
CC = gcc
RM = rm -f

all:	$(NAME)

run: $(OBJS)
	$(CC) $(FLAGS) $(OBJS)  
# -L. libft/libft.a
	./a.out

run_w:
	gcc $(FLAGS) $(SRCS)
	a.exe


$(NAME):	$(OBJS)
# cp libft/libft.a $(NAME)
	ar rcs $(NAME) $(OBJS)

.c.o: ${HEADER}
# $(MAKE) -C ./libft
	$(CC) $(FLAGS) -c $< -o $@

bonus: re

clean:
# $(MAKE) clean -C ./libft
	$(RM) $(OBJS) $(OBJS_B) 

fclean:	clean
# $(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

# bonus: $(OBJS) $(OBJS_B)
# 	ar rcs $(NAME) $(OBJS) $(OBJS_B)

.PHONY : all clean fclean re