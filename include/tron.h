/*
** tron.h for tron in /home/louis/my_projects/games/tron
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Sun Oct 25 14:47:01 2015 louis giesen
** Last update Fri Oct 30 21:12:16 2015 louis giesen
*/

#ifndef TRON_H_
# define TRON_H_

# define WINX 1280
# define WINY 720
# define LEFT 276
# define RIGHT 275
# define UP 273
# define DOWN 274
# define ESC 27
# define DEAD -1

# include <SDL/SDL.h>
# include <SDL/SDL_mixer.h>
# include <SDL/SDL_image.h>
# include <sys/socket.h>
# include <sys/types.h>


enum {PLAYER1 = 1, PLAYER2, PLAYER3, PLAYER4};
enum {CONTINUE, LOST};
enum {HAUT, BAS, GAUCHE, DROITE}; /* DOIT RESTER UNE ENUM DE 0 A 3 */
enum {LOCAL, ONLINE};

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

/*
** petite structure de coordonnées
*/
typedef struct	s_struct
{
  int		x;
  int		y;
  int		z;
}		t_struct;

typedef struct	s_menu
{
  SDL_Surface	*menu;
  SDL_Surface	*menu_local;
  SDL_Surface	*menu_connect;
  SDL_Surface	*menu_connect_push;
  SDL_Surface	*wait_others;
  SDL_Rect	pos_menu;
  int		mouse_x;
  int		mouse_y;
}		t_menu;

/*
** cette structure n'est utilse
** que pour le tracage de droites
*/
typedef struct	s_coord
{
  t_struct	point1;
  t_struct	point2;
  t_struct	super_point;
  t_struct	diff;
  t_struct	inc;
  t_struct	super_inc;
  t_struct	point;
  t_struct	point3;
  t_struct	save;
  t_struct	point_fuite;
}		t_coord;

typedef struct	s_keys
{
  int		up;
  int		left;
  int		down;
  int		right;
}		t_keys;

typedef struct	s_moto
{
  int		nb_player;
  SDL_Surface	*moto;
  int		x;
  int		y;
  int		dir;
  Uint32	color;
}		t_moto;

typedef struct	s_player
{
  t_keys	keys;
  t_moto	moto;
  char		*name;
  int		dead;
  struct s_player	*next;
}		t_player;

typedef struct	s_sdl
{
  SDL_Surface	*ecran;
  SDL_Surface	*void_screen;
  SDL_Event	event;
  SDL_Rect	pos_null;
  Uint32	color;
}		t_sdl;

typedef struct	s_ptr
{
  t_sdl		sdl;
  t_menu	menu;
  t_moto	moto;
  t_player	*player;
}		t_ptr;

/*
** add_player
*/
t_player	*add_player(t_player *player, int left, int right, char *name);
t_player	*remove_player(t_player *player);

/*
** map
*/
char	**init_map();

/*
** aff_droite
*/
int	affiche_droite(t_sdl *ptr, t_coord *point);
void	sdl_putpixel(SDL_Surface *surface, int x,
		     int y, unsigned long pixel);

/*
** events
*/
int	various_events(t_ptr *ptr, int sock);
int	local_events(t_ptr *ptr);

/*
** menu
*/
int	menu(t_ptr *ptr);
char	*my_strdup(char *str);

#endif /* !TRON_H_ */
