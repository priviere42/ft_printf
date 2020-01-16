/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 13:29:23 by priviere    ###    #+. /#+    ###.fr     */
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
done				: c : Int argument convertis en (unsigned char)
done						  Si c = '\0' il faut forcer l'affichage du '\0'
done					: s : Chaine de caractere sans le \0 en (char *)
					: p : Affiche en hexadecimal le pointeur void * casté en (unsigned long long)

	TYPE NOMBRES
done					: d : int signed decimal (int)
done					: i : integer signed decimal (int)
done					: u : unsigned decimal (unsigned int)
done					: x : unsigned hexadecimal (unsigned int)
done					: X : unsigned hexadecimal en MAJUSCULE (unsigned int)
*/

// gerer 'p'
// ajouter compteur
// faire un bon makefile
// faire passer des tests

void my_printf_str(va_list my_list, t_params *par)
{
    char *src = va_arg(my_list, char *);
	int i;

	i = ft_strlen(src);
	while (par->flag != '-' && i < par->width)
	{
		write(1, " ", 1);
		i++;
	}
	if (par->precision != -1)
    	write(1, src, ft_strlen_prec(src, par->precision));
	else
		write(1, src, ft_strlen(src));
	while (par->flag == '-' && i < par->width)
	{
		write(1, " ", 1);
		i++;
	}
}

void my_printf_char(va_list my_list, t_params *par)
{
    unsigned char *c;
    int i;

	i = 1;
	while (par->flag != '-' && i < par->width)
	{
		write(1, " ", 1);
		i++;
	}
    c = malloc(sizeof(unsigned char) * 2);
    c[0] = (unsigned char)va_arg(my_list, int);
    c[1] = '\0';

    write(1, &c[0], 1);
}

