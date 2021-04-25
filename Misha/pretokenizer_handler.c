#include "minishell.h"

static void  masks_injection(char *line_normal, char *line_with_spaces,
char *mask_normal, char *mask_real)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(line_with_spaces))
	{
		while(line_with_spaces[i] != line_normal[j])
			i++;
		mask_real[i++] = mask_normal[j++];
	}
}

int	preparser(char *line, char *mask)
{
	size_t	i;
	char 	*line_normal;
	char 	*mask_normal;
    // обработать 5 в маске и линии
	i = 0;
	while (i < ft_strlen(line))
	{
		if (mask[i] == '5')
		{
			mask[i] = ' ';
			line[i] = ' ';
		}
		i++;
	}
	/*if (!(line_normal = normal_form(line)))
		return (0);
	if (!(mask_normal = normal_form(mask)))
		return (0);
	printf("%s\n", line_normal);
	printf("%s\n", mask_normal); */
}

int	preparation_preparser(char *line) // входит изначальная "грязная "команда
{
	char 	*mask_normal;

	if (!(mask_normal = get_mask_normal(line)))
		return (0);
	printf("%s\n", line);
	printf("%s\n", mask_normal);
	//preparser(line_normal, mask_normal);
	return (1);
}

int main() {
	//char *line = "kek\\''";
	//char *line = "kek'okj\\hf''\\$kekehf\\'lol";
	char *line = "ls -la \"$\" kek.txt; cat -e kek.txt";
	if (!preparation_preparser(line))
		return (0);
}