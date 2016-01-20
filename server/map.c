/*
** map.c for tronc in /home/danjou_a/test/reseau/super_tron/server
**
** Made by Quentin Danjou
** Login   <danjou_a@epitech.net>
**
** Started on  Mon Oct 26 17:00:47 2015 Quentin Danjou
** Last update Fri Oct 30 21:18:24 2015 louis giesen
*/

#include <pthread.h>
#include <stdlib.h>
#include "server.h"

extern t_game	tron;

int	move_player(char nm_player, char action)
{
  if (action == GAUCHE || action == DROITE)
    {
      tron.players[nm_player -1][2] = (action == GAUCHE)
	? ((tron.players[nm_player -1][2] == HAUT)
	   ? GAUCHE
	   : ((tron.players[nm_player -1][2] == BAS)
	      ? DROITE
	      : ((tron.players[nm_player -1][2] == GAUCHE)
		 ? BAS
		 : ((tron.players[nm_player -1][2] == DROITE)
		    ? HAUT
		    : -1))))
	: ((tron.players[nm_player -1][2] == HAUT)
	   ? DROITE
	   : ((tron.players[nm_player -1][2] == BAS)
	      ? GAUCHE
	      : ((tron.players[nm_player -1][2] == GAUCHE)
		 ? HAUT
		 : ((tron.players[nm_player -1][2] == DROITE)
		    ? BAS
		    : -1))));
    }
  if (tron.players[nm_player -1][2] == -1)
    return (1);
  if (tron.players[nm_player -1][2] == HAUT)
    tron.players[nm_player -1][1] -= 1;
  else if (tron.players[nm_player -1][2] == BAS)
    tron.players[nm_player -1][1] += 1;
  else if (tron.players[nm_player -1][2] == GAUCHE)
    tron.players[nm_player -1][0] -= 1;
  else
    tron.players[nm_player -1][0] += 1;
  return (0);
}

void	init_players(int nb_players)
{
  int	i = 0;

  while (i < nb_players)
    {
      /* position x */
      tron.players[i][0] = (WINX / (nb_players * nb_players)) * (i + 1);
      /* position y */
      tron.players[i][1] = (WINY / (nb_players * nb_players)) * (i + 1);
      /* direction */
      tron.players[i][2] = i % 4;
      ++i;
    }
}

char	**init_map()
{
  char	**new = NULL;

  if ((new = malloc(sizeof(char *) * WINY + 1)) == NULL)
    return (NULL);
  for (int i = 0; i < WINY; i++)
    {
      if ((new[i] = malloc(sizeof(char) * WINX + 1)) == NULL)
        return (NULL);
      for (int j = 0; j < WINX; j++)
        new[i][j] = 0;
      new[WINX] = '\0';
    }
  new[WINY] = NULL;
  return (new);
}

void	free_map(char **map)
{
  int	i = 0;

  while (i < WINY)
    {
      free(map[i]);
      ++i;
    }
  free(map);
}
