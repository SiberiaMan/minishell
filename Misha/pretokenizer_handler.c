#include "minishell.h"

static size_t	preparation_parser(char *line) // входит изначальная "грязная
// "команда
{
	char 	*mask_normal;

	if (!(mask_normal = get_mask_normal(line)))
		return (0);
	printf("%s\n", line);
	printf("%s\n", mask_normal);
	if (!parser(line, mask_normal))
	{
		free(mask_normal);
		return (0);
	}
	char **srcs = split_symbols(line, mask_normal, ';');
	int i = 0;
	while (srcs[i])
		printf("%s\n", srcs[i++]);
	free(mask_normal);
	return (1);
}

int main() {
	//char *line = "kek\\''";
	//char *line = "kek' okj\\hf''\\$kekehf\\'lol";
	char line[] = ";;;";
	if (!preparation_parser(line))
		return (0);
}