void my_printf_unbr(va_list my_list, t_params *par)
{
    int num = va_arg(my_list, int);
	int i;
	int nbr_len;

	nbr_len = ft_strlen(ft_itoa_base(num, 10));
	i = nbr_len - 1;
//	if (par->precision > 0 && par->width != -1)    // these lines are getting a problem
//		par->flag = 'a';
//	printf("\nwidth dans printfnbr = %d, flag = %c, precision = %d\n", par->width, par->flag, par->precision);
	// if (par->precision >= 0 && par->width > 0 && par->width > par->precision)
	// {
	// 	while (par->flag != '-' && nbr_len < (par->width - par->precision))
	// 	{
	// 	//	write(1, "YOYO\n", 5);
	// 		write(1, " ", 1);
	// 		nbr_len++;
	// 	}
	// }
	// else
	{
		while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
		{
		//	write(1, "YOYO\n", 5);
			write(1, " ", 1);
			nbr_len++;
		}
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ft_putunbr(num);
	while (par->flag == '-' && nbr_len < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
}

void my_printf_nbr(va_list my_list, t_params *par)
{
    int num = va_arg(my_list, int);
	int i;
	int nbr_len;

	nbr_len = ft_strlen(ft_itoa_base(num, 10));
	i = nbr_len - 1;
//	if (par->precision > 0 && par->width != -1)    // these lines are getting a problem
//		par->flag = 'a';
//	printf("\nwidth dans printfnbr = %d, flag = %c, precision = %d\n", par->width, par->flag, par->precision);
	// if (par->precision >= 0 && par->width > 0 && par->width > par->precision)
	// {
	// 	while (par->flag != '-' && nbr_len < (par->width - par->precision))
	// 	{
	// 	//	write(1, "YOYO\n", 5);
	// 		write(1, " ", 1);
	// 		nbr_len++;
	// 	}
	// }
	// else
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	ft_putnbr(num);
	while (par->flag == '-' && nbr_len < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
}

void	my_printf_hexa(va_list my_list, t_params *par)
{
    int num = va_arg(my_list, int);
	int i;
	int nbr_len;

	nbr_len = ft_strlen(ft_itoa_base(num, 16));
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	write(1, ft_itoa_base(num, 16), ft_strlen(ft_itoa_base_maj(num, 16)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
}

void	my_printf_majhexa(va_list my_list, t_params *par)
{
    int num = va_arg(my_list, int);
	int i;
	int nbr_len;

	nbr_len = ft_strlen(ft_itoa_base_maj(num, 16));
	i = nbr_len - 1;
	while (par->flag == 'a' && nbr_len < par->width && par->precision < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	write(1, ft_itoa_base_maj(num, 16), ft_strlen(ft_itoa_base_maj(num, 16)));
	while (par->flag == '-' && nbr_len < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
}

void	my_printf_p(va_list my_list, t_params *par)
{
    unsigned long long num = va_arg(my_list, unsigned long long);
	int i;
	int nbr_len;

	nbr_len = ft_strlen(ft_ulltoa_base(num, 16));
	i = nbr_len - 1;
	printf("\npar->width = %d, par->flag = %c, par->precision = %d, nbr_len - 1 = %i\n", par->width, par->flag, par->precision, i);
	while (par->flag == 'a' && nbr_len + 3 < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
	write(1, "0x1", 3);
	while (par->precision > 0 && ++i < par->precision && par->flag != '-')
		write (1, "0", 1);
	while (par->precision == -1 && par->flag == '0' && ++i < par->width)
		write (1, "0", 1);
	if (!(par->precision == 0 && num == 0))
    	write(1, ft_ulltoa_base(num, 16), ft_strlen(ft_ulltoa_base(num, 16)));
	while (par->flag == '-' && nbr_len + 3 < par->width)
	{
		write(1, " ", 1);
		nbr_len++;
	}
}

int 	ft_check_wildcard(va_list my_list, const char *src, int i, t_params *par)
{
	int num;
	
	if (src[i] == '*')
	{
		if ((num = va_arg(my_list, int)) < 0)
		{
			par->width = -1 * num;
			par->flag = '-';
		}
		else
			par->width = num;
		i++;
	}
	if (src[i] == '.' && src[i + 1] == '*')
	{
		par->precision = va_arg(my_list, int);
		if (par->precision < 0)
		{
			par->precision = -1 * par->precision;
			if (par->width == -1)
				par->flag = '-';
		}
		i = i + 2;
	}
	return (i);
}

int	ft_check_flags(va_list my_list, const char *src, int i, t_params *par)
{
	if (src[i] == '0' || src[i] == '-')
	{
		par->flag = (src[i] == '0') && (src[i + 1] == '-') ? '-' : src[i];
		if (((src[i] == '0') && (src[i + 1] == '-'))
		|| ((src[i] == '-') && (src[i + 1] == '0')))
			i++;
		i++;
	}
	if (src[i] >= '0' && src[i] <= '9')
	{	
		par->width = ft_atoi(&src[i]);
		while (src[i] && (src[i] >= '0' && src[i] <= '9'))
			i++;
	}
	i = ft_check_wildcard(my_list, src, i, par);
	if ((src[i] == '.' && src[i + 1]))
		par->precision = ft_atoi(&src[++i]);
	if ((par->flag != 'a') && src[i + 1] >= '0' && src[i + 1] <= '9' && par->precision == -1)
		par->width = ft_atoi(&src[i++]);
	while (src[i] && (src[i] >= '0' && src[i] <= '9'))
		i++;
//	printf("\npar->width = %d, par->flag = %c, par->precision = %d, index = %i\n", par->width, par->flag, par->precision, i);
	return (i);
}

t_params	*ft_init_par(t_params *par)
{
	par = malloc(sizeof(t_params) * 1);
	par->precision = -1;
	par->width = -1;
	par->flag = 'a';
	return (par);
}

// int ft_find_index(char *tab, char element)
// {
// 	int i;

// 	i = 0;
// 	while (tab[i] != 0)
// 	{
// 		if (tab[i] == element)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }	

// traiter tout ce qu'il y a apres le %, jusqua un des flags s, c, d, p etc...
void ft_printf(const char *src, ...)
{
    va_list my_list;
	t_params *par;
	// void (*tabFunction[3]) (va_list *) = {my_printf_str, my_printf_char, my_printf_nbr};
	// char tabIndex[4] = {'s', 'c', 'd', 0};
	// int tmp;
    int i;

    va_start(my_list, src);
    i = 0;
	// tmp = 0;
    while (src[i])
    {
		par = ft_init_par(par);
        if (src[i] != 0 && i != 0 && src[i - 1] == '%')
        {
			i = ft_check_flags(my_list, src, i, par);
			// tmp = ft_find_index(tabIndex, src[i]);
			// if (tmp != -1)
			// 	(*tabFunction[tmp]) (&my_list);
	//		printf("\npar->width = %d, par->flag = %c, par->precision = %d, index = %d, src[i] = %c\n", par->width, par->flag, par->precision, i, src[i]);
            if (src[i] == 'd' || src[i] == 'i')
                my_printf_nbr(my_list, par);
            if (src[i] == 's')
                my_printf_str(my_list, par);
            if (src[i] == 'c')
                my_printf_char(my_list, par);
			if (src[i] == 'u')
				my_printf_unbr(my_list, par);
			if (src[i] == 'X')
				my_printf_majhexa(my_list, par);
			if (src[i] == 'x')
				my_printf_hexa(my_list, par);
			if (src[i] == 'p')
				my_printf_p(my_list, par);
            else if ((src[i] == '%' ||
			(src[i] != 's' && src[i] != 'c' && src[i] != 'd' && src[i] != 'i' && src[i] != 'u' && src[i] != 'x' && src[i] != 'X')))
            {
                write(1, &src[i], 1);
				if (!(src[i] == '%'))
                	i++;
            }
        }
        else if (src[i] != '%')
            write(1, &src[i], 1);
        i++;
		free(par);
    }
	return ;
}

int main()
{
	char* tutu = "sa";

    ft_printf("Mon printf : %*p\n", 20, tutu);
       printf("The printf : %*p\n", 20, tutu);
	
    return (0);
}
