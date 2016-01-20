/*
** server.h for tron in /home/danjou_a/test/reseau/super_tron/include
**
** Made by Quentin Danjou
** Login   <danjou_a@epitech.net>
**
** Started on  Mon Oct 26 23:21:36 2015 Quentin Danjou
** Last update Wed Oct 28 11:39:27 2015 louis giesen
*/

#ifndef SERVER_H_
# define SERVER_H_

# define DEAD (-1)

typedef struct		s_game
{
  char			**map; /* la map */
  pthread_mutex_t	lock; /* mutex */
  int			players[10][3]; /* [nb joueurs] [x, y, dir] */
}			t_game;

typedef struct	s_sock
{
  int		socks[10];
  int		pos;
}		t_sock;


enum {PLAYER1 = 1, PLAYER2, PLAYER3, PLAYER4};
enum {CONTINUE, LOST};
enum {HAUT, BAS, GAUCHE, DROITE}; /* DOIT RESTER UNE ENUM DE 0 A 3 */

# define WINX 1280
# define WINY 720
# define LEFT 276
# define RIGHT 275
# define UP 273
# define DOWN 274
# define ESC 27

/*
** map.c
*/
char	**init_map();
void	free_map(char **);
int	move_player(char nm_player, char action);
void	init_players();

#endif /* !SERVER_H_ */
