/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/18 09:41:57 by priviere     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 15:41:27 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *s, ...)
{
	va_list		my_list;
	t_params	*par;
	int			*ret;
	int			real_ret;

	if (!(ret = malloc(sizeof(int) * 2)))
		return (-1);
	ret[0] = 0;
	ret[1] = 0;
	va_start(my_list, s);
	while (s[ret[0]])
	{
		par = ft_init_par(par);
		ret = my_fct(par, my_list, s, ret);
		ret[0]++;
		free(par);
	}
	real_ret = ret[1];
	free(ret);
	return (real_ret);
}


// #include <limits.h>
// int main()
// {
//  //   char *tutu = "fast";
// 	int ret = 0;
// 	int ret_printf = 0;

//     ret =   	ft_printf("[%25%]\n");
// 	printf("Retour de mon printf :%d\n", ret);

//     ret_printf =  printf("[%25%]\n");
// 	printf("Retour du vrai printf :%d\n", ret_printf);


//     // ret = ft_printf("[%1.0d]\n", 10);
// 	// printf("Retour de mon printf :%d\n", ret);
//     // ret_printf = printf("[%1.0d]\n", 10);
// 	// printf("Retour du vrai printf :%d\n", ret_printf);
// 	return (0);
// }

// int main(void)
// {
//     int ret = 0, ret2 = 0;

//     ret = ft_printf("|%8.15d|\n", 42);
//     ret2 = dprintf(1, "|%8.15d|\n", 42);

//     if (ret != ret2)
//         dprintf(1, "ko in return\n");
//     return 0;
// }
