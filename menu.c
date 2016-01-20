/*
** menu.c for tron in /home/louis/my_projects/super_tron
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Mon Oct 26 12:53:50 2015 louis giesen
** Last update Fri Oct 30 21:13:44 2015 louis giesen
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tron.h"

void	fill_mouse_motion(t_ptr *ptr, SDL_Rect pos)
{
  SDL_BlitSurface(ptr->menu.menu, NULL, ptr->sdl.ecran, &ptr->menu.pos_menu);
  ptr->menu.mouse_x = ptr->sdl.event.motion.x;
  ptr->menu.mouse_y = ptr->sdl.event.motion.y;
  if (ptr->menu.mouse_x > 225 && ptr->menu.mouse_x < 925
      && ptr->menu.mouse_y > 500 && ptr->menu.mouse_y < 720)
    SDL_BlitSurface(ptr->menu.menu_connect_push, NULL, ptr->sdl.ecran, &pos);
  else
    SDL_BlitSurface(ptr->menu.menu_connect, NULL, ptr->sdl.ecran, &pos);
  SDL_Flip(ptr->sdl.ecran);
}

int	new_challenger(t_ptr *ptr)
{
  int	left;
  int	right;
  int	leave = 0;

  while (42)
    {
      if (leave == 2)
	break ;
      SDL_WaitEvent(&ptr->sdl.event);
      if (ptr->sdl.event.type == SDL_KEYDOWN)
	{
	  if (leave == 0)
	    left = ptr->sdl.event.key.keysym.sym;
	  else if (leave == 1)
	    right = ptr->sdl.event.key.keysym.sym;
	  leave++;
	}
    }
  ptr->player = add_player(ptr->player, left, right, "player");
  return (0);
}

int	menu_local(t_ptr *ptr)
{
  SDL_Rect	pos;

  pos.x = 0;
  pos.y = 0;
  SDL_BlitSurface(ptr->menu.menu_local, NULL, ptr->sdl.ecran, &pos);
  SDL_Flip(ptr->sdl.ecran);
  while (42)
    {
      SDL_WaitEvent(&ptr->sdl.event);
      if (ptr->sdl.event.type == SDL_KEYDOWN
	  && ptr->sdl.event.key.keysym.sym == ESC)
	return (0);
      else if (ptr->sdl.event.type == SDL_MOUSEMOTION)
	{
	  ptr->menu.mouse_x = ptr->sdl.event.motion.x;
	  ptr->menu.mouse_y = ptr->sdl.event.motion.y;
	}
      else if (ptr->sdl.event.type == SDL_MOUSEBUTTONDOWN)
	{
	  if ((ptr->menu.mouse_x > 600 && ptr->menu.mouse_x < 700)
	      && (ptr->menu.mouse_y > 340 && ptr->menu.mouse_y < 380))
	    return (1);
	  else if ((ptr->menu.mouse_x > 800 && ptr->menu.mouse_x < 1200)
	      && (ptr->menu.mouse_y > 640 && ptr->menu.mouse_y < 680))
	    new_challenger(ptr);
	  else if ((ptr->menu.mouse_x > 200 && ptr->menu.mouse_x < 600)
	      && (ptr->menu.mouse_y > 640 && ptr->menu.mouse_y < 680))
	    remove_player(ptr->player);
	}
    }
  return (0);
}

char	*my_strdup(char *str)
{
  int	i = 0;
  char	*str2;

  if ((str2 = malloc(sizeof(char) * (strlen(str) + 1))) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      str2[i] = str[i];
      i++;
    }
  str2[i] = '\0';
  return (str2);
}

int		menu(t_ptr *ptr)
{
  SDL_Rect	pos;

  pos.x = 240;
  pos.y = 400;
  SDL_BlitSurface(ptr->menu.menu, NULL, ptr->sdl.ecran, &ptr->menu.pos_menu);
  SDL_BlitSurface(ptr->menu.menu_connect, NULL, ptr->sdl.ecran, &pos);
  SDL_Flip(ptr->sdl.ecran);
  while (42)
    {
      SDL_WaitEvent(&ptr->sdl.event);
      if (ptr->sdl.event.type == SDL_QUIT)
	exit (EXIT_SUCCESS);
      else if (ptr->sdl.event.type == SDL_KEYDOWN
	       && ptr->sdl.event.key.keysym.sym == ESC)
	exit (EXIT_SUCCESS);
      else if (ptr->sdl.event.type == SDL_MOUSEMOTION)
	fill_mouse_motion(ptr, pos);
      else if (ptr->sdl.event.type == SDL_MOUSEBUTTONDOWN
	       && (ptr->menu.mouse_x > 225 && ptr->menu.mouse_x < 925)
	       && (ptr->menu.mouse_y > 500 && ptr->menu.mouse_y < 720))
	break ;
      else if (ptr->sdl.event.type == SDL_MOUSEBUTTONDOWN
	       && (ptr->menu.mouse_x > 275 && ptr->menu.mouse_x < 925)
	       && (ptr->menu.mouse_y > 150 && ptr->menu.mouse_y < 300))
	if (menu_local(ptr) == 1)
	  return (LOCAL);
    }
  SDL_BlitSurface(ptr->menu.wait_others, NULL, ptr->sdl.ecran, &pos);
  SDL_Flip(ptr->sdl.ecran);
  return (ONLINE);
}
