/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/08 17:47:06 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

/*
Ecrire au fur et a mesure le texte puis les flags%_ puis text puis flags%_ ...
Traiter le %
done					: % : pour afficher un % si precede %

Recuperer les flags :
					: 0 : Suivi de la width : nombre en str donne le minimum de CARACTERES
						  à afficher. Si precision est donnée avec d (done), i, u, o, x, X le flag est ignoré
						  printf("%00d\n", 0);-> outputs '0' (done)
done					: - : Aligne a gauche dans la width
done						  Prioritaire sur le 0 si les deux flags sont présents

Recuperer la width :
done					: entier decimal : (si negatif passe en positif et met le flag a '-') nombre de caracteres a afficher
done						  ajoute des ' ' a gauche ou droite si '-' si trop grand
						  ne tronque pas les nombres originaux
					: * : largeur de champs ou precision ou les deux indiqué par *

recuperer la precision :
					: . : Suivi d'un nombre en str (ne peut pas etre negatif) donne le nombre minimum de CHIFFRES
						  a afficher pour d (done), i, o, u, x, X (si pas de chiffre precision a 0)
done						  nombre de char max a afficher pour s 
done						  printf("%.0d", 0);  -> no output
done						  printf("%.0d", 10); -> outputs 10
					: * : largeur de champs ou precision ou les deux indiqué par *

recuperer les types de conversion:

	TYPE LETTRES (Precision non specifiée : Minimum de nombres qui doivent apparaitre)
				 (Si precision donnée aligner sur la droite avec zero a gauche)
					: c : Int argument convertis en (unsigned char)
						  Si c = '\0' il faut forcer l'affichage du '\0'
					: s : Chaine de caractere sans le \0 en (char *)
					: p : Affiche en hexadecimal le pointeur void * casté en (unsigned long long)
 
	TYPE NOMBRES
					: d : int signed decimal (int)
					: i : integer signed decimal (int)
					: u : unsigned decimal (unsigned int)
					: x : unsigned hexadecimal (unsigned int)
					: X : unsigned hexadecimal en MAJUSCULE (unsigned int)
*/

typedef struct	s_params
{
	char		flag;
	int			width;
	int			precision;
	char		type;
}				t_params;

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

int ft_strlen_prec(char *src, int precision)
{
	int i;

	i = 0;
	while (src[i] && i < precision)
		i++;
	return (i);
}

void my_printf_str(va_list my_list, int precision, int width, char flag)
{
    char *src = va_arg(my_list, char *);
	int i;

	i = ft_strlen(src);
	while (flag != '-' && i < width)
	{
		write(1, " ", 1);
		i++;
	}
	if (precision != -1)
    	write(1, src, ft_strlen_prec(src, precision));
	else
		write(1, src, ft_strlen(src));
	while (flag == '-' && i < width)
	{
		write(1, " ", 1);
		i++;
	}
}

void my_printf_char(va_list my_list)
{
    char *c;
    
    c = malloc(sizeof(char) * 2);
    c[0] = (char)va_arg(my_list, int);
    c[1] = '\0';

    write(1, &c[0], 1);
}

void my_printf_nbr(va_list my_list, int precision, int width, char flag)
{
    int num = va_arg(my_list, int);
	int i;
	int nbr_len;

	nbr_len = ft_strlen(ft_itoa(num));
	i = nbr_len - 1;
//	printf("\nwidth dans printfnbr = %d, flag = %c, precision = %d", width, flag, precision);
	while (precision > 0 && ++i < precision)
		write (1, "0", 1);
	while (precision == -1 && flag == '0' && ++i < width)
		write (1, "0", 1);
	while (flag == 'a' && nbr_len < width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
	if (!(precision == 0 && num == 0))
    	ft_putnbr(num);
	while (flag == '-' && nbr_len < width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
}

int	ft_check_flags(const char *src, int i, t_params *par)
{
	if (src[i] == '0' || src[i] == '-')
	{
		par->flag = (src[i] == '0') && (src[i + 1] == '-') ? '-' : src[i];
		if ((src[i] == '0') && (src[i + 1] == '-'))
			i++;
		i++;
	}
	if (src[i] > '0' && src[i] <= '9')
		par->width = ft_atoi(&src[i]);
	if ((src[i] == '.' || src[i] == '*') && src[i + 1])
	{
		par->precision = ft_atoi(&src[i + 1]);
		i++;
		while (src[i] && (src[i] >= '0' && src[i] <= '9'))
			i++;
	}
	if ((par->flag != 'a') && src[i + 1] >= '0' && src[i + 1] <= '9')
	{
		par->width = ft_atoi(&src[i]);
		i++;
		while (src[i] && (src[i] >= '0' && src[i] <= '9'))
			i++;
	}
//	i++;
	//printf("par->width = %d,\n par->flag = %c,\n par->precision = %d\n", par->width, par->flag, par->precision);
	return (i);
}


// traiter tout ce qu'il y a apres le %, jusqua un des flags s, c, d, p etc...
void ft_printf(const char *src, ...)
{
    va_list my_list;
	t_params *par;
    int i;

    va_start(my_list, src);
    i = 0;
    while (src[i])
    {
		par = malloc(sizeof(t_params) * 1);
		par->precision = -1;
		par->width = -1;	
		par->flag = 'a';
        if (src[i] != 0 && i != 0 && src[i - 1] == '%')
        {
			i = ft_check_flags(src, i, par);
	//		printf("\npar->width = %d, par->flag = %c, par->precision = %d, index = %d, src[i] = %c\n", par->width, par->flag, par->precision, i, src[i]);
            if (src[i] == 'd')
                my_printf_nbr(my_list, par->precision, par->width, par->flag);
            if (src[i] == 's')
                my_printf_str(my_list, par->precision, par->width, par->flag);
            if (src[i] == 'c')
                my_printf_char(my_list);
            else if ((src[i] == '%' || (src[i] != 's' && src[i] != 'c' && src[i] != 'd')))
            {
                write(1, &src[i], 1);
				if (!(src[i] == '%'))
                	i++;
            }
        }
        else if (src[i] != '%')
            write(1, &src[i], 1);
        i++;
    }
	return ;
}

int main(int ac, char **argv)
{
    ft_printf("Mon printf : %s %s %.10d hello %% %.12s salut \n", "nani", "chaine 1 ", 1450, "chaine de caracteres");
       printf("The printf : %s %s %.10d hello %% %.12s salut \n", "nani", "chaine 1 ", 1450, "chaine de caracteres");
	
    return (0);
}
