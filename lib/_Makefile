NAME = libft.a

# DIRECTORIES 
SRC_DIR = srcs
#OBJS_DIR = objs

#ARCHIVED
#AR = ar rcs

#SRCS & OBJS
SRCS = $(wildcard ./srcs/*.c)
OBJS = $(SRCS:.c=.o)
INCLUDE	= libft.h
#OBJS = $(addprefix $(OBJS_DIR)/,$(SOURCES:.c=.o))

#GAY RULEES
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

#TARJETS

all:	$(NAME)

$(NAME):	$(OBJS) $(INCLUDE)
		ar -rcs $(NAME) $(OBJS)

.c.o:
			$(CC) $(FLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(OBJS) $(NAME)

re: clean all
help:
	@echo "Makefile - make all"