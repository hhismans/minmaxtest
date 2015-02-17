/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 00:44:58 by hhismans          #+#    #+#             */
/*   Updated: 2015/02/17 01:58:16 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#define VOID	0
#define PLAYERX	1
#define PLAYERO	2

void	drawgrid(int grid[][3]);
void	setgrid(int grid[][3]);

void	IA_jouer(int jeu[][3], int profondeur);
int gagnant(int jeu[][3]);
int min(int jeu[][3], int profondeur);
void nb_series(int jeu[][3],int* series_j1, int* series_j2, int n); //Compte le nombre de séries de n pions alignés de chacun des joueurs
int eval(int jeu[][3]);
int max(int jeu[][3], int profondeur);
/**
 * main de test minmax
 */

int main(void)
{
	int grid[3][3];
	char *input;

	setgrid(grid);
	drawgrid(grid);

	while (1)
	{
		get_next_line(0, &input);
		if (ft_isdigit(input[0]))
		{
			grid[(input[0] - '0') % 3][(input[0] - '0') / 3] = PLAYERX;
		}
		IA_jouer(grid, 50);
		if (gagnant(grid))
			ft_putstr("there is a winner !");
		drawgrid(grid);
	}
	return(0);
}

void	setgrid(int grid[][3])
{
	int i;
	int j;

	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			grid[i][j] = 0;
			i++;
		}
		j++;
	}
}
void	drawgrid(int grid[][3])
{
	int i;
	int j;

	j = 0;
	while (j < 3)
	{
		i = 0;
		while (i < 3)
		{
			if (grid[i][j] == VOID)
				ft_putchar('.');
			if (grid[i][j] == PLAYERX)
				ft_putchar('X');
			if (grid[i][j] == PLAYERO)
				ft_putchar('O');
			i++;
		}
		ft_putchar('\n');
		j++;
	}
}

void	IA_jouer(int jeu[][3], int profondeur)
{
	int max_ = -10000;
	int tmp, maxi, maxj;
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (jeu[i][j] == VOID)
			{
				jeu[i][j] = PLAYERO;
				tmp = min(jeu, profondeur - 1);

				if (tmp > max_)
				{
					max_ = tmp;
					maxi = i;
					maxj = j;
				}

				jeu[i][j] = VOID;
			}
		}
	}
		jeu[maxi][maxj] = PLAYERO;
}

int max(int jeu[][3], int profondeur)
{
	if (profondeur == 0 || gagnant(jeu))
	{
		return eval(jeu);
	}
	int max_ = -10000;
	int i,j,tmp;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (jeu[i][j] == VOID)
			{
				jeu[i][j] = PLAYERO;
				tmp = min(jeu, profondeur - 1);

				if (tmp > max_)
				{
					max_ = tmp;
				}
				jeu[i][j] = VOID;
			}
		}
	}
	return (max_);
}

int min(int jeu[][3], int profondeur)
{
	if (profondeur == 0 || gagnant(jeu))
	{
		return eval(jeu);
	}
	int min_ = 10000;
	int i,j,tmp;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (jeu[i][j] == VOID)
			{
				jeu[i][j] = PLAYERO;
				tmp = max(jeu, profondeur - 1);

				if (tmp < min_)
				{
					min_ = tmp;
				}
				jeu[i][j] = VOID;
			}
		}
	}
	return (min_);
}

void nb_series(int jeu[][3],int* series_j1, int* series_j2, int n) //Compte le nombre de séries de n pions alignés de chacun des joueurs
{ 
     int compteur1, compteur2, i, j;
     
     *series_j1 = 0;
     *series_j2 = 0;

     compteur1 = 0;
     compteur2 = 0;

      //Diagonale descendante
     for(i=0;i<3;i++)
     {
          if(jeu[i][i] == 1)
          {
               compteur1++;
               compteur2 = 0;

               if(compteur1 == n)
               {
                    (*series_j1)++;
               }
          }
          else if(jeu[i][i] == 2)
          {
               compteur2++;
               compteur1 = 0;
      
               if(compteur2 == n)
               {
                     (*series_j2)++;
               }
          }        
     }

     compteur1 = 0;
     compteur2 = 0;

     //Diagonale montante
     for(i=0;i<3;i++)
     {
          if(jeu[i][2-i] == 1)
          {
               compteur1++;
               compteur2 = 0;

               if(compteur1 == n)
               {
                    (*series_j1)++;
               }
          }
          else if(jeu[i][2-i] == 2)
          {
               compteur2++;
               compteur1 = 0;
      
               if(compteur2 == n)
               {
                     (*series_j2)++;
               }
          }        
     }

     //En ligne
     for(i=0;i<3;i++)
     {
          compteur1 = 0;
          compteur2 = 0;
        
          //Horizontalement
          for(j=0;j<3;j++)
          {
               if(jeu[i][j] == 1)
               {
                    compteur1++;
                    compteur2 = 0;

                    if(compteur1 == n)
                    {
                         (*series_j1)++;
                    }
               }
               else if(jeu[i][j] == 2)
               {
                    compteur2++;
                    compteur1 = 0;

                    if(compteur2 == n)
                    {
                         (*series_j2)++;
                    }
               }
          }

          compteur1 = 0;
          compteur2 = 0;

          //Verticalement
          for(j=0;j<3;j++)
          {
               if(jeu[j][i] == 1)
               {
                    compteur1++;
                    compteur2 = 0;

                    if(compteur1 == n)
                    {
                         (*series_j1)++;
                    }
               }
               else if(jeu[j][i] == 2)
               {
                    compteur2++;
                    compteur1 = 0;

                    if(compteur2 == n)
                    {
                         (*series_j2)++;
                    }
               }
          }
     }
}

int eval(int jeu[][3])
{
     int vainqueur,nb_de_pions = 0;
     int i,j;

     //On compte le nombre de pions présents sur le plateau
     for(i=0;i<3;i++)
     {
          for(j=0;j<3;j++)
          {
               if(jeu[i][j] != 0)
               {
                    nb_de_pions++;
               }
          }
     }

     if( (vainqueur = gagnant(jeu)) != 0)
     {
          if( vainqueur == 1 )
          {
               return 1000 - nb_de_pions;
          }
          else if( vainqueur == 2 )
          {
               return -1000 + nb_de_pions;
          }
          else
          {
               return 0;
          }
     }

     //On compte le nombre de séries de 2 pions alignés de chacun des joueurs
     int series_j1 = 0, series_j2 = 0;
     
     nb_series(jeu,&series_j1,&series_j2,2);

     return series_j1 - series_j2;
}

int gagnant(int jeu[][3])
{
     int i,j;
     int j1,j2;

     nb_series(jeu,&j1,&j2,3);
	printf("j1 = %d, j2 = %d\n", j1, j2);
     if(j1)
     {
          return 1;
     }
     else if(j2)
     {
          return 2;
     }
     else
     {
          //Si le jeu n'est pas fini et que personne n'a gagné, on renvoie 0
          for(i=0;i<3;i++)
          {
               for(j=0;j<3;j++)
               {
                    if(jeu[i][j] == 0)
                    {
                         return 0;
                    }
               }
          }
     }

     //Si le jeu est fini et que personne n'a gagné, on renvoie 3
     return 3;
}
