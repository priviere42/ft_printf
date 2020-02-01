/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe_test.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 14:02:58 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 17:20:27 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../ft_printf.h"

#define NUM 10

// TESTS STRINGS
#define TEST1 "%s~\n", "salut"
#define TEST2 "%5s~\n", "heyo"
#define TEST3 "%-7s~\n", "coucou"
#define TEST4 "%-s~\n", "piscine"
#define TEST5 "%8.4s~\n", "fatigue fatigue"
#define TEST6 "%s~\n", "cluster"
#define TEST7 "%s~\n", s
#define TEST8 "%9s~\n", s
#define TEST9 "%.s~\n", s
#define TEST10 "%-4.s~\n", "holahello"
#define TEST11 "%5.*s~\n", -3, "holahello"
#define TEST12 "%*.3s~\n", 7, "okok"
#define TEST13 "%*.*s~\n", 18, 4, "fatigue fatigue"
#define TEST14 "%*.*s~\n", -18, 4, "fatigue fatigue"
#define TEST15 "%salut~\n", "il pleut dehors"
#define TEST16 "%.s~\n", "pied de table"
#define TEST17 "%s%s%s~\n", "j'ai", "tres", "faim"
#define TEST18 "%s~\n", "oksalut"
#define TEST19 "%3sss~\n", "okok"
#define TEST20 "%.7*s~\n", 4, "0123456789"
#define TEST21 "%.**s~\n", 0, 4, "hajime"
#define TEST22 "%%s~\n"

// TESTS NUMS
#define TEST23 "%d~\n", INT_MAX + 1234
#define TEST24 "%u~\n", UINT_MAX + 1234
#define TEST25 "%i~\n", INT_MAX + 1234
#define TEST26 "%x~\n", UINT_MAX + 1234
#define TEST27 "%X~\n", UINT_MAX + 1234
#define TEST28 "%4.3d%09u%-8.6X%*.4x~\n", 43, 1234, 1214, 7, 321

#define TEST29 "%3d~\n", 2
#define TEST30 "%-3d~\n", 0
#define TEST31 "%03d~\n", 2
#define TEST32 "%0*d~\n", 3, 0
#define TEST33 "%*d~\n", -3, 0
#define TEST34 "%.d~\n", 0
#define TEST35 "%.1d~\n", 0
#define TEST36 "%4.d~\n", 0
#define TEST37 "%04.d~\n", 0
#define TEST38 "%-3.*d~\n", -4, 17
#define TEST39 "%*.*d~\n", 3, -4, 17
#define TEST40 "%.1d~\n", 2
#define TEST41 "%2.d~\n", 2
#define TEST42 "%-4.3d~\n", 47
#define TEST43 "%-4.4d~\n", 47
#define TEST44 "%-4.5d~\n", 47
#define TEST45 "%4.3d~\n", 47
#define TEST46 "%4.4d~\n", 47
#define TEST47 "%4.5d~\n", 47

#define TEST48 "%3u~\n", 2
#define TEST49 "%-3u~\n", 0
#define TEST50 "%03u~\n", 2
#define TEST51 "%0*u~\n", 3, 0
#define TEST52 "%*u~\n", -3, 0
#define TEST53 "%.u~\n", 0
#define TEST54 "%.1u~\n", 0
#define TEST55 "%4.u~\n", 0
#define TEST56 "%04.u~\n", 0
#define TEST57 "%-3.*u~\n", -4, 17
#define TEST58 "%*.*u~\n", 3, -4, 17
#define TEST59 "%.1u~\n", 2
#define TEST60 "%2.u~\n", 2
#define TEST61 "%-4.3u~\n", 47
#define TEST62 "%-4.4u~\n", 47
#define TEST63 "%-4.5u~\n", 47
#define TEST64 "%4.3u~\n", 47
#define TEST65 "%4.4u~\n", 47
#define TEST66 "%4.5u~\n", 47

#define TEST67 "%3x~\n", 2
#define TEST68 "%-3x~\n", 0
#define TEST69 "%03x~\n", 2
#define TEST70 "%0*x~\n", 3, 0
#define TEST71 "%*x~\n", -3, 0
#define TEST72 "%.x~\n", 0
#define TEST73 "%.1x~\n", 0
#define TEST74 "%4.x~\n", 0
#define TEST75 "%04.x~\n", 0
#define TEST76 "%-3.*x~\n", -4, 17
#define TEST77 "%*.*x~\n", 3, -4, 17
#define TEST78 "%.1x~\n", 2
#define TEST79 "%2.x~\n", 2
#define TEST80 "%-4.3x~\n", 47
#define TEST81 "%-4.4x~\n", 47
#define TEST82 "%-4.5x~\n", 47
#define TEST83 "%4.3x~\n", 47
#define TEST84 "%4.4x~\n", 47
#define TEST85 "%4.5x~\n", 47

#define TEST86 "%3X~\n", 2
#define TEST87 "%-3X~\n", 0
#define TEST88 "%03X~\n", 2
#define TEST89 "%0*X~\n", 3, 0
#define TEST90 "%*X~\n", -3, 0
#define TEST91 "%.X~\n", 0
#define TEST92 "%.1X~\n", 0
#define TEST93 "%4.X~\n", 0
#define TEST94 "%04.X~\n", 0
#define TEST95 "%-3.*X~\n", -4, 17
#define TEST96 "%*.*X~\n", 3, -4, 17
#define TEST97 "%.1X~\n", 2
#define TEST98 "%2.X~\n", 2
#define TEST99 "%-4.3X~\n", 47
#define TEST100 "%-4.4X~\n", 47
#define TEST101 "%-4.5X~\n", 47
#define TEST102 "%4.3X~\n", 47
#define TEST103 "%4.4X~\n", 47
#define TEST104 "%4.5X~\n", 47

