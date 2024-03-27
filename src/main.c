#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "msh_signals.h"
#include "get_next_line.h"
#include "minishell.h"
#include <stdlib.h>
#include "utils.h"
#include "commands.h"
#include "lexer.h"
#include "struct.h"

void	minishell_loop(t_shell *shell)
{
	char	*trimmed_line;

	// check_signals(&shell->p_termios);
	while (1)
	{
		if (isatty(fileno(stdin)))
		{
			trimmed_line = get_input(readline("minishell> "));
			if (!trimmed_line)
				builtin_exit(shell, NULL);
			add_history(trimmed_line);
			if (!*trimmed_line || lexer(shell, trimmed_line) != LEXER_SUCCESS)
				continue ;
			if (shell->env && *shell->env && shell->token)
				execute_commands(shell, shell->token);
		}
		else
		{
			trimmed_line = get_input(get_next_line(fileno(stdin)));
			if (!trimmed_line)
			{
				arr_free(shell->env);
				free(shell);
				exit(1);
			}
			if (!*trimmed_line || lexer(shell, trimmed_line) != LEXER_SUCCESS)
				continue ;
			if (shell->env && *shell->env && shell->token)
				execute_commands(shell, shell->token);
			int status = shell->exit_status;
			if (shell->env)
				arr_free(shell->env);
			free(shell);
			exit(status);
		}
	}
}

int main(int ac, char **av, char **envp)
{
	t_shell		*shell;

	(void)ac;
	(void)av;
	// if (ac > 1 || av[1])
	// 	return (printf("do not pass arguments\n"), 1);
	shell = init_shell(envp);
	if (!shell)
		return (1);
	minishell_loop(shell);
	return (0);
}
