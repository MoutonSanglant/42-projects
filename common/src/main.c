#include "options.h"

#include <stdio.h>

int color(char const *arg)
{
	static int control = 0;

	if (control++ > 0)
	{
		printf("color multiple times !!\n");
		return (0);
	}

	printf("color callback: %s\n", arg);
	return (1);
}

int test(char const *arg)
{
	printf("test callback: %s\n", arg);
	return (1);
}

int fallback(char const *arg)
{
	printf("'%s' fallback\n", arg);
	return (0);
}

int main(int argc, char const **argv)
{
	const t_option	options[3] = {
		{ .name = "color", .token = "c", .fn = &color, .arg = 0 },
		{ .name = "test", .token = "t", .fn = &test, .arg = 1 },
		{ NULL }
	};

	if (parse_options(argc, argv, options, &fallback))
	{
		printf("ERROR USAGE !!\n");
		return (1);
	}

	return (0);
}
