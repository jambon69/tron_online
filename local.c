/*
** local.c for tron in /home/louis/my_projects/super_tron
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Fri Oct 30 19:34:27 2015 louis giesen
** Last update Sun Nov  1 20:43:10 2015 louis giesen
*/

#include <stdlib.h>
#include "tron.h"

char	**local_map;

int	local_blit_this(t_ptr *ptr)
{
  t_player	*first;

  first = ptr->player;
  while (ptr->player != NULL)
    {
      if (ptr->player->dead == 1)
	{
	  ptr->player = ptr->player->next;
	  continue ;
	}
      if (ptr->player->moto.dir == HAUT)
	ptr->player->moto.y--;
      else if (ptr->player->moto.dir == BAS)
	ptr->player->moto.y++;
      else if (ptr->player->moto.dir == GAUCHE)
	ptr->player->moto.x--;
      else if (ptr->player->moto.dir == DROITE)
	ptr->player->moto.x++;
      if (ptr->player->moto.x <= 0
	  || ptr->player->moto.x >= WINX
	  || ptr->player->moto.y <= 0
	  || ptr->player->moto.y >= WINY)
	ptr->player->dead = 1;
      if (local_map[ptr->player->moto.y][ptr->player->moto.x] != 0)
	ptr->player->dead = 1;
      local_map[ptr->player->moto.y][ptr->player->moto.x] =
	ptr->player->moto.nb_player;
      sdl_putpixel(ptr->sdl.ecran, ptr->player->moto.x,
		   ptr->player->moto.y, ptr->player->moto.color);
      ptr->player = ptr->player->next;
    }
  ptr->player = first;
  return (EXIT_SUCCESS);
}

int	local_move(t_ptr *ptr, int dir)
{
  if (dir == GAUCHE)
    ptr->player->moto.dir = (ptr->player->moto.dir == HAUT ? GAUCHE :
			    ptr->player->moto.dir == BAS ? DROITE :
			    ptr->player->moto.dir == GAUCHE ? BAS :
			    HAUT);
  else
    ptr->player->moto.dir = (ptr->player->moto.dir == HAUT ? DROITE :
			    ptr->player->moto.dir == BAS ? GAUCHE :
			    ptr->player->moto.dir == GAUCHE ? HAUT :
			    BAS);
  return (EXIT_SUCCESS);
}

int	local_action(t_ptr *ptr, int key)
{
  t_player	*first;

  first = ptr->player;
  while (ptr->player != NULL)
    {
      if (ptr->player->dead == 1)
	{
	  ptr->player = ptr->player->next;
	  continue ;
	}
      if (key == ptr->player->keys.left)
	local_move(ptr, GAUCHE);
      else if (key == ptr->player->keys.right)
	local_move(ptr, DROITE);
      ptr->player = ptr->player->next;
    }
  ptr->player = first;
  return (EXIT_SUCCESS);
}

int	local_events(t_ptr *ptr)
{
  int	keypress = 0;

  local_map = init_map();
  SDL_FillRect(ptr->sdl.ecran, NULL, 0x000000);
  SDL_Flip(ptr->sdl.ecran);
  while (42)
    {
      SDL_Delay(10);
      SDL_PollEvent(&ptr->sdl.event);
      if (ptr->sdl.event.type == SDL_QUIT)
	exit (EXIT_SUCCESS);
      else if (ptr->sdl.event.type == SDL_KEYDOWN && keypress == 0)
	{
	  if (ptr->sdl.event.key.keysym.sym == ESC)
	    return (EXIT_SUCCESS);
	  local_action(ptr, ptr->sdl.event.key.keysym.sym);
	  keypress = 1;
	}
      else if (ptr->sdl.event.type == SDL_KEYUP)
	keypress = 0;
      local_blit_this(ptr);
      SDL_Flip(ptr->sdl.ecran);
    }
  return (EXIT_SUCCESS);
}
