NAME		=	minishell

HEADER		=	./include/

LIBFT		=	lib/libft.a

CC			=	gcc

# CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) -lreadline -fsanitize=address
CFLAGS		=	 -Werror -Wall -Wextra -g -I $(HEADER)  -fsanitize=address

SRCS		=	$(wildcard ./srcs/*.c)

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT)	:
				make -C ./lib

clean		:
				rm -rf $(OBJS)
				make clean -C ./lib
run			: $(all)
				./minishell


fclean		:	clean
				rm $(NAME)
				make fclean -C ./lib

re			:	fclean all