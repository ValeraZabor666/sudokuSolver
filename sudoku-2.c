#include <stdlib.h>
#include <unistd.h>

int	**convert(char **argv)
{
	int	**dest;
	int	i;
	int	j;

	i = 0;
	j = 0;
	dest = NULL;
	dest = (int**)malloc(sizeof(int*) * 9);
	while (i <= 8)
	{
		dest[i] = (int*)malloc(sizeof(int) * 9);
		j = 0;
		while (j <= 8)
		{
			if (argv[i + 1][j] == '.')
				dest[i][j] = 0;
			else
				dest[i][j] = argv[i + 1][j] - '0';
			j++;
		}
		i++;
	}
	return (dest);
}

int	possible(int y, int x, int n, int **dest)
{
	int	col;
	int	line;

	col = -1;
	line = -1;
	while (++col <= 8 && ++line <= 8)
	{
		if (dest[y][col] == n)
			return (0);
		if (dest[line][x] == n)
			return (0);
	}
	line = y - (y % 3);
	while (line / 3 <= y / 3 && line <= 8)
	{
		col = x - (x % 3);
		while (col / 3 <= x / 3 && col <= 8)
		{
			if (dest[line][col] == n)
				return (0);
			col++;
		}
		line++;
	}
	return (1);
}


int	solve(int **dest)
{
	int x;
	int y;
	int n;

	y = -1;
	n = 0;
	while (++y <= 8)
	{
		x = -1;
		while (++x <= 8)
			if (dest[y][x] == 0)
			{
				while (++n <= 9)
					if (possible(y, x, n, dest))
					{
						dest[y][x] = n;
						if (solve(dest))
							return (1);
						dest[y][x] = 0;
					}
				return (0);
			}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 10)
	{
		write(1, "Error\n", 6);
		return (0);
	} 
	int **dest;
	int i;
	int j;
	char a;

	i = -1;
	dest = convert(argv);
	solve(dest);
	while (++i <= 8)
	{
		j = -1;
		while (++j <= 8)
		{
			a = dest[i][j] + '0';
			write(1, &a, 1);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	return (0);
}
