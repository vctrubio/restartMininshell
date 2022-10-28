NAME = minishell
SRCS = $(wildcard ./srcs/*.c)
OBJS = $(SRCS:.c=.o)
RM = rm -f
FLAGS = -Werror -Wextra -Wall

LIBFT_PATH		=	./lib
LIBFT			=	$(LIBFT_PATH)/libft.a

$(NAME) : $(OBJS)
	@echo "here from makefile"
	$(MAKE) --directory=lib
	gcc -g $(OBJS) $(LIBFT) -lreadline -o $@

all:	$(NAME)

run: all
	./minishell

clean:
	make clean -C lib
	$(RM) $(OBJS) $(NAME)

re: clean all