// TESTS CHARS
#define TEST105 "%c~\n", 'a'
#define TEST106 "%.c~\n", 'U'
#define TEST107 "%%~\n"
#define TEST108 "%4c~\n", 'x'
#define TEST109 "%-4c~\n", 'P'
#define TEST110 "%c~\n", 0
#define TEST111 "%4.c~\n", 0
#define TEST112 "%c%c%c~\n", 'a', 'b', 'c'
#define TEST113 "%*c~\n", 3, 'J'
#define TEST114 "%3%25%%%c~\n", 'T'
#define TEST115 "%*%~\n", 3
#define TEST116 "%c%2c%3c%4c%5c~\n", 'a', 'b', 0, 'c', 'd'
#define TEST117 "%c%-2c%-3c%-4c%-5c~\n", 'a', 'b', 0, 'c', 'd'
#define TEST118 "%%-2%%4%%-3%%%%%%%%%%~\n"

// TESTS POINTERS
#define TEST119 "%p\n", p
#define TEST120 "%.p~\n", p
#define TEST121 "%.p~\n", n
#define TEST122 "%-4.p~\n", n
#define TEST123 "%7.3p~\n", n
#define TEST124 "%19.15p~\n", p
#define TEST125 "%12p~\n", n
#define TEST126 "%-12p~\n", n
#define TEST127 "%17p~\n", p
#define TEST128 "%-17p~\n", p
#define TEST129 "%11p~\n", p
#define TEST130 "%-11p~\n", p
#define TEST131 "%.18p~\n", p
#define TEST132 "%20.18p~\n", p
#define TEST133 "%-20.18p~\n", p
#define TEST134 "%8.17p~\n", p
#define TEST135 "%p%p%p~\n", p, n , NULL
#define TEST136 "%*.18p~\n", 20, p
#define TEST137 "%*.18p~\n", -20, p
#define TEST138 "%-*.p~\n", 4, n
#define TEST139 "%---23p~\n", p

// TESTS DE PORCS QUI VONT DEMOLIR TON PRINTF
#define TEST140 "%% %-18.p abcdef%% %000*.u %--x%*.7X %-7.3sss~\n", p, 12, -2010102, -1323, 9, 654, "heyhey"
#define TEST141 "salut %-19.15p|%-3.2i|%.03*x moi c'est %s~\n", p, 7, 6, 2345678, "luis"
#define TEST142 "%---4dd %uiu %*p..%xx%%x %XxX%12.7X,,%.c~\n", INT_MAX + 1, -1, -4, NULL, 2547, 756897, 145, 0
#define TEST143 "%5..p\t%6.3s%7.5s%6.8s~\n", NULL, NULL, "ceci est non nul", "debroussailleuse"
#define TEST144 "%.s%s%006X%--p%%%%~\n", "ichougra est une legende, ", "ichougra est un escroc", 1254, p
#define TEST145 "%.sps%5%w|%-7.d|**%*X%*x%*.5i~\n", "test", -87268, -7, -87452, 10, 1112111, -13, UINT_MAX + 789
#define TEST146 "~\n"
#define TEST147 "%~\n"
#define TEST148 "%2.p\t%21.19s%-4.7s%6.8s~\n", NULL, "le black hole approche", 0, "abcdefgh"
#define TEST149 "a%ca%ca%ca%ca%ca%ca%ca%ca~\n", 0, 0, 0, 0, 0, 0, 0, 0
#define TEST150 "test %s, plus d'%s~\n", "gentil", "inspi"

