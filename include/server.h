/*
** server.h for tron in /home/danjou_a/test/reseau/super_tron/include
** 
** Made by Quentin Danjou
** Login   <danjou_a@epitech.net>
** 
** Started on  Mon Oct 26 23:21:36 2015 Quentin Danjou
** Last update Tue Oct 27 11:12:39 2015 Quentin Danjou
*/

#ifndef SERVER_H_
# define SERVER_H_

# define NB_PLAYERS (2) /* NE PAS METTRE 0 */
# define DEAD (-1)

typedef struct		s_game
{
  char			**map; /* la map */
  pthread_mutex_t	lock; /* mutex */
  int			players[NB_PLAYERS][3]; /* [nb joueurs] [x, y, dir] */
}			t_game;

/*
** map.c
*/
char	**init_map();
void	free_map(char **);

#endif /* !SERVER_H_ */
