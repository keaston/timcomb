#include <stdio.h>
#include <stdlib.h>

void do_timcomb(int n, int r, int c, int *a)
{
	if (r == n)
	{
		/* output the result */
		int i, j;

		putchar('{');
		for (i = 0; i < n; i++)
		{
			if (i)
				putchar(','), putchar(' ');
			putchar('(');	
			for (j = 0; j < n; j++)
			{
				if (j)
					putchar(','), putchar(' ');
				printf("%d", a[i * n + j]);
			}
			putchar(')');
		}
		puts("}");
	}
	else
	{
		if (r == 0)
		{
			/* First row */
			a[r * n + c] = c + 1;
			do_timcomb(n, r + (c + 1) / n, (c + 1) % n, a);
		}
		else if (r == c)
		{
			/* Major axis */
			a[r * n + c] = 1;
			do_timcomb(n, r + (c + 1) / n, (c + 1) % n, a);
		}
		else
		{
			int x;

			for (x = 2; x <= n; x++)
			{
				int i, found = 0;

				/* Search prior rows in this column */
				for (i = 0; i < r && !found; i++)
					found = (a[i * n + c] == x);
				/* Search prior columns in this row */
				for (i = 0; i < c && !found; i++)
					found = (a[r * n + i] == x);

				if (!found)
				{
					a[r * n + c] = x;
					do_timcomb(n, r + (c + 1) / n, (c + 1) % n, a);
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int n;
	int *a;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <n>\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);
	a = malloc(n * n * sizeof *a);

	if (!a)
	{
		fprintf(stderr, "Out of memory\n");
		return 2;
	}

	do_timcomb(n, 0, 0, a);

	return 0;
}