int main()
{
	int ret[2];
	int test = 1;
	char *n = NULL;
	char *p = (char*)malloc(sizeof(char));
	char *s = strdup("heyo heyo");
	

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST1);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST1);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST2);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST2);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST3);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST3);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST4);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST4);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST5);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST5);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST6);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST6);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST7);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST7);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST8);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST8);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST9);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST9);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST10);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST10);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST11);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST11);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST12);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST12);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST13);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST13);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST14);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST14);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST15);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST15);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST16);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST16);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST17);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST17);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST18);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST18);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST19);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST19);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST20);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST20);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST21);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST21);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST22);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST22);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST23);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST23);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST24);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST24);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST25);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST25);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST26);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST26);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST27);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST27);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST28);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST28);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST29);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST29);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST30);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST30);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST31);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST31);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST32);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST32);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST33);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST33);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST34);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST34);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST35);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST35);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST36);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST36);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST37);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST37);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST38);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST38);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST39);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST39);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST40);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST40);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST41);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST41);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST42);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST42);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST43);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST43);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST44);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST44);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST45);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST45);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST46);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST46);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST47);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST47);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST48);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST48);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST49);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST49);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST50);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST50);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST51);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST51);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST52);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST52);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST53);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST53);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST54);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST54);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST55);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST55);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST56);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST56);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST57);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST57);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST58);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST58);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST59);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST59);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST60);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST60);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST61);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST61);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST62);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST62);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST63);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST63);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST64);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST64);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST65);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST65);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST66);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST66);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST67);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST67);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST68);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST68);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST69);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST69);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST70);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST70);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST71);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST71);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST72);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST72);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST73);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST73);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST74);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST74);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST75);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST75);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST76);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST76);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST77);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST77);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST78);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST78);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST79);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST79);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST80);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST80);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST81);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST81);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST82);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST82);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST83);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST83);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST84);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST84);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST85);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST85);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST86);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST86);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST87);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST87);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST88);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST88);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST89);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST89);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST90);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST90);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST91);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST91);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST92);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST92);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST93);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST93);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST94);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST94);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST95);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST95);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST96);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST96);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST97);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST97);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST98);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST98);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST99);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST99);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST100);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST100);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST101);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST101);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST102);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST102);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST103);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST103);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST104);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST104);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST105);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST105);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST106);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST106);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST107);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST107);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST108);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST108);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST109);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST109);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST110);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST110);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST111);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST111);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST112);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST112);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST113);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST113);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST114);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST114);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST115);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST115);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST116);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST116);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST117);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST117);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST118);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST118);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST119);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST119);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST120);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST120);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST121);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST121);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST122);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST122);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST123);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST123);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST124);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST124);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST125);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST125);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST126);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST126);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST127);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST127);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST128);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST128);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST129);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST129);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST130);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST130);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST131);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST131);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST132);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST132);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST133);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST133);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST134);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST134);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST135);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST135);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST136);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST136);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST137);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST137);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST138);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST138);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST139);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST139);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST140);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST140);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST141);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST141);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	ret[0] = ft_printf("mine : ~"TEST142);
	printf("ret = %d\n", ret[0]);
	ret[1] = printf("real : ~"TEST142);
	printf("ret = %d\n", ret[1]);
	test++;
	printf("____________________________________\n");

	printf("~ TEST%4.2d ~\n", test);
	  ret[0] = ft_printf("mine : ~"TEST143);
	  printf("ret = %d\n", ret[0]);
	  ret[1] = printf("real : ~"TEST143);
	  printf("ret = %d\n", ret[1]);
	  test++;
	  printf("____________________________________\n");

	  printf("~ TEST%4.2d ~\n", test);
	  ret[0] = ft_printf("mine : ~"TEST144);
	  printf("ret = %d\n", ret[0]);
	  ret[1] = printf("real : ~"TEST144);
	  printf("ret = %d\n", ret[1]);
	  test++;
	  printf("____________________________________\n");

	  printf("~ TEST%4.2d ~\n", test);
	  ret[0] = ft_printf("mine : ~"TEST145);
	  printf("ret = %d\n", ret[0]);
	  ret[1] = printf("real : ~"TEST145);
	  printf("ret = %d\n", ret[1]);
	  test++;
	  printf("____________________________________\n");

	  printf("~ TEST%4.2d ~\n", test);
	  ret[0] = ft_printf("mine : ~"TEST146);
	  printf("ret = %d\n", ret[0]);
	  ret[1] = printf("real : ~"TEST146);
	  printf("ret = %d\n", ret[1]);
	  test++;
	  printf("____________________________________\n");

	  printf("~ TEST%4.2d ~\n", test);
	  ret[0] = ft_printf("mine : ~"TEST147);
	  printf("ret = %d\n", ret[0]);
	  ret[1] = printf("real : ~"TEST147);
	  printf("ret = %d\n", ret[1]);
	  test++;
	  printf("____________________________________\n");

	  printf("~ TEST%4.2d ~\n", test);
	  ret[0] = ft_printf("mine : ~"TEST148);
	  printf("ret = %d\n", ret[0]);
	  ret[1] = printf("real : ~"TEST148);
	  printf("ret = %d\n", ret[1]);
	  test++;
	  printf("____________________________________\n");

	  printf("~ TEST%4.2d ~\n", test);
	  ret[0] = ft_printf("mine : ~"TEST149);
	  printf("ret = %d\n", ret[0]);
	  ret[1] = printf("real : ~"TEST149);
	  printf("ret = %d\n", ret[1]);
	  test++;
	  printf("____________________________________\n");

	  printf("~ TEST%4.2d ~\n", test);
	  ret[0] = ft_printf("mine : ~"TEST150);
	  printf("ret = %d\n", ret[0]);
	  ret[1] = printf("real : ~"TEST150);
	  printf("ret = %d\n", ret[1]);
	  test++;
	  printf("____________________________________\n");

	  free(p);
	  p = NULL;
	  free(s);
	  s = NULL;
}
