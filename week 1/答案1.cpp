#include <stdio.h>
 
int main()
{
	int A, i, j, k, p = 0;
	scanf("%d", &A);
	for(i=A; i<A+4; ++i)
		for(j=A; j<A+4; ++j)
			for(k=A; k<A+4; ++k)
			{
				if(i != j && i != k && j != k)
				{
	
					printf("%d", i*100+10*j+k);
					p++;
					if(p%6 == 0)
						printf("\n");
					else 
						printf(" ");
				}
			}
	
	return 0; 
}
