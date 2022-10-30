# NAME = minishell
# SRCS = $(wildcard ./srcs/*.c)
# OBJS = $(SRCS:.c=.o)
# RM = rm -f
# FLAGS = -Werror -Wextra -Wall

# LIBFT_PATH		=	./lib
# LIBFT			=	$(LIBFT_PATH)/libft.a

# $(NAME) : $(OBJS)
# 	@echo "here from makefile"
# 	$(MAKE) --directory=lib
# 	gcc -g $(OBJS) $(LIBFT) -lreadline -o $@

# all:	$(NAME)

# run: all
# 	./minishell

# clean:
# 	make clean -C lib
# 	$(RM) $(OBJS) $(NAME)

# re: clean all

NAME		=	minishell

HEADER		=	./include/

LIBFT		=	lib/libft.a

CC			=	gcc

# CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) -lreadline #-fsanitize=address
CFLAGS		=	 -g -I $(HEADER)  -fsanitize=address 

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

fclean		:	clean
				rm $(NAME)
				make fclean -C ./lib

re			:	fclean all