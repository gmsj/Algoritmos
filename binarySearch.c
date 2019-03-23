
/*******************************************************************************
*
*                     Implementação Busca binária
*                       Autor: Gabriel Matheus
*                          github.com/gmsj
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main () {
	int v[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}; // vetor usado para demonstração
	int x, m, l = 0, r = 10;
	printf("Valor procurado: \n");
	scanf("%d", &x);
	do {
		m = floor((l + r)/2);
		if (x == v[m]) {
			printf("Encontrado na posicao: %d\n", m);
			return m;
		}
		else if (x < v[m]) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	} while (l <= r);
	printf("Nao encontrado\n");
	return -1;
}
