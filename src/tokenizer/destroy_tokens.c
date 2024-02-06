#include "tokens.h"

#ifndef TEST_TOKENS_H
# include "libft.h"
# include "struct.h"
# include <stdlib.h>
#endif

void	destroy_all_tokens(t_shell *shell)
{
	t_token	*token;
	size_t	i;
	size_t	ii;

	if (!shell->token)
		return ;
	token = shell->token;
	i = 0;
	while (token[i].split_pipes)
	{
		if (token[i].cmd_args)
		{
			ii = 0;
			while (token[i].cmd_args[ii].elem)
			{
				free(token[i].cmd_args[ii].elem);
				ii++;
			}
			free(token[i].cmd_args);
		}
		if (token[i].command)
			arr_free(token[i].command);
		i++;
	}
	free(shell->token);
	shell->token = NULL;
}

// remove single token from shell
void	destroy_single_token(t_shell *shell, t_token *token)
{
	size_t	i = 0;
	size_t	ii;

	if (!token || !shell || !shell->token)
		return ;
	i = 0;
	while (shell->token[i].split_pipes != token->split_pipes)
		i++;
	if (!shell->token[i].split_pipes)
		return ;
	if (shell->token[i].cmd_args == token->cmd_args)
	{
		ii = 0;
		while (token->cmd_args[ii].elem)
		{
			free(token->cmd_args[ii].elem);
			ii++;
		}
		free(token->cmd_args);
	}
}

#include "libft.h"
t_token	*remove_token(t_shell *shell, t_token *token)
{
	size_t	i;

	if (!token)
		return (NULL);
	destroy_single_token(shell, token);
	i = 0;
	while (shell->token[i].split_pipes != token->split_pipes)
		i++;
	if (!shell->token[i].split_pipes)
		return (NULL);
	while (shell->token[i + 1].split_pipes)
	{
		shell->token[i] = shell->token[i + 1];
		i++;
	}
	ft_memset(&shell->token[i], 0, sizeof(t_token));
	return (shell->token);
}