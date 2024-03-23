#include "tokens.h"
#include "utils.h"
#include "arr_utils.h"
#include <stdio.h>
#include "libft.h"

void	convert_tokens_to_string_array(t_token *token)
{
	size_t	i;
	size_t	ii;
	char	**tmp;

	i = 0;
	ii = 0;
	if (!token || !token->cmd_args || !token->cmd_args[0].elem)
		return ;
	while (token[i].cmd_args)
	{
		ii = 0;
		tmp = NULL;
		while (token[i].cmd_args[ii].elem)
		{
			if (token[i].cmd_args[ii].type != REDIR)
			{
				token[i].tmp_arr = append_str_arr(tmp,
						token[i].cmd_args[ii].elem);
				arr_free(tmp);
				if (!token[i].tmp_arr)
					return ((void)printf("something went to shit!\n"));
				tmp = token[i].tmp_arr;
			}
			ii++;
		}
		token[i].command = token[i].tmp_arr;
		i++;
	}
}

// splits into split_pipes, removes whitespace and assigns to tokens
t_token	*get_tokens(char const *trimmed_line)
{
	int		i;
	char	**split_pipes;
	t_token	*token;

	if (!ft_strchr(trimmed_line, '|'))
		split_pipes = append_str_arr(NULL, trimmed_line);
	else
		split_pipes = split_outside_quotes(trimmed_line, "|");
	if (!split_pipes)
		return (eprint("alloc fail!"), NULL);
	if (!*split_pipes)
		return (arr_free(split_pipes), NULL);
	token = init_token(arr_len(split_pipes));
	i = 0;
	while (token && split_pipes[i])
	{
		token[i].split_pipes = ft_strtrim(split_pipes[i], WHITESPACE);
		i++;
	}
	if (!token)
		eprint("alloc fail token");
	i = 0;
	while (token[i].split_pipes && split_pipes[i])
	{
		if (token[i].split_pipes != split_pipes[i])
			free(split_pipes[i]);
		i++;
	}
	free(split_pipes);
	return (token);
}
