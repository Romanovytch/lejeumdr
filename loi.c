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

static void	afficher_recap(int **tab, double *loi, double nb)
{
  double	total;
  int		i;

  printf("\nloi choisie :\t\t\tB(100, %.4f)\n", (float)nb / 10000);
  total = 0;
  for (i = 0 ; i < 7 ; i++)
    total += pow(tab[i][1] - loi[i], 2) / loi[i]; 
  printf("somme des carrés des écarts :\tX² = %.3f\n", total);
  printf("degrés de liberté :\t\tv = 5\n");
  printf("validité de l'ajustement :\t");
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

static void	coef_binomiale(int **tab, int *data)
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
  afficher_recap(tab, loi, nb);
  free(loi);
  free(coef);
}

void		appliquer_loi(int **tab, int *data)
{
  coef_binomiale(tab, data);
}
