#include <stdlib.h>
#include <stdio.h>

static void	affichage(int **tab)
{
  int		i;
  int		j;

  i = 0;
  printf("x ");
  for (j = 0 ; j < 9 ; j++)
    {
      printf(" | ");
      if (tab[i][0] == 8)
	printf("%d+", j);
      else if (tab[i][0] > j)
	printf("%d-%d", j, tab[i][0]);
      else
	printf("%d  ", j);
      j = tab[i][0];
      ++i;
    }
  printf("\n");
}

static void	make_tab(int ***tab, int **data)
{
  int		i;
  int		j;
  int		k;
  int		nb;

  for (i = 0 ; i < 9 ; i++)
    for (j = 0 ; j < 2 ; j++)
      (*tab)[i][j] = 0;

  k = 0;
  i = 0;
  while (i < 9)
    {
      nb = 0;
      while (nb < 10 && i < 9)
	{
	  nb += (*data)[i];
	  ++i;
	}
      (*tab)[k][0] = i - 1;
      (*tab)[k][1] = nb;
      ++k;
    }
}

static void	free_tab(int ***tab)
{
  int		i;

  for (i = 0 ; i < 9 ; i++)
    free((*tab)[i]);
  free(*tab);
}

static void	parse(int ***tab, int **data, char **av)
{
  int		i;
  int		nb;

  *data = (int *)malloc(sizeof(int) * 9);
  *tab = (int **)malloc(sizeof(int *) * 9);
  for (i = 0 ; i < 9 ; i++)
    (*tab)[i] = (int *)malloc(sizeof(int) * 2);

  for (i = 1 ; i < 10 ; i++)
    (*data)[i - 1] = atoi(av[i]);
  make_tab(tab, data);
}

int	main(int argc, char **argv)
{
  int	*data;
  int	**tab;

  if (argc != 10)
    {
      printf("Utilisation : %s [a] [b] [c] [d] [e] [f] [g] [h] [i]\n", argv[0]);
      return (EXIT_FAILURE);
    }
  parse(&tab, &data, argv);
  //menu(data);
  affichage(tab);
  appliquer_loi(tab, data);
  free(data);
  free_tab(&tab);
  return (EXIT_SUCCESS);
}
