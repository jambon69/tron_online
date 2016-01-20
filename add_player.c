/*
** add_player.c for tron in /home/louis/my_projects/super_tron
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Fri Oct 30 20:00:22 2015 louis giesen
** Last update Sun Nov  1 20:44:28 2015 louis giesen
*/

#include <string.h>
#include <stdlib.h>
#include "tron.h"

t_player	*init_moto(t_player *player)
{
  static int	nb = 1;

  player->moto.nb_player = nb;
  if (nb == 1)
    {
      player->moto.x = 200;
      player->moto.y = 200;
      player->moto.dir = BAS;
      player->moto.color = 0x00FF00;
    }
  else if (nb == 2)
    {
      player->moto.x = 800;
      player->moto.y = 200;
      player->moto.dir = GAUCHE;
      player->moto.color = 0x00FFFF;
    }
  else if (nb == 3)
    {
      player->moto.x = 200;
      player->moto.y = 600;
      player->moto.dir = DROITE;
      player->moto.color = 0xFFFF00;
    }
  else if (nb == 4)
    {
      player->moto.x = 800;
      player->moto.y = 600;
      player->moto.dir = HAUT;
      player->moto.color = 0xFF00FF;
    }
  nb++;
  return (player);
}

t_player	*init_keys(t_player *player, int left, int right)
{
  player->keys.right = right;
  player->keys.left = left;
  return (player);
}

t_player	*remove_player(t_player *player)
{
  t_player	*tmp = player;

  if (player == NULL)
    return (NULL);
  if (tmp->next == NULL)
    {
      free(player);
      return (NULL);
    }
  while (tmp && tmp->next && tmp->next->next)
    tmp = tmp->next;
  tmp->next = NULL;
  tmp = tmp->next;
  free(tmp);
  return (player);
}

t_player	*add_player(t_player *player, int left, int right, char *name)
{
  t_player	*node;
  t_player	*tmp;

  if (player == NULL)
    {
      if ((player = malloc(sizeof(t_player))) == NULL)
	return (NULL);
      if ((player->name = my_strdup(name)) == NULL)
	return (NULL);
      player = init_moto(player);
      player = init_keys(player, left, right);
      player->next = NULL;
      return (player);
    }
  tmp = player;
  if ((node = malloc(sizeof(*node))) == NULL)
    return (NULL);
  if ((node->name = my_strdup(name)) == NULL)
    return (NULL);
  node = init_moto(node);
  node = init_keys(node, left, right);
  while (tmp && tmp->next)
    tmp = tmp->next;
  tmp->next = node;
  node->next = NULL;
  return (player);
}
