#include <stdbool.h>
#include "libft.h"

bool	*bool_arr_zeroing(size_t len)
{
	size_t	i = 0;
	bool	*ignore;

	ignore = (bool *) ft_calloc(len + 1, sizeof(bool));
	if (!ignore)
		return (NULL);
	while (i < len + 1)
	{
		ignore[i] = false;
		i++;
	}
	return (ignore);
}

// "this is my input "ignore" 't' 'this' "is" 'a' "test" 'string'""
// "                 00000000 000 000000 0000 000 000000 000000000"
// "this is my input \"ignore\" 't' 'this' \"is\" 'a' \"test\" 'string'"
// "11111111111111111000000001000100000010000100010000001000000000"
// "00000000000000000111111110111011111101111011101111110111111111"

/**
 * @brief ignore range starting at c
 * @warning caller needs to make sure that c is not unclosed
 * @param s
 * @param ignore array of bools
 * @param c character delimiting the range
 */
void	range_ignore(const char *s, bool *ignore, unsigned char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c && ignore[i] == false)
		{
			ignore[i] = true;
			i++;
			while (s[i] && s[i] != c)
			{
				ignore[i] = true;
				i++;
			}
			if (s[i] == c)
				ignore[i] = true;
			while (s[i] != c)
			{
				ignore[i] = false;
				i--;
			}
		}
		else
			i++;
	}
}