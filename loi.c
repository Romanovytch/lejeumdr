#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double	fact(int nb)
{
    int		indice;
    double	factorielle = 1;

    if (nb == 0)
      return 1;  
    for (indice = nb ; indice > 0 ; indice--)
      factorielle = factorielle * indice;
    return (factorielle);
}

static void     afficher_tableau(int **tab, double *loi)
{
  int           i;
  int           j;

  i = 0;
  printf("Ox");
  for (j = 0 ; j < 9 ; j++)
    {
      printf(" | %d ", tab[i][1]);
      j = tab[i][0];
      ++i;
    }
  printf("\n");
  i = 0;
  printf("Tx");
  for (j = 0 ; j < 9 ; j++)
    {
      printf(" | %.1f", loi[i]);
      j = tab[i][0];
      ++i;
    }
  printf("\n");
}

static void	get_validity()
{
  char		*line;

  for (i = 0; i < validity i++)
    line = get_next_line(fd);
  
}

static void	afficher_recap(int **tab, double *loi, double nb, int classe)
{
  int		pourcent[] = {99, 90, 80, 70, 60, 50, 40, 30,
			      20, 10, 5, 2, 1};
  double	values[] = {0.55, 1.61, 2.34, 3.00, 3.66, 4.35, 5.13, 
			    6.06, 7.29, 9.24, 11.07, 11.67, 13.28};
  double	total;
  int		i;

  printf("\nloi choisie :\t\t\tB(100, %.4f)\n", (float)nb / 10000);
  total = 0;
  for (i = 0 ; i < classe ; i++)
    {
      total += pow(tab[i][1] - loi[i], 2) / loi[i];
      printf("%f %d %f\n", total, tab[i][1], loi[i]);
    }
  printf("somme des carrés des écarts :\tX² = %.3f\n", total);
  printf("degrés de liberté :\t\tv = %d\n", classe - 2);
  printf("validité de l'ajustement :\t");
  for (i = 0 ; i < 13 ; i++)
    {
      if (values[i] > total)
	{
	  printf("%d%% < P < %d%%\n", pourcent[i], pourcent[i - 1]);
	  return ;
	}
    }
  printf("P < 1%%\n");
}

static void	loi_binomiale(double **loi, double *coef, int *data)
{
  double	total;
  double	res;
  int		nb;
  int		i;
  int		k;

  i = 0;
  k = 0;
  while (i < 9)
    {
      nb = 0;
      res = 0;
      while (nb < 10 && i < 9)
        {
          nb += data[i];
	  res += coef[i];
          ++i;
        }
      if (i == 9)
	(*loi)[k] = 100.0f - total;
      else
	{
	  total += res;
	  (*loi)[k] = res;
	}
      ++k;
    }
}

static void	coef_binomiale(int **tab, int *data, int classe)
{
  double	*coef;
  double	*loi;
  double	res;
  int		k;
  int		nb;
  int		i;

  nb = 0;
  for (i = 0 ; i < 9 ; i++)
    nb += i * data[i];
  coef = (double *)malloc(sizeof(double) * 9);
  loi = (double *)malloc(sizeof(double) * 9);
  for (i = 0 ; i < 9 ; i++)
    {
      if (i == 8)
	{
	  coef[i] = 100;
	  for (k = 0 ; k < 8 ; k++)
	    coef[i] -= coef[k];
	}
      else
	coef[i] = 100 * (fact(100) / (fact(i) * fact(100 - i))) * 
	  pow(((float)nb/10000), i) * pow(1 - ((float)nb/10000), 100 - i);
    }
  loi_binomiale(&loi, coef, data);
  afficher_tableau(tab, loi);
  afficher_recap(tab, loi, nb, classe);
  free(loi);
  free(coef);
}

void		appliquer_loi(int **tab, int *data, int classe)
{
  coef_binomiale(tab, data, classe);
}
