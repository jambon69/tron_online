/*
** game.c for torn in /home/louis/my_projects/super_tron/client
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Sat Nov 28 18:18:46 2015 louis giesen
** Last update Sat Nov 28 19:21:13 2015 louis giesen
*/

#include "tron.h"

int	draw_wall(t_coord *player)
{
  glBegin(GL_QUADS);
  glColor3ub(255, 0, 0);
  glVertex3d(player->x, player->y, player->z);
  glVertex3d(player->x, player->y, player->z + 100);
  glVertex3d(player->x, player->y + 50, player->z + 100);
  glVertex3d(player->x, player->y + 50, player->z);
  glEnd();
  if (player->dir == UP)
    player->z++;
  else if (player->dir == DOWN)
    player->z--;
  else if (player->dir == LEFT)
    player->x--;
  else if (player->dir == RIGHT)
    player->x++;
  return (SUCCESS);
}

int	draw_platform()
{
  glBegin(GL_QUADS);
  glColor3ub(255, 255, 255);
  glVertex3d(500, 500, 0);
  glVertex3d(500, -500, 0);
  glVertex3d(-500, -500, 0);
  glVertex3d(-500, 500, 0);
  glEnd();
  return (SUCCESS);
}

int	move(t_camera *camera, t_coord *player, int symbol)
{
  (void) camera;
  if (symbol == 0) {
    if (player->dir == UP)
      player->dir = LEFT;
    else if (player->dir == LEFT)
      player->dir = DOWN;
    else if (player->dir == DOWN)
      player->dir = RIGHT;
    else if (player->dir == RIGHT)
      player->dir = UP;
  } else {
    if (player->dir == UP)
      player->dir = RIGHT;
    else if (player->dir == RIGHT)
      player->dir = DOWN;
    else if (player->dir == DOWN)
      player->dir = LEFT;
    else if (player->dir == LEFT)
      player->dir = UP;
  }
  printf("moved\n");
  return (SUCCESS);
}

int	launch_the_game(t_opengl *opengl, t_camera *camera)
{
  int	i = 0;
  int	continuer = 1;
  t_coord	player = {0, 0, 0, 0, UP};
  static t_ptr_key	ptr[9] =
    {{SDLK_DOWN, &modif_cam_z}, {SDLK_UP, &modif_cam_z},
     {SDLK_LEFT, &modif_cam_x}, {SDLK_RIGHT, &modif_cam_x},
     {280, &modif_cam_y}, {281, &modif_cam_y},
     {Q, &move}, {D, &move},
     {0, NULL}};

  while (continuer == 1) {
    SDL_PollEvent(&opengl->event);
    SDL_Delay(10);
    if (opengl->event.type == SDL_QUIT)
      exit(SUCCESS);
    if (opengl->event.type == SDL_KEYDOWN) {
      i = 0;
      while (i < 11) {
	if (opengl->event.key.keysym.sym == ptr[i].keycode) {
	  if ((i % 2) == 0)
	    ptr[i].ptr_keycode(camera, &player, 0);
	  else if ((i % 2) == 1)
	    ptr[i].ptr_keycode(camera, &player, 1);
	}
	i = i + 1;
      }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera->x, camera->y, camera->z,
	      camera->eye_x, camera->eye_y, camera->eye_z, 0, 0, 1);
    draw_platform();
    draw_wall(&player);
    SDL_GL_SwapBuffers();
    glFlush();
  }
  return (SUCCESS);
}
