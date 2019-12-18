/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/18 13:49:13 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
Ecrire au fur et a mesur le texte puis les flags%_ puis text puis flags%_ ...
Traiter le %
					: % : pour afficher un % si precede %

Recuperer les flags :
					: 0 : Suivi de la width : nombre en str donne le minimum de CHARACTERE
						  à afficher. Si precision est donnée avec d, i, u, o, x, X le flag est ignoré
						  printf("%00d\n", 0);-> outputs '0'
					: - : Aligne a gauche dans la width
						  Prioritaire sur le 0 si les deux flags sont présents

Recuperer la width :
					: entier decimal : (si negatif passe en positif et met le flag a '-') nombre de characteres a afficher
						  ajoute des ' ' a gauche ou droit si '-' si trop grand
						  ne tronque pas les nombres originaux
					: * : largeur de champs ou precision ou les deux indiqué par *

recuperer la precision :
					: . : Suivi d'un nombre en str (ne peux pas etre negatif) donne le nombre minimum de CHIFFRES
						  a afficher pour d, i, o, u, x, X (si pas de chiffre precision a 0)
						  nombre de char max a afficher pour s 
						  printf("%.0d", 0);  -> no output
						  printf("%.0d", 10); -> outputs 10
					: * : largeur de champs ou precision ou les deux indiqué par *
					
recuperer les types de conversion:

	TYPE LETTRES (Precision non specifié : Minimum de nombres qui doivent apparaitre)
				 (Si precision donnée aligner sur la droite avec zero a gauche)
					: c : Int argument convertis en (unsigned char)
						  Si c = '\0' il faut forcer l'affichage du '\0'
					: s : Chaine de charactere sans le \0 en (char *)
					: p : Affiche en hexadecimal le pointeur void * caster en (unsigned long long)
                    
	TYPE NOMBRES
					: d : int signed decimal (int)
					: i : integer signed decimal (int)
					: u : unsigned decimal (unsigned int)
					: x : unsigned hexadecimal (unsigned int)
					: X : unsigned hexadecimal en MAJUSCULE (unsigned int)
*/

void	ft_putnbr(int n)
{
	int mod;
	int div;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = n * -1;
		}
		if (n <= 9)
		{
			n = n + 48;
			write(1, &n, 1);
		}
		else
		{
			div = n / 10;
			mod = n % 10;
			ft_putnbr(div);
			ft_putnbr(mod);
		}
	}
}

void my_printf_str(va_list my_list)
{
    char *src = va_arg(my_list, char *);
    
    write(1, src, strlen(src));
}

void my_printf_char(va_list my_list)
{
    char *c;
    
    c = malloc(sizeof(char) * 2);
    c[0] = (char)va_arg(my_list, int);
    c[1] = '\0';

    write(1, &c[0], 1);
}

void my_printf_nbr(va_list my_list)
{
    int num = va_arg(my_list, int);

    ft_putnbr(num);
}

void ft_printf(const char *src, ...)
{
    va_list my_list;
    int i;

    va_start(my_list, src);
    i = 0;
    while (src[i])
    {
        if (src[i] != 0 && i != 0 && src[i - 1] == '%')
        {
            if (src[i] == 'd')
                my_printf_nbr(my_list);
            if (src[i] == 's')
                my_printf_str(my_list);
            if (src[i] == 'c')
                my_printf_char(my_list);
        }
        else if (src[i] != '%')
            write(1, &src[i], 1);
        i++;
    }
}

int main(int ac, char **argv)
{
    ft_printf("%d", 145);
    return (0);
}