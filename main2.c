#include "ft_printf.h"

int		ft_printf(const char *, ...);
#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

typedef	struct		s_main
{
	int		count;
	int		count2;
}					t_main;

void	ft_return_val(int mine, int real, t_main *main)
{
	if (real == mine)
	{
		main->count++;
		main->count2++;
		printf("\033[1;32m%s\033[0m\n\n\n", "OK");
	}
	else
	{
		main->count2++;
		printf("\033[1;31m%s\033[0m\n\n\n", "KO");
	}
}

int	main()
{
	t_main	main[1];
	int		mine;
	int		real;
	//char	*str = "astek";
	char	stre[] = {'a', 's', 10, 'E', 'k', 0, 3, 123, -15, 15};

	main->count = 0;
	main->count2 = 0;
	mine = 0;
	real = 0;

/*
FIXED :

    printf("##### Tests [2.s] #####\n");
	real = printf("|%2.s|\n", "test");
	mine = ft_printf("|%2.s|\n", "test");
	ft_return_val(mine, real, main);
*/
    printf("##### Tests [10.d] : 0 #####\n");
	real = printf("|%10.d|\n", stre[5]);
	mine = ft_printf("|%10.d|\n", stre[5]);
	ft_return_val(mine, real, main);

    printf("##### Tests [*.d] : 10 0 #####\n");
	real = printf("|%*.d|\n", 10, stre[5]);
	mine = ft_printf("|%*.d|\n", 10, stre[5]);
	ft_return_val(mine, real, main);

    printf("##### Tests [10.u] : 0 #####\n");
	real = printf("|%10.u|\n", stre[5]);
	mine = ft_printf("|%10.u|\n", stre[5]);
	ft_return_val(mine, real, main);

    printf("##### Tests [*.u] : 10 0 #####\n");
	real = printf("|%*.u|\n", 10, stre[5]);
	mine = ft_printf("|%*.u|\n", 10, stre[5]);
	ft_return_val(mine, real, main);

	printf("##### Tests [0*.*u] : 5 -5 8 #####\n");
	real = printf("|%0*.*u|\n", 5, -5, 8);
	mine = ft_printf("|%0*.*u|\n", 5, -5, 8);
	ft_return_val(mine, real, main);

/*
NE COMPILE PAS NORMALEMENT :

	printf("##### Tests [00000-000002'percent'] #####\n");
	real = printf("|%00000-000002%|\n");
	mine = ft_printf("|%00000-000002%|\n");
	ft_return_val(mine, real, main);


	printf("##### Tests [--0--0--00-00-02.10'percent'] #####\n");
	real = printf("|%--0--0--00-00-02.10%|\n");
	mine = ft_printf("|%--0--0--00-00-02.10%|\n");
	ft_return_val(mine, real, main);
*/
    printf("Variables testees : None \n");
    real = printf("V -00-02%%[%-00-02%] / 00-02%%[%00-02%] / -12[%-12%] / -012%%[%-012%]\n");
    mine = ft_printf("F -00-02%%[%-00-02%] / 00-02%%[%00-02%] / -12[%-12%] / -012%%[%-012%]\n");
    printf("V=%i F=%i  ", real, mine);
    if (real != mine)
        printf("\033[1;31m%s\033[0m\n", "KO");
    else
        printf("\033[1;32m%s\033[0m\n", "OK");
    printf("###########################################################################\n");

    
    printf("Variables testees : -5, 0, 0 / -5, 0, Hello / -5, -2, 8 / -5, 1, Hello\n");
	real = printf("V *.*d ->[%*.*d] / *.*s ->[%*.*s] / *.*d ->[%*.*d] / *.*s ->[%*.*s]\n", -5, 0, 0, -5, 0, "Hello", -5, -2, 8, -5, 1, "Hello");
	mine = ft_printf("F *.*d ->[%*.*d] / *.*s ->[%*.*s] / *.*d ->[%*.*d] / *.*s ->[%*.*s]\n", -5, 0, 0, -5, 0, "Hello", -5, -2, 8, -5, 1, "Hello");
	printf("V=%i F=%i  ", real, mine);
	if (real != mine)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("###########################################################################\n");
    

}
