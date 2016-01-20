/*
** event.c for tron in /home/louis/my_projects/games/tron
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Sun Oct 25 15:09:41 2015 louis giesen
** Last update Fri Oct 30 19:34:13 2015 louis giesen
*/

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "tron.h"

char	**init_map()
{
  char	**new = NULL;

  if ((new = malloc(sizeof(char *) * WINY)) == NULL)
    return (NULL);
  for (int i = 0; i < WINY; i++)
    {
      if ((new[i] = malloc(sizeof(char) * WINX)) == NULL)
	return (NULL);
      for (int j = 0; j < WINX; j++)
	new[i][j] = 0;
    }
  return (new);
}

int		hey_server_move_it(int sock, int x, int y, t_ptr *ptr)
{
  int		buffer[3];
  int		i = 1000;

  buffer[0] = ptr->moto.nb_player;
  buffer[1] = x;
  buffer[2] = y;
  while (send(sock, buffer, sizeof(int) * 3, 0) < 0)
    {
      if (i-- > 0)
	fprintf(stderr, "Je re-essaie...\n");
      else
	return (-1);
    }
  return (0);
}

int		hey_server_tell_me_what_is_new(int sock, t_ptr *ptr)
{
  int		buffer[3];
  int		c;

  buffer[0] = 0;
  buffer[1] = 0;
  buffer[2] = 0;
  while ((c = recv(sock, buffer, sizeof(*buffer) * 3, MSG_DONTWAIT)) > 0)
    {
      if (c != sizeof(*buffer) * 3)
	continue ;
      if (buffer[0] == 1)
	{
	  sdl_putpixel(ptr->sdl.ecran, buffer[1], buffer[2],
		       SDL_MapRGB(ptr->sdl.ecran->format, 0x00, 0xFF, 0xFF));
	}
      else if (buffer[0] == 2)
	{
	  sdl_putpixel(ptr->sdl.ecran, buffer[1], buffer[2],
		       SDL_MapRGB(ptr->sdl.ecran->format, 0x00, 0xFF, 0x00));
	}
      else if (buffer[0] == 3)
	{
	  sdl_putpixel(ptr->sdl.ecran, buffer[1], buffer[2],
		       SDL_MapRGB(ptr->sdl.ecran->format, 0xFF, 0x00, 0x00));
	}
      else if (buffer[0] == 4)
	{
	  sdl_putpixel(ptr->sdl.ecran, buffer[1], buffer[2],
		       SDL_MapRGB(ptr->sdl.ecran->format, 0xFF, 0x00, 0xFF));
	}
      SDL_Flip(ptr->sdl.ecran);
    }
  return (0);
}

int	move_it(t_ptr *ptr, char **map, int sock, int dead)
{
  if (dead == 0)
    {
      if (ptr->moto.dir == HAUT)
	ptr->moto.y--;
      else if (ptr->moto.dir == BAS)
	ptr->moto.y++;
      else if (ptr->moto.dir == GAUCHE)
	ptr->moto.x--;
      else if (ptr->moto.dir == DROITE)
	ptr->moto.x++;
      if (ptr->moto.x <= 0
	  || ptr->moto.x >= WINX
	  || ptr->moto.y <= 0
	  || ptr->moto.y >= WINY)
	return (LOST);
      if (map[ptr->moto.y][ptr->moto.x] != 0)
	return (LOST);
      map[ptr->moto.y][ptr->moto.x] = ptr->moto.nb_player;
    }
  if (hey_server_move_it(sock, ptr->moto.x, ptr->moto.y, ptr) == -1)
    return (LOST);
  sdl_putpixel(ptr->sdl.ecran, ptr->moto.x, ptr->moto.y, ptr->moto.color);
  SDL_Flip(ptr->sdl.ecran);
  return (CONTINUE);
}

int	various_events(t_ptr *ptr, int sock)
{
  Uint8	*keys = SDL_GetKeyState(NULL);
  int	keypress = 0;
  char	to_send[2];
  int	temps_precedent = 0;
  int	temps_actuel;

  SDL_FillRect(ptr->sdl.ecran, NULL, 0x000000);
  SDL_Flip(ptr->sdl.ecran);
  while (42)
    {
      temps_actuel = SDL_GetTicks();
      if (temps_actuel - temps_precedent > 15)
	{
	  hey_server_tell_me_what_is_new(sock, ptr);
	  SDL_PollEvent(&ptr->sdl.event);
	  /* SDL_Delay(10); */
	  if (ptr->sdl.event.type == SDL_QUIT)
	    break ;
	  else if (ptr->sdl.event.type == SDL_KEYDOWN && keypress == 0)
	    {
	      keypress = 1;
	      if (keys[ESC])
		break ;
	      else if (keys[LEFT])
		{
		  to_send[0] = ptr->moto.nb_player;
		  to_send[1] = GAUCHE;
		  if (send(sock, to_send, sizeof(*to_send) * 2, 0) < 0)
		    {
		      printf("send failed\n");
		      return (EXIT_SUCCESS);
		    }
		}
	      else if (keys[RIGHT])
		{
		  to_send[0] = ptr->moto.nb_player;
		  to_send[1] = DROITE;
		  if (send(sock, to_send, sizeof(*to_send) * 2, 0) < 0)
		    {
		      printf("send failed\n");
		      return (EXIT_SUCCESS);
		    }
		}
	    }
	  if (ptr->sdl.event.type == SDL_KEYUP)
	    keypress = 0;
	  to_send[0] = ptr->moto.nb_player;
	  to_send[1] = HAUT;
	  if (send(sock, to_send, sizeof(*to_send) * 2, 0) < 0)
	    {
	      printf("send failed\n");
	      return (EXIT_SUCCESS);
	    }
	  temps_precedent = temps_actuel;
	}
    }
  return (EXIT_SUCCESS);
}
