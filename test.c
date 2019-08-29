#include <stdio.h>
#include <malloc.h>


struct T1
{
	int x;
	int y;
	int z;
};


typedef struct Test
{
	int a;
	struct T1 * t1;
} Test;


int main(void)
{
	fprintf(stdout, "Start!\n");
	Test t;
	t.t1 = (struct T1 *) malloc(sizeof(struct T1));
	t.t1->x = 1;
	t.t1->y = 2;
	t.t1->z = 3;
	fprintf(stdout, "Ok %d %d %d!\n", t.t1->x, t.t1->y, t.t1->z);
	
	return 0;
}

