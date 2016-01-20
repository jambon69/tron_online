##
## Makefile for  in /home/louis/my_projects/super_tron/server
## 
## Made by louis giesen
## Login   <louis@epitech.net>
## 
## Started on  Mon Oct 26 11:32:13 2015 louis giesen
## Last update Sun Nov  1 20:47:01 2015 louis giesen
##

SRCS =	server.c 	\
	map.c		\

OBJS =	$(SRCS:.c=.o)

NAME =	server

CFLAGS =	-I./

CC   =	gcc -std=c99

LDFLAGS =	-lpthread

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
