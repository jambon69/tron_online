/*
** main.c for tron in /home/louis/my_projects/games/tron
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Sun Oct 25 14:50:55 2015 louis giesen
** Last update Fri Oct 30 21:14:58 2015 louis giesen
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "textures.h"
#include "tron.h"

extern int h_errno;

#define PORT 22000

int	init_menu(t_ptr *ptr)
{
  if ((ptr->menu.menu = IMG_Load("images/menu_fond.png")) == NULL
      || (ptr->menu.menu_connect = IMG_Load("images/menu_connect.png")) == NULL
      || (ptr->menu.menu_connect_push = IMG_Load("images/menu_connect_push.png")) == NULL
      || (ptr->menu.wait_others = IMG_Load("images/wait_others.png")) == NULL
      || (ptr->menu.menu_local = IMG_Load("images/menu_local.png")) == NULL)
    return (EXIT_FAILURE);
  ptr->menu.pos_menu.x = 0;
  ptr->menu.pos_menu.y = 0;
  return (EXIT_SUCCESS);
}

int	init_ptr(t_ptr *ptr)
{
  if ((ptr->sdl.ecran =
       SDL_SetVideoMode(WINX, WINY, 32, SDL_HWSURFACE)) == NULL
      || (ptr->sdl.void_screen = IMG_Load("images/void_screen.png")) == NULL)
    return (EXIT_FAILURE);
  ptr->player = NULL;
  SDL_WM_SetCaption("TRON", NULL);
  SDL_Init(SDL_INIT_VIDEO);
  ptr->moto.dir = BAS;
  ptr->moto.color = SDL_MapRGB(ptr->sdl.ecran->format, 0xFF, 0xFF, 0x00);
  if (init_menu(ptr) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

long			init_network(char *ip)
{
  long			sock;
  struct sockaddr_in	sin;
  struct protoent	*proto;

  proto = getprotobyname("TCP");
  sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
  bzero(&sin, sizeof(sin));
  if (sock == -1)
    {
      fprintf(stderr, "socket()");
      exit(EXIT_FAILURE);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
  sin.sin_addr.s_addr = inet_addr(ip);
  if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) != 0)
    {
      printf("Server not running.\n");
      exit(1);
    }
  return (sock);
}

int	wait_the_start(int sock, t_ptr *ptr, char *name)
{
  int	buffer[3];

  if (send(sock, name, sizeof(char) * 3, 0) < 0)
    {
      printf("camarchepas\n");
      exit (EXIT_FAILURE);
    }
  if (recv(sock, buffer, sizeof(int) * 3, 0) < 0)
    {
      printf("recv failed\n");
      exit(EXIT_FAILURE);
    }
  ptr->moto.nb_player = (int) buffer[0];
  ptr->moto.x = (int) buffer[1];
  ptr->moto.y = (int) buffer[2];
  return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
  t_ptr		ptr;
  int		sock = -1;
  char		name[3] = "AAA";
  t_player	*first;

  if (ac < 2)
    {
      printf("USAGE : ./tron IP\n");
      return (EXIT_FAILURE);
    }
  if (init_ptr(&ptr) == EXIT_FAILURE)
    {
      printf("Something went wrong during initialisation\n");
      return (EXIT_FAILURE);
    }
  while (42)
    {
      if (menu(&ptr) == ONLINE)
	{
	  sock = init_network(av[1]);
	  wait_the_start(sock, &ptr, name);
	  if ((various_events(&ptr, sock)) == EXIT_FAILURE)
	    {
	      printf("Something went wrong during game\n");
	      return (EXIT_FAILURE);
	    }
	  send(sock, "ST", sizeof(char) * 2, 0);
	  shutdown(sock, 2);
	}
      else
	{
	  local_events(&ptr);
	  first = ptr.player;
	  while (ptr.player != NULL)
	    {
	      ptr.player->dead = 0;
	      ptr.player = ptr.player->next;
	    }
	  ptr.player = first;
	}
    }
  return (EXIT_SUCCESS);
}
