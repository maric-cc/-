# include <stdio.h>
# include <math.h>
# include <string.h>
# include <time.h>

# define MIN(x, y) ((x)<(y) ? (x):(y))

# define N 9
# define DIR_N 4
# define INF 0x7fffffff
# define MAX_DEPTH 1000
# define SIZE 3

char solved;
char start[N], goal[N];
char cur[N];

int bound;
const char md[] = { 'u', 'l', 'r', 'd' };
const short int dir[][2] = { {-1,0}, {0,-1}, {0,1}, {1,0} };
char path[MAX_DEPTH];

void move(void);
void solve(void);
char read(char *s);
int IDAstar(void);
char bool_inv(char *s);
int heu(void);
int dfs(int zero_pos, int depth, char direction);
void print_state(char *s);

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	while (read(start))
	{
		read(goal);
		memcpy(cur, start, N);
		solve();
	}

	printf("time cost %.6lf s.\n", (double)clock() / CLOCKS_PER_SEC);

	return 0;
}

void solve()
{
	int i, depth;

	if (bool_inv(start) != bool_inv(goal)) puts("unsolvable");
	else
	{
		memset(path, -1, sizeof(path));
		depth = IDAstar();
		for (i = 0; path[i] != -1; ++i)
		{
			putchar(md[path[i]]);
		}
		printf(" %d\n", i);
	}
	//move(); //打印移动过程，调试的时候用的，加上这个总共用时31ms
}

char read(char *s)
{
	char c[5];
	int i;

	if (EOF == scanf("%s", c)) return 0;
	else s[0] = (c[0] == 'x' ? 0 : c[0] - '0');
	for (i = 1; i < N; ++i)
	{
		scanf("%s", c);
		s[i] = (c[0] == 'x' ? 0 : c[0] - '0');
	}

	return 1;
}

int IDAstar(void)
{
	int i;

	solved = 0;
	bound = heu();

	for (i = 0; start[i] && i < N; ++i);

	while (!solved && bound < 100)
	{
		bound = dfs(i, 0, -10);
	}

	return bound;
}

int dfs(int pos, int depth, char d)
{
	int h, i, nx, ny, npos, nbound, t;

	h = heu();

	if (depth + h > bound) return depth + h;
	if (h == 0)
	{
		/* printf("depth = %d.\n", depth); */
		solved = 1;
		return depth;
	}

	nbound = INF;
	for (i = 0; i < DIR_N; ++i)
	{
		if (i + d == DIR_N - 1) continue;
		nx = pos / SIZE + dir[i][0];
		ny = pos % SIZE + dir[i][1];
		if (0 <= nx && nx < SIZE && 0 <= ny && ny < SIZE)
		{
			path[depth] = i;
			npos = nx * SIZE + ny;
			cur[pos] = cur[npos]; cur[npos] = 0;    /* 后来一直出错就是这里的原因：pos -> npos */
			t = dfs(npos, depth + 1, i);
			if (solved) return t;
			nbound = MIN(nbound, t);
			cur[npos] = cur[pos]; cur[pos] = 0;
		}
	}
	return nbound;
}

int heu(void)            /* return heu(cur_state) */
{
	char ch;
	int i, j, ret;

	ret = 0;
	for (i = 0; i < N; ++i)
	{
		ch = goal[i];
		if (ch == 0) continue;
		for (j = 0; j < N; ++j)
		{
			if (ch == cur[j])
			{
				ret = ret + abs(i / SIZE - j / SIZE) + abs(i%SIZE - j % SIZE);
			}
		}
	}

	return ret;
}

char bool_inv(char *s)
{
	char ch, ret;
	int i, j;

	ret = 0;
	for (i = 0; i < N - 1; ++i)
	{
		if ((ch = s[i]) == 0) continue;
		for (j = i + 1; j < N; ++j)
		{
			if (s[j] && s[j] < ch) ret = 1 - ret;
		}
	}

	return ret;
}

void move(void)
{
	char ncur[N];
	int i, pos, nx, ny, npos;

	memcpy(ncur, start, N);
	print_state(ncur);
	for (i = 0; start[i] && i < N; ++i);
	pos = i;
	for (i = 0; path[i] != -1; ++i)
	{
		nx = pos / SIZE + dir[path[i]][0];
		ny = pos % SIZE + dir[path[i]][1];
		npos = nx * SIZE + ny;
		ncur[pos] = ncur[npos]; ncur[npos] = 0;
		pos = npos;
		print_state(ncur);
	}
}

void print_state(char *s)
{
	int i;

	for (i = 0; i < N; ++i)
	{
		putchar(s[i] + '0');
	}
	putchar('\n');
}


