/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tests.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: priviere <priviere@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/18 10:29:29 by abourin      #+#   ##    ##    #+#       */
/*   Updated: 2019/12/19 11:26:24 by priviere    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include <stdio.h>

int main(void)
{
	int t;
	char c;

	c = 'a';
	t = 50;
	printf("p0 % .3s\n", "cccc");
	printf("pp %.50d\n", 10000);
	printf("p1 %.4s\n", "cccc");
	printf("p2 %.10s\n", "cccc");
	printf("p3 %.4s\n", NULL);
	printf("p4 %.5s\n", "aaaaa");
	printf("p5 %.3d\n", 100);
	printf("p6 %.0d\n", 100);
	printf("p7 %.4d\n", 100);
	printf("p8 %.10d\n", 100);
	printf("p9 %.50d\n", 100);
	printf("p10 %.1d\n", 100);
	printf("p11 %.3d\n", 100);
	printf("p12 %.0d\n", 0);
	printf("p13 %.3i\n", 100);
	printf("p14 %.0i\n", 100);
	printf("p15 %.4i\n", 100);
	printf("p16 %.10i\n", 100);
	printf("p17 %.50i\n", 100);
	printf("p18 %.1i\n", 100);
	printf("p19 %.3x\n", 100);
	printf("p20 %.0x\n", 0);
	printf("p21 %.3x\n", 100);
	printf("p22 %.0x\n", 100);
	printf("p23 %.4x\n", 100);
	printf("p24 %.10x\n", 100);
	printf("p25 %.50x\n", 100);
	printf("p26 %.1x\n", 100);
	printf("p27 %.3x\n", 100);
	printf("p28 %.0x\n", 0);
	printf("p29 %.3u\n", 100);
	printf("p30 %.0u\n", 100);
	printf("p31 %.4u\n", 100);
	printf("p32 %.10u\n", 100);
	printf("p33 %.50u\n", 100);
	printf("p34 %.1u\n", 100);
	printf("p35 %.3u\n", 100);
	printf("p36 %.0u\n", 0);
	printf("taaa %100s\n", "hello");
}