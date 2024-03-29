#include "libft.h"
#include "libutils.h"
#include "tokens.h"
#include "utils.h"

static char	*collect_as_ascii(char *readline_line)
{
	int		i;
	char	*collected_line;

	i = 0;
	collected_line = NULL;
	while (readline_line && readline_line[i])
	{
		if (ft_isascii(readline_line[i]))
		{
			collected_line = append_char_str(collected_line, readline_line[i]);
			if (!collected_line)
				return (free(readline_line), NULL);
		}
		i++;
	}
	if (readline_line)
		free(readline_line);
	return (collected_line);
}

char	*get_input(char *rl_prompt)
{
	static	char	*line;
	char			*trim;

	if (!rl_prompt)
		return (free_null(&line), NULL);
	line = collect_as_ascii(rl_prompt);
	if (!line)
		return (NULL);
	trim = ft_strtrim(line, WHITESPACE);
	free_null(&line);
	if (!trim)
		return (NULL);
	line = trim;
	return (line);
}
