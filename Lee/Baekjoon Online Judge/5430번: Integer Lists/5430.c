#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int main()
{
	uint_fast8_t t;
	size_t n;
	char op[100001];
	char in[400002];
	char* x[100000];

	scanf("%" SCNuFAST8, &t);

	for(uint_fast8_t throwaway = 0; throwaway < t; ++throwaway)
	{
		scanf("%s", op);
		scanf("%zu", &n);
		scanf("%s", in);

		memset(x, 0, 100000);

		char** write = x;
		char* seek;

		for(seek = in; *seek != ']'; ++seek)
		{
			if(*seek == '[' || *seek == ',')
			{
				if(*seek == '[' && *(seek + 1) == ']')
					break;
				else if(*seek == ',')
					*seek = '\0';

				*(write++) = ++seek;
			}
		}
		*seek = '\0';

		bool rev = false;
		char** begin = x;
		char** end = x + n;

		bool error = false;

		for(char* o = op; *o != '\0'; ++o)
		{
			switch(*o)
			{
			case 'R':
				rev = !rev;
				break;

			case 'D':
				if(rev) --end;
				else ++begin;

				if(begin > end)
					error = true;
				break;
			}

			if(error) break;
		}

		if(error)
		{
			printf("error\n");
			continue;
		}

		printf("[");
		if(rev)
		{
			char** i = end - 1;
			if(i >= begin)
			{
				printf("%s", *(i--));
				while(i >= begin)
					printf(",%s", *(i--));
			}

		}
		else
		{
			char** i = begin;
			if(i < end)
			{
				printf("%s", *(i++));
				while(i < end)
					printf(",%s", *(i++));
			}
		}
		printf("]\n");
	}

	return 0;
}
