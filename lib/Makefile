# NAME = libft.a

# # DIRECTORIES 
# SRC_DIR = srcs
# #OBJS_DIR = objs

# #ARCHIVED
# #AR = ar rcs

# #SRCS & OBJS
# SRCS = $(wildcard ./srcs/*.c)
# OBJS = $(SRCS:.c=.o)
# INCLUDE	= libft.h
# #OBJS = $(addprefix $(OBJS_DIR)/,$(SOURCES:.c=.o))

# #GAY RULEES
# CC = gcc
# FLAGS = -Wall -Wextra -Werror
# RM = rm -f

# #TARJETS

# all:	$(NAME)

# $(NAME):	$(OBJS) $(INCLUDE)
# 		ar -rcs $(NAME) $(OBJS)

# .c.o:
# 			$(CC) $(FLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)

# clean:
# 	$(RM) $(OBJS) $(NAME)

# re: clean all
# help:
# 	@echo "Makefile - make all"

NAME 		= libft.a
HEADER 		= libft.h
SRC 		= $(wildcard ./srcs/*.c)
# BONUS 		= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
# 		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
# 		ft_lstnew.c ft_lstsize.c
OBJ 		= ${SRC:.c=.o}
# BONUS_OBJS	= $(BONUS:.c=.o)
FLAGS 		= -Wall -Wextra -Werror #$-fsanitize=address

all: ${NAME}

$(NAME): ${OBJ}
	ar -rs ${NAME} ${OBJ}

%.o: %.c 
	gcc ${FLAGS} -c -o $@ $<

bonus: ${NAME} ${BONUS} ${BONUS_OBJS}
	ar -rs ${NAME} ${OBJ} ${BONUS_OBJS}

clean:
	rm -f ${OBJ} ${BONUS_OBJS}

.PHONY: clean
fclean: clean
	rm -f ${NAME}

re: fclean all