/*
** main.c for tro in /home/louis/my_projects/super_tron/client
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Sat Nov 28 18:04:18 2015 louis giesen
** Last update Sat Nov 28 19:00:28 2015 louis giesen
*/

#include "tron.h"

int	init_opengl(t_opengl *opengl, t_camera *camera)
{
  if ((opengl->ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL)) == NULL)
    return (FAIL);
  SDL_WM_SetCaption("TRON !", NULL);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,
		    MIX_DEFAULT_CHANNELS, 1024) == -1)
    return (FAIL);
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    return (FAIL);
  SDL_Flip(opengl->ecran);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(35, (double)WIDTH/HEIGHT, 1, 1000);
  glEnable(GL_DEPTH_TEST);
  camera->x = 0.0;
  camera->y = -400.0;
  camera->z = 200.0;
  camera->eye_x = 0.0;
  camera->eye_y = 0.0;
  camera->eye_z = 0.0;
  SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
  return (SUCCESS);
}

int		main(int ac, char **av)
{
  t_opengl	opengl;
  t_camera	camera;

  (void) ac;
  (void) av;
  if (init_opengl(&opengl, &camera) == FAIL)
    return (EXIT_FAILURE);
  while (42)
    {
      /* launch_menu && connectToServer*/
      launch_the_game(&opengl, &camera);
    }
  return (EXIT_SUCCESS);
}
