/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 09:44:23 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 17:28:18 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#define xstr(s) str(s)
#define str(s) #s
#include "../ft_printf.h"

// gcc test.c libftprintf.a -D TEST="xstr(%d\n), 4" -o test
// gcc tester.c libftprintf.a -D TEST="xstr(~%32%%salut~\n), NULL" -o test && ./test | cat -e

int main()
{
	int	ret;
	int	*p;

	p = (int*)malloc(sizeof(int));
	ret = ft_printf("mine: "TEST);
	printf("mine ret = %d\n", ret);
	printf("\n");
	ret = printf("vrai: "TEST);
	printf("real ret = %d\n", ret);
}
