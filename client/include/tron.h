/*
** tron.h for tron in /home/louis/my_projects/super_tron/client
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Sat Nov 28 18:04:44 2015 louis giesen
** Last update Sat Nov 28 19:13:41 2015 louis giesen
*/

#ifndef TRON_H_
# define TRON_H_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_mixer.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <stdio.h>
# include <stdlib.h>

# define FAIL -1
# define SUCCESS 0

# define HEIGHT 720
# define WIDTH 1280
# define Z 122
# define Q 113
# define S 115
# define D 100
# define ENTER 13
# define BACKSPACE 8

enum {LEFT, RIGHT, UP, DOWN};

typedef struct	s_coord
{
  double	x;
  double	y;
  double	z;
  double	size;
  int		dir;
}		t_coord;

typedef struct	s_camera
{
  double	x;
  double	y;
  double	z;
  double	eye_x;
  double	eye_y;
  double	eye_z;
}		t_camera;

typedef struct	s_ptr_key
{
  unsigned int	keycode;
  void		(*ptr_keycode)(t_camera *camera, t_coord *player, int symbol);
}		t_ptr_key;

typedef struct	s_opengl
{
  SDL_Surface	*ecran;
  SDL_Event	event;
}		t_opengl;

/*
** game on
*/
int	launch_the_game(t_opengl *opengl, t_camera *camera);

/*
** pov
*/
void	modif_cam_z(t_camera *camera, t_coord *player, int symbol);
void	modif_cam_y(t_camera *camera, t_coord *player, int symbol);
void	modif_cam_x(t_camera *camera, t_coord *player, int symbol);

#endif /* !TRON_H_ */
