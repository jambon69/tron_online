##
## Makefile for tron in /home/louis/my_projects/games/tron
## 
## Made by louis giesen
## Login   <louis@epitech.net>
## 
## Started on  Sun Oct 25 15:00:54 2015 louis giesen
## Last update Fri Oct 30 20:09:38 2015 louis giesen
##

SRCS =	main.c		\
	aff_droite.c	\
	event.c		\
	menu.c		\
	local.c		\
	add_player.c	\

OBJS =	$(SRCS:.c=.o)

NAME =	tron

CFLAGS = -I./include
CFLAGS += -W -Wall -Wextra -Werror

LDFLAGS += -L. -lSDL -lSDL_mixer -lSDL_image

RM =	rm -f

CC =	gcc -std=c99 -g3 -O2

all: $(NAME) $(SERVER_NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
