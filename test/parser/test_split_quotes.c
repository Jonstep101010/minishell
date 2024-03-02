#include "support_lib.c"
#include "tokens.h"
#include "unity.h"

#include "interpret_quotes.c"
// #include "split_outside_quotes.c"
#include "libft.h"
#include "utils.h"
#include "arr_utils.h"
#include <unistd.h>
#include "parser.h"

#include "free_strjoin.c"
#include "expander.c"
#include "expand_variables.c"
#include "key.c"
#include "env_var.c"
#include "arr_utils.c"
#include "occurs.c"

#include "split_outside_quotes.c"

void	test_find_leaks() {
	char	*input = strdup("echo | \"nopipes |\" | echo hello");
	char	**tokens = split_outside_quotes(input, "|");

	if (!tokens || !input)
		TEST_FAIL();
	TEST_ASSERT_EQUAL_STRING("echo | \"nopipes |\" | echo hello", input);
	free(input);
	char	*expected[] =
		{"echo ", " \"nopipes |\" ", " echo hello", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 4);
	arr_free(tokens);
}

void	test_find_leaks_two() {
	char	*input = strdup("echo");
	char	**tokens = split_outside_quotes(input, "|");

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	TEST_ASSERT_EQUAL_STRING("echo", input);
	free(input);
	char	*expected[] =
		{"echo", NULL, NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
}

void	test_only_expand() {
	char	*input = strdup("$somedir ");
	char	**tokens = split_outside_quotes(input, "|");

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	TEST_ASSERT_EQUAL_STRING("$somedir ", input);
	free(input);
	char	*expected[] =
		{"$somedir ", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
}

void	test_leading_trailing_char() {
	char	*input = strdup("||echo $somedir|");
	char	**tokens = split_outside_quotes(input, "|");

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	char	*expected[] =
		{"echo $somedir", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
	free(input);
}

void	test_leading_trailing_and_split() {
	char	*input = strdup("         echo $somedir' '           ");
	char	**tokens = split_outside_quotes(input, WHITESPACE);

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	char	*expected[] =
		{"echo", "$somedir' '", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 3);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
	free(input);
}

void	test_only_trim() {
	char	*input = strdup("                    ");
	char	**tokens = split_outside_quotes(input, WHITESPACE);

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	char	*expected[] =
		{"", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
	free(input);
}

void	test_only_trim_single() {
	char	*input = strdup("        h            ");
	char	**tokens = split_outside_quotes(input, WHITESPACE);

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	char	*expected[] =
		{"h", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
	free(input);
}

void	test_only_trim_single_quotes() {
	char	*input = strdup("        '            ");
	char	**tokens = split_outside_quotes(input, WHITESPACE);

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	char	*expected[] =
		{"'", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
	free(input);
}

void	test_only_trim_single_quotes2() {
	char	*input = strdup("        'h'            ");
	char	**tokens = split_outside_quotes(input, WHITESPACE);

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	char	*expected[] =
		{"'h'", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
	free(input);
}

void	test_set_of_chars_isspace() {
	char	*input = strdup("    \t \r   h   \n  \t  \r  \n  ");
	char	**tokens = split_outside_quotes(input, " \t\r\n");

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	char	*expected[] =
		{"h", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
	free(input);
}

void	test_set_of_chars_isspace_error() {
	char	*input = strdup("    \t \r   h   \n  \t  \r  \n  ");
	char	**tokens = split_outside_quotes(input, " \t\r\n");

	if (!input)
		TEST_FAIL_MESSAGE("input alloc");
	if (!tokens)
		TEST_FAIL_MESSAGE("tokens alloc");
	char	*expected[] =
		{"h", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, tokens, 2);
	TEST_ASSERT_EQUAL(arr_len((const char **)tokens), arr_len((const char **)expected));
	arr_free(tokens);
	free(input);
}

#ifndef WHITESPACE
# define WHITESPACE " \t\r\n\v\f"
#endif

void	test_split_some_stuff() {
	char *line = "ls \n-l\r \tsomedir | cat -e | wc -l";
	char	**split_tokens = split_outside_quotes(line, "|");
	char	**expected = (char *[]){"ls \n-l\r \tsomedir ", " cat -e ", " wc -l", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, split_tokens, 4);

	// do string trim on all spaces inside the split tokens
	char	**trimmed_tokens = arr_trim(split_tokens, WHITESPACE);
	char	**expected_trimmed = (char *[]){"ls \n-l\r \tsomedir", "cat -e", "wc -l", NULL};
	TEST_ASSERT_NOT_NULL(trimmed_tokens);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_trimmed, trimmed_tokens, 4);

	char	**split_tokens_0 = split_outside_quotes(trimmed_tokens[0], WHITESPACE);

	char	**expected_0 = (char *[]){"ls", "-l", "somedir", NULL};

	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_0, split_tokens_0, 4);

	arr_free(trimmed_tokens);
	arr_free(split_tokens);
	arr_free(split_tokens_0);
}

void	test_nothing_to_trim() {
	char *line = "ls -l somedir | cat -e | wc -l";
	char	**split_tokens = split_outside_quotes(line, "|");
	char	**expected = (char *[]){"ls -l somedir ", " cat -e ", " wc -l", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, split_tokens, 4);

	// do string trim on all spaces inside the split tokens
	char	**trimmed_tokens = arr_trim(split_tokens, WHITESPACE);
	char	**expected_trimmed = (char *[]){"ls -l somedir", "cat -e", "wc -l", NULL};
	TEST_ASSERT_NOT_NULL(trimmed_tokens);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_trimmed, trimmed_tokens, 4);

	char	**split_tokens_0 = split_outside_quotes(trimmed_tokens[0], WHITESPACE);

	char	**expected_0 = (char *[]){"ls", "-l", "somedir", NULL};

	TEST_ASSERT_EQUAL_STRING_ARRAY(expected_0, split_tokens_0, 4);

	arr_free(trimmed_tokens);
	arr_free(split_tokens);
	arr_free(split_tokens_0);
}
