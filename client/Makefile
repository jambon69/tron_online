##
## Makefile for make in /home/louis/my_projects/super_tron/client
## 
## Made by louis giesen
## Login   <louis@epitech.net>
## 
## Started on  Sat Nov 28 18:00:56 2015 louis giesen
## Last update Sat Nov 28 18:44:13 2015 louis giesen
##

SRCS =	main.c		\
	game.c		\
	modif_pov.c	\

OBJS =	$(SRCS:.c=.o)

NAME =	tron

CFLAGS +=	-I./include
CFLAGS +=	-W -Wall -Wextra

LDFLAGS =	-lSDL -lSDL_mixer -lSDL_image -lGL -lGLU

CC =	gcc

RM =	rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
