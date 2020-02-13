#include "ft_printf.h"

int main ()
{
	int ret;
	int ret2;
	char *test;

	test = malloc(sizeof(char) * (5 + 1));
	free(test);
	test = NULL;

	printf("Variables testees : -45, 10 / -45, 10 / -45, 10 / -45, 10\n");
	ret =     printf("V *.0x[%*.0x] / *.0X[%*.0X] / 0.*x[%0.*x] / 0.*X[%0.*X]\n",
			-45, 10, -45, 10, -45, 10, -45, 10);
	ret2 = ft_printf("F *.0x[%*.0x] / *.0X[%*.0X] / 0.*x[%0.*x] / 0.*X[%0.*X]\n",
			-45, 10, -45, 10, -45, 10, -45, 10);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : -15, \"Renard\", -15, \"Panda\", \"Firefox\", \"Pelican\", \"KEK\"\n");
	ret =     printf("V .*s[%.*s] / *s[%*s] / 16s[%16s] / -12s[%-12s] / -2s[%-2s]\n",
			-15, "Renard", -15, "Panda", "Firefox", "Pelican", "KEK");
	ret2 = ft_printf("F .*s[%.*s] / *s[%*s] / 16s[%16s] / -12s[%-12s] / -2s[%-2s]\n",
			-15, "Renard", -15, "Panda", "Firefox", "Pelican", "KEK");
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : 10, -720496195, 10, -532517157\n");
	ret =     printf("V *.0d[%*.0d] / 0.*[%0.*d]\n",
			10, -720496195, 10, -532517157);
	ret2 = ft_printf("F *.0d[%*.0d] / 0.*[%0.*d]\n",
			10, -720496195, 10, -532517157);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : None\n");
	ret =     printf("V %%%%[%%] / %%.%%[%.%] / -24%%[%-54%] / 0.24%%[%0.24%] / -2%%[%-2%]\n");
	ret2 = ft_printf("F %%%%[%%] / %%.%%[%.%] / -24%%[%-54%] / 0.24%%[%0.24%] / -2%%[%-2%]\n");
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : -25, \"lol\"\n");
	ret =     printf("V %%*%%[%*%] / %%s[%s]\n", -25, "lol");
	ret2 = ft_printf("F %%*%%[%*%] / %%s[%s]\n", -25, "lol");
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : 0, 0, 0, -1, -1\n");
	ret =     printf("V -1.0i ->[%-1.0i] / -2.10i ->[%-2.10i] / -10.0i ->[%-10.0i] / -3.2i ->[%-3.2i] / -3.10i ->[%-3.10i]\n",
			0, 0, 0, -1, -1);
	ret2 = ft_printf("F -1.0i ->[%-1.0i] / -2.10i ->[%-2.10i] / -10.0i ->[%-10.0i] / -3.2i ->[%-3.2i] / -3.10i ->[%-3.10i]\n",
			0, 0, 0, -1, -1);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : '', 'Hello', 'Hello'\n");
	ret =     printf("V -1.0s ->[%-1.0s] / -5.0s ->[%-5.1s] / -6.2s ->[%-6.2s]\n", "", "Hello", "Hello");
	ret2 = ft_printf("F -1.0s ->[%-1.0s] / -5.0s ->[%-5.1s] / -6.2s ->[%-6.2s]\n", "", "Hello", "Hello");
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : 5, 5, 5\n");
	ret =     printf("V -2.0X ->[%-2.0X] / -2.0X ->[%-2.0X] / -2X ->[%-2X] / .0X ->[%.0X]\n", 5, 0, 5, 5);
	ret2 = ft_printf("F -2.0X ->[%-2.0X] / -2.0X ->[%-2.0X] / -2X ->[%-2X] / .0X ->[%.0X]\n", 5, 0, 5, 5);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : UINT_MAX, 0, UINT_MAX, UINT_MAX\n");
	ret =     printf("V -10.10X ->[%-10.10X] / -10.10X ->[%-10.10X] / -10X ->[%-10X] / .10X ->[%.10X]\n",
			UINT_MAX, 0, UINT_MAX, UINT_MAX);
	ret2 = ft_printf("F -10.10X ->[%-10.10X] / -10.10X ->[%-10.10X] / -10X ->[%-10X] / .10X ->[%.10X]\n",
			UINT_MAX, 0, UINT_MAX, UINT_MAX);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : 5, 5, 5\n");
	ret =     printf("V -5.7X ->[%-5.7X] / -5X ->[%-5X] / .7X ->[%.7X]\n", 5, 5, 5);
	ret2 = ft_printf("F -5.7X ->[%-5.7X] / -5X ->[%-5X] / .7X ->[%.7X]\n", 5, 5, 5);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : 10, 0 / -10, 0 / -10, 0 / -1, 1000\n");
	ret =     printf("V -*d ->[%-*d] / .*d ->[%.*d] / 0*d ->[%0*d] / -10.*d ->[%-10.*d]\n", 10, 0, -10, 0, -10, 0, -1, 1000);
	ret2 = ft_printf("F -*d ->[%-*d] / .*d ->[%.*d] / 0*d ->[%0*d] / -10.*d ->[%-10.*d]\n", 10, 0, -10, 0, -10, 0, -1, 1000);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : -5, 0, 0 / -5, 0, Hello / -5, -2, 8 / -5, 1, Hello\n");
	ret =     printf("V *.*d ->[%*.*d] / *.*s ->[%*.*s] / *.*d ->[%*.*d] / *.*s ->[%*.*s]\n",
			-5, 0, 0, -5, 0, "Hello", -5, -2, 8, -5, 1, "Hello");
	ret2 = ft_printf("F *.*d ->[%*.*d] / *.*s ->[%*.*s] / *.*d ->[%*.*d] / *.*s ->[%*.*s]\n",
			-5, 0, 0, -5, 0, "Hello", -5, -2, 8, -5, 1, "Hello");
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : 5 / 5 / 5 / 5 / 5\n");
	ret =     printf("V 5.x[%5.x] / 5.X[%5.X] / 5.u[%5.u] / 5.d[%5.d] / 5.i[%5.i]\n", 20, 20, 20, 20, 20);
	ret2 = ft_printf("F 5.x[%5.x] / 5.X[%5.X] / 5.u[%5.u] / 5.d[%5.d] / 5.i[%5.i]\n", 20, 20, 20, 20, 20);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : NULL / &ret / NULL / &ret / NULL / &ret\n");
	ret =     printf("V 5.p[%5.p] / 20.p[%20.p] / .p[%.p] / .p[%.p] / -15p[%-15p] / -15p[%-15p] / -15.p[%-15.p] / -15.p[%-15.p]\n",
			NULL, &ret, NULL, &ret, NULL, &ret, NULL, &ret);
	ret2 = ft_printf("F 5.p[%5.p] / 20.p[%20.p] / .p[%.p] / .p[%.p] / -15p[%-15p] / -15p[%-15p] / -15.p[%-15.p] / -15.p[%-15.p]\n",
			NULL, &ret, NULL, &ret, NULL, &ret, NULL, &ret);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : Avec une variable puis free puis rendu a NULL / NULL / &ret / NULL / &ret / NULL / &ret\n");
	ret =     printf("V 5.p[%5.p] / 20.p[%20.p] / .p[%.p] / -15p[%-15p] /  -15.p[%-15.p]\n",
					 &test, &test, &test, &test, &test);
	ret2 = ft_printf("F 5.p[%5.p] / 20.p[%20.p] / .p[%.p] / -15p[%-15p] /  -15.p[%-15.p]\n",
					 &test, &test, &test, &test, &test);
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

	printf("Variables testees : Rien\n");
	ret =     printf("V -10.10 ->[%-10.10%] / -10.10 -10.10 ->[%-10.10%%-10.10%] / 4%% ->[%%%%] / 6%% ->[%%%%%%]\n");
	ret2 = ft_printf("F -10.10 ->[%-10.10%] / -10.10 -10.10 ->[%-10.10%%-10.10%] / 4%% ->[%%%%] / 6%% ->[%%%%%%]\n");
	printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

    printf("Variables testees : -8473\n");
    ret =     printf("V 050.40d ->[%050.40d] / [.30d ->[%.30d] / [10.2d ->[%10.2d] / [010.2d ->[%010.2d] / [010d ->[%010d]\n",
    		-8473, -8473, -8473, -8473, -8473);
    ret2 = ft_printf("F 050.40d ->[%050.40d] / [.30d ->[%.30d] / [10.2d ->[%10.2d] / [010.2d ->[%010.2d] / [010d ->[%010d]\n",
    		-8473, -8473, -8473, -8473, -8473);
    printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

    printf("Variables testees : -10 / -88 / -1\n");
    ret =     printf("V 1.50d ->[%1.50d] // 010.5d ->[%010.5d] / -1.10d[%-1.10d]\n", -10, -88, -1);
    ret2 = ft_printf("F 1.50d ->[%1.50d] // 010.5d ->[%010.5d] / -1.10d[%-1.10d]\n", -10, -88, -1);
    printf("V=%i F=%i  ", ret, ret2);
	if (ret != ret2)
		printf("\033[1;31m%s\033[0m\n", "KO");
	else
		printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

    printf("Variables testees : -3, -3, coucou / -10, -10, coucou\n");
    ret =     printf("V -*.*s[%-*.*s] / *.*s[%*.*s]\n", -3, -3, "coucou", -10, -10, "coucou");
    ret2 = ft_printf("F -*.*s[%-*.*s] / *.*s[%*.*s]\n", -3, -3, "coucou", -10, -10, "coucou");
    printf("V=%i F=%i  ", ret, ret2);
    if (ret != ret2)
        printf("\033[1;31m%s\033[0m\n", "KO");
    else
        printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

    printf("Variables testees : -3, -3, 8 / -10, -10, 8\n");
    ret =     printf("V -*.*d[%-*.*d] / *.*s[%*.*d]\n", -3, -3, 8, -10, -10, 8);
    ret2 = ft_printf("F -*.*d[%-*.*d] / *.*s[%*.*d]\n", -3, -3, 8, -10, -10, 8);
    printf("V=%i F=%i  ", ret, ret2);
    if (ret != ret2)
        printf("\033[1;31m%s\033[0m\n", "KO");
    else
        printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

    printf("Variables testees : None \n");
    ret =     printf("V -00-02%%[%-00-02%] / 00-02%%[%00-02%] / -12[%-12%] / -012%%[%-012%]\n");
    ret2 = ft_printf("F -00-02%%[%-00-02%] / 00-02%%[%00-02%] / -12[%-12%] / -012%%[%-012%]\n");
    printf("V=%i F=%i  ", ret, ret2);
    if (ret != ret2)
        printf("\033[1;31m%s\033[0m\n", "KO");
    else
        printf("\033[1;32m%s\033[0m\n", "OK");
	printf("\033[1;32m###########################################################################\033[0m\n");

    printf("FIN\n");
    return (0);
}
