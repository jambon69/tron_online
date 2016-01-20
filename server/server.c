/*
** server.c for tron in /home/louis/my_projects/super_tron
**
** Made by louis giesen
** Login   <louis@epitech.net>
**
** Started on  Sun Oct 25 21:02:00 2015 louis giesen
** Last update Sun Nov  1 20:46:54 2015 louis giesen
*/

#define _GNU_SOURCE
#include <fcntl.h>
#include <SDL/SDL.h>
#include <strings.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include "server.h"

#define PORT 22000

t_game   tron;
static int	dead[] = {0, 0, 0, 0};

typedef struct	s_mut_sockets
{
  pthread_mutex_t	mutex;
}		t_mut_socks;

static t_mut_socks	mut_socks =
  {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
  };

static void	write_all_client(int *socks, int nm_player)
{
  int		buff[3];
  int		i = 1;

  buff[0] = nm_player;
  if (dead[nm_player - 1] == 1)
    return ;
  buff[1] = tron.players[nm_player - 1][0];
  buff[2] = tron.players[nm_player - 1][1];
  if (buff[2] > 0 && buff[2] < WINY
      && buff[1] > 0 && buff[1] < WINX
      && tron.map[buff[2]][buff[1]] == 0)
    tron.map[buff[2]][buff[1]] = buff[0];
  else
    dead[nm_player - 1] = 1;
  while (i < socks[0] + 1)
    {
      if (send(socks[i], buff, sizeof(*buff) * 3, 0) < 0)
	{
	  fprintf(stderr, "send failed\n");
	  return ;
	}
      i++;
    }
}

static int	read_client(int *socks, int sock, char buffer[])
{
  int		c;

  while ((c = recv(sock, buffer, sizeof(*buffer) * 2, 0)) > 0)
    {
      if (c != sizeof(*buffer) * 2)
	continue ;
      if (strncmp(buffer, "ST", 2) == 0)
	return (1);
      pthread_mutex_lock(&(tron.lock));
      if (move_player(buffer[0], buffer[1]) == 0)
	{
	  write_all_client(socks, buffer[0]);
	}
      pthread_mutex_unlock(&(tron.lock));
    }
  return (0);
}

int			*init_server(int *socks, int nb_players)
{
  int			fd_sock;
  struct sockaddr_in	sin = {0};
  struct sockaddr_in	csin = {0};
  int			csock;
  int			i = 1;

  if ((fd_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf("socket failed\n");
      return (NULL);
    }
  bzero(&sin, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = htons(INADDR_ANY);
  sin.sin_port = htons(PORT);
  if (bind(fd_sock, (struct sockaddr *) &sin, sizeof(sin)) == -1)
    {
      printf("bind failed\n");
      return (NULL);
    }
  if (listen(fd_sock, 5) == -1)
    {
      printf("listen failed\n");
      return (NULL);
    }
  printf("Waiting for client to connect...\n");
  while (i < nb_players + 1)
    {
      if ((socks[i] = accept4(fd_sock, (struct sockaddr *)NULL, NULL,
			      SOCK_NONBLOCK)) != -1)
	{
	  printf("A client just connected !\n");
	  i++;
	}
    }
  socks[i] = fd_sock;
  socks[0] = i - 1;
  printf("All clients connected, game ready to start\n");
  return (socks);
}

void	*thread_read(void *socks)
{
  char	buf[2];

  while (42)
    {
      buf[0] = 0;
      buf[1] = 0;
      if (read_client(((t_sock *)socks)->socks,
		      ((t_sock *)socks)->socks[((t_sock *)socks)->pos], buf) == 1)
	break ;
    }
  return (NULL);
}

int		launch_server(int *sock)
{
  char		buf[2];
  pthread_t	thread;
  pthread_t	thread2;
  pthread_t	thread3;
  t_sock	socks;
  t_sock	socks2;
  t_sock	socks3;
  int		i = -1;

  while (++i < sock[0] + 1)
    {
      socks.socks[i] = sock[i];
      socks2.socks[i] = sock[i];
      socks3.socks[i] = sock[i];
    }
  if (sock[0] >= 2)
    {
      socks.pos = 2;
      pthread_create(&thread, NULL, thread_read, (void *)&socks);
    }
  if (sock[0] >= 3)
    {
      socks2.pos = 3;
      pthread_create(&thread2, NULL, thread_read, (void *)&socks2);
    }
  if (sock[0] >= 4)
    {
      socks3.pos = 4;
      pthread_create(&thread3, NULL, thread_read, (void *)&socks3);
    }
  while (42)
    {
      buf[0] = 0;
      buf[1] = 0;
      if (read_client(sock, sock[1], buf) == 1)
	return (EXIT_SUCCESS);
    }
  return (EXIT_SUCCESS);
}

int	send_start_signals(int *socks, int len)
{
  int	i = 1;
  int	buffer[3];

  while (i < len + 1)
    {
      buffer[0] = i;
      buffer[1] = tron.players[i - 1][0];
      buffer[2] = tron.players[i - 1][1];
      if (send(socks[i], buffer, sizeof(int) * 3, 0) < 0)
	{
	  fprintf(stderr, "first send failed\n");
	  exit(EXIT_FAILURE);
	}
      i++;
    }
  return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
  int	*sock;
  int	nb_players;
  int	i;

  nb_players = (argc < 2 ? 2 : atoi(argv[1]));
  while (42)
    {
      if ((tron.map = init_map()) == NULL)
	return (EXIT_FAILURE);
      init_players(nb_players);
      if (pthread_mutex_init(&(tron.lock), NULL) != 0)
	{
	  fprintf(stderr, "mutex init failed\n");
	  return (EXIT_FAILURE);
	}
      if ((sock = malloc(sizeof(int) * nb_players + 2)) == NULL
	  || (sock = init_server(sock, nb_players)) == NULL)
	{
	  free_map(tron.map);
	  return (EXIT_FAILURE);
	}
      send_start_signals(sock, sock[0]);
      launch_server(sock);
      free_map(tron.map);
      i = 0;
      while (++i < sock[0] + 2)
	{
	  dead[i - 1] = 0;
	  close(sock[i]);
	}
      free(sock);
    }
  return (EXIT_SUCCESS);
}
