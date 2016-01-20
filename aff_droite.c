/*
** aff_droite.c for droite  in /home/giesen_l/jeu_1D
**
** Made by Louis Giesen
** Login   <giesen_l@epitech.net>
**
** Started on  Sun Apr  5 21:32:37 2015 Louis Giesen
** Last update Sun Oct 25 15:04:28 2015 louis giesen
*/

#include "tron.h"

void		sdl_putpixel(SDL_Surface *surface, int x,
			     int y, unsigned long pixel)
{
  int		bpp;

  bpp = surface->format->BytesPerPixel;
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
  switch (bpp)
    {
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
	p[0] = (pixel >> 16) & 0xff;
	p[1] = (pixel >> 8) & 0xff;
	p[2] = pixel & 0xff;
      }
      else
	{
	  p[0] = pixel & 0xff;
	  p[1] = (pixel >> 8) & 0xff;
	  p[2] = (pixel >> 16) & 0xff;
	}
      break;
    case 4:
      *(Uint32 *)p = pixel;
      break;
    }
}

static int	init_point(t_coord *point)
{
  point->diff.x = point->point2.x - point->point1.x;
  point->diff.y = point->point2.y - point->point1.y;
  point->inc.x = 1;
  point->inc.y = 1;
  return (0);
}

static int	who_is_superior(t_coord *point)
{
  if (point->diff.x < 0)
    point->diff.x = point->diff.x * (-1);
  if (point->diff.y < 0)
    point->diff.y = point->diff.y * (-1);
  if (point->point2.x < point->point1.x)
    point->inc.x = -1;
  if (point->point2.y < point->point1.y)
    point->inc.y = -1;
  point->super_point.x = point->point1.x;
  point->super_point.y = point->point1.y;
  return (0);
}

static int	first_condition(t_sdl *ptr, int e, int i, t_coord *point)
{
  sdl_putpixel(ptr->ecran, point->super_point.x,
	       point->super_point.y, ptr->color);
  e = (2 * point->diff.y) - point->diff.x;
  point->super_inc.x = 2 * (point->diff.y - point->diff.x);
  point->super_inc.y = 2 * (point->diff.y);
  while (i < point->diff.x)
    {
      if (e >= 0)
	{
	  point->super_point.y = point->super_point.y + point->inc.y;
	  e = e + point->super_inc.x;
	}
      else
	e = e + point->super_inc.y;
      point->super_point.x = point->super_point.x + point->inc.x;
      sdl_putpixel(ptr->ecran, point->super_point.x,
		   point->super_point.y, ptr->color);
      i = i + 1;
    }
  return (i);
}

static int	seconde_condition(t_sdl *ptr, int e, int i, t_coord *point)
{
  sdl_putpixel(ptr->ecran, point->super_point.x,
	       point->super_point.y, ptr->color);
  e = (2 * point->diff.x) - point->diff.y;
  point->super_inc.y = 2 * (point->diff.x - point->diff.y);
  point->super_inc.x = 2 * (point->diff.x);
  while (i < point->diff.y)
    {
      if (e >= 0)
	{
	  point->super_point.x = point->super_point.x + point->inc.x;
	  e = e + point->super_inc.y;
	}
      else
	e = e + point->super_inc.x;
      point->super_point.y = point->super_point.y + point->inc.y;
      sdl_putpixel(ptr->ecran, point->super_point.x,
		   point->super_point.y, ptr->color);
      i = i + 1;
    }
  return (i);
}

int	affiche_droite(t_sdl *ptr, t_coord *point)
{
  int		e;
  int		i;
  int		red;

  init_point(point);
  i = 0;
  e = 0;
  who_is_superior(point);
  red = SDL_MapRGB(ptr->ecran->format, 0xFF, 0x00, 0x00);
  ptr->color = red;
  if (point->diff.x > point->diff.y)
    i = first_condition(ptr, e, i, point);
  else
    i = seconde_condition(ptr, e, i, point);
  return (0);
}
