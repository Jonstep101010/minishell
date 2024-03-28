#ifndef UTILS_H
# define UTILS_H
# include "arr_utils.h"
# include "tokens.h"
# include <stddef.h>
# include <stdbool.h>
# include "struct.h"

char	*equal(const char *expected, const char *actual);
int		arr_ncmp(char *const *arr1, char *const *arr2, size_t n);

void	rm_str_arr(char **arr, const char *s);
char	**arr_trim(char **arr, char const *set);

// error handling
/**
 * @brief "minishell: " + fmt on stderr
 */
void	eprint(const char *fmt, ...);
void	exit_free(t_shell *shell, int exit_code);
void	exit_error(t_shell *shell, char *error_elem);

/**
 * @brief fmt on stderr
 */
void	eprint_single(const char *fmt, ...);
void	exit_free(t_shell *shell, int exit_code);
void	exit_error(t_shell *shell, char *error_elem);

#endif