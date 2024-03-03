#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "arr_utils.c"
#include "find_key.c"
#include "print_arr_sep.c"
#include "str_equal.c"
#include "expander.c"
#include "support_lib.c"

#define TOKENS_H
#define STRUCT_H

#ifndef WHITESPACE
# define WHITESPACE " \t\n\r\v\f"
#endif

typedef struct s_token	t_token;

enum e_arg
{
	STRING,
	PIPE,
	EXPANSION,
};

enum e_quote
{
	SINGLE,
	DOUBLE,
	NONE,
};

enum e_builtin
{
	ENV,
	EXPORT,
	UNSET,
	CD,
	PWD,
	BUILTIN_ECHO,
	EXIT,
	NOT_BUILTIN,
};

typedef struct s_arg
{
	char	*elem;
	enum	e_arg	type;
	enum	e_quote	quote;
}	t_arg;
t_arg	*init_cmdargs(size_t size);

typedef struct s_shell	t_shell;
struct s_token
{
	t_arg	*cmd_args;// keep attributes in execution (i.e. redirs), cmd_args[0] is the first token/command (not pipe)
	char	*split_pipes;
	// char	**args;
	char	**tmp_arr;
	char	**command;// for execution (each token has the command)
	enum	e_builtin	builtin_info;
	// size_t	status;// for usage with the pipes?
	// char	*bin;// for finding path/to/bin?
	int		(*cmd_func)(t_shell *, t_token *);// not sure if this is necessary
};

// @audit-info mod split_quotes to take a function pointer (for whitespace that can be space or tab)
// take the token with command string and split it into command and arguments
// if we find any pipes
// char	*expand_variables(const char *input, const char **envp);

#include <termios.h>
typedef struct s_shell
{
	char	**split_tokens;
	char	**split_pipes;
	int		exit_status;
	char	**owned_envp;
	char	*line;
	char	*expanded_line;
	char	*trimmed_line;
	char	*tmp;
	char	**tmp_arr;
	// char	**command;// not sure if we need this
	t_token	*token;
	struct termios	p_termios;
}	t_shell;

void	mock_convert_split_token_string_array_to_tokens(t_shell *shell)
{
	size_t	i;
	size_t	ii;
	size_t	len;

	i = 0;
	ii = 0;
	char	*tmp;
	if (!shell->token || !shell->token[i].split_pipes)
		return ;
	while (shell->token[i].split_pipes)
	{
		// split into command and arguments
		shell->token[i].tmp_arr = split_outside_quotes(shell->token[i].split_pipes, WHITESPACE);
		if (!shell->token[i].tmp_arr)
			return ;
		len = arr_len((const char **)shell->token[i].tmp_arr);
		if (len == 0)
			return ;
		// create cmd_args with space for the arguments
		shell->token[i].cmd_args = init_cmdargs(len);
		if (!shell->token[i].cmd_args)
			return ;
		ii = 0;
		while (shell->token[i].tmp_arr[ii])
		{
			// store the cmd_args in the token
			shell->token[i].cmd_args[ii].elem = shell->token[i].tmp_arr[ii];
			if (!shell->token[i].cmd_args[ii].elem)
				return ;
			// @follow-up add more properties (count?), separate function?
			if (str_cchr(shell->token[i].cmd_args[ii].elem, '\'') == 0 && str_cchr(shell->token[i].cmd_args[ii].elem, '"') == 0)
				shell->token[i].cmd_args[ii].quote = NONE;
			if (str_cchr(shell->token[i].cmd_args[ii].elem, '"'))
				shell->token[i].cmd_args[ii].quote = DOUBLE;
			if (str_cchr(shell->token[i].cmd_args[ii].elem, '\''))
				shell->token[i].cmd_args[ii].quote = SINGLE;
			while (str_cchr(shell->token[i].cmd_args[ii].elem, '$'))
			{
				tmp = expander(shell->token[i].cmd_args[ii].elem, (const char **)shell->owned_envp);
				if (!tmp)
					return ;
				if (ft_strncmp(tmp, shell->token[i].cmd_args[ii].elem, ft_strlen(tmp)) == 0)
				{
					printf("recursive expansion is the same as the original, freeing\n");
					printf("reex: %s\n", shell->token[i].cmd_args[ii].elem);
					free(tmp);
					break ;
				}
				free(shell->token[i].cmd_args[ii].elem);
				shell->token[i].cmd_args[ii].elem = tmp;
			}
			shell->token[i].cmd_args[ii].type = STRING; // default type
			ii++;
		}
		free(shell->token[i].tmp_arr);
		i++;
	}
}
#include "token_utils.c"
#include "build_tokens.c"
t_shell	*support_test_tokens_input(char *line, char **envp)
{
	t_shell	*shell;

	// input like "ls -l somedir | cat -e | wc -l";
	shell = (t_shell *) malloc(sizeof(t_shell));
	char	*input = ft_strdup(line);

	shell->split_pipes = split_outside_quotes(input, "|");
	free(input);

	// trim beforehand
	shell->split_tokens = arr_trim(shell->split_pipes, WHITESPACE);
	arr_free(shell->split_pipes);
	shell->owned_envp = arr_dup((const char **)envp);

	// add the split tokens as tokens
	add_pipes_as_tokens(shell);

	mock_convert_split_token_string_array_to_tokens(shell);
	return (shell);
}
