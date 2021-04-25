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

/*for (int i = 0; i < ft_strlen(line_normal); i++)
		printf("%d ", mask_normal[i]);
	printf("\n");
	for (int i = 0; i < ft_strlen(line_with_spaces); i++)
		printf("%d ", mask_real[i]);
	printf("\n"); */

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
	if (!(line_normal = normal_form(line)))
		return (0);
	if (!(mask_normal = normal_form(mask)))
		return (0);
	for (int j = 0; j < ft_strlen(mask_normal); j++)
		printf("%c ", mask_normal[j]);
	printf("\n");
	for (int j = 0; j < ft_strlen(line_normal); j++)
		printf("%c ", line_normal[j]);
	printf("\n");
}

int	preparation_preparser(char *line) // входит изначальная "грязная "команда
{
	char 	*line_normal;
	char 	*line_with_spaces;
	char 	*mask_normal;
	char 	*mask_real;

	if (!(line_normal = normal_form(line))) // normal_form течет
		return (0);
	if (!(line_with_spaces = normal_space_form(line)))
		return (0);
	if (!(mask_normal = get_mask_normal(line_normal)))
		return (0);
	if (!(mask_real = get_mask_real(line_with_spaces)))
		return (0);
	masks_injection(line_normal, line_with_spaces, mask_normal, mask_real);
	printf("%s\n", line_normal);
	printf("%s\n", line_with_spaces);
	printf("%s\n", mask_normal);
	printf("%s\n", mask_real);
	printf("\n");
	//preparser(line_normal, mask_normal);
	return (1);
}

int main() {
	char *line = "\\";
	if (!preparation_preparser(line))
		return (0);
}