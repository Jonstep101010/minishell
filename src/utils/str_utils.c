#include "libft.h"

char	*free_first_join(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin((const char *)s1, s2);
	free(s1);
	return (joined);
}
