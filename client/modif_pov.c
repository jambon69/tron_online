/*
** modif_pov.c for  in /home/jankov_n/rendu/CPE_2014_lemin/parser
**
** Made by nicolas jankovic
** Login   <jankov_n@epitech.net>
**
** Started on  Fri Sep 18 15:57:52 2015 nicolas jankovic
** Last update Sat Nov 28 19:14:40 2015 louis giesen
*/

#include "tron.h"

void	modif_cam_z(t_camera *camera, t_coord *player, int symbol)
{
  (void) player;
  if (symbol == 0)
    camera->eye_z--;
  else if (symbol == 1)
    camera->eye_z++;
}

void	modif_cam_y(t_camera *camera, t_coord *player, int symbol)
{
  (void) player;
  if (symbol == 0)
    camera->eye_y--;
  else if (symbol == 1)
    camera->eye_y++;
}

void	modif_cam_x(t_camera *camera, t_coord *player, int symbol)
{
  (void) player;
  if (symbol == 0)
    camera->eye_x--;
  else if (symbol == 1)
    camera->eye_x++;
}
