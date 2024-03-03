#include "unity.h"
#include "arr_utils.c"
#include "export_var.c"
#include "print_arr_sep.c"
#include "str_equal.c"
#include "key.c"
#include "free_strjoin.c"
#include "support_lib.c"

void	test_replace_key() {
	char	*env[] = {"something=wrong", "this=false", "some=none", NULL};
	char	**arr = arr_dup((const char **)env);
	char	**ret = export_var(arr, "this=correct");
	if (!ret)
		TEST_FAIL();
	char	*expected[] = {"something=wrong", "this=correct", "some=none", NULL};
	printf("%s\n", arr[1]);
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, ret, 3);
	arr_free(ret);
}

void	test_replace_key_two() {
	char	*env[] = {"something=wrong", "this=false", "some=none", NULL};
	char	**arr = arr_dup((const char **)env);
	char	**ret = export_var(arr, "this= correct");
	if (!ret || !arr)
		TEST_FAIL();
	char	*expected[] = {"something=wrong", "this= correct", "some=none", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, ret, 4);
	arr_free(ret);
}

// #include "support_shell.c"

// void	test_export_invalid_name() {
// 	t_shell	*shell = setup_shell(NULL);
// 	char	*env[] = {"something=wrong", "this=false", "some=none", NULL};
// 	char	**arr = arr_dup((const char **)env);
// 	shell->owned_envp = arr;
// 	char	*tmp[] = {"export", "th@is=", "correct", NULL};
// 	char	**command;
// 	command = arr_dup((const char **)tmp);

// 	export(shell);
// 	char	*expected[] = {"something=wrong", "this=false", "some=none", NULL};
// 	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, arr, 4);
// 	arr_free(arr);
// 	arr_free(command);
// 	clean_shell(shell);
// }

// void	test_export_valid_name() {
// 	t_shell	*shell = setup_shell(NULL);
// 	char	*env[] = {"something=wrong", "this=false", "some=none", NULL};
// 	char	**arr = arr_dup((const char **)env);
// 	shell->owned_envp = arr;
// 	char	*tmp[] = {"export", "this=correct", NULL};
// 	command = arr_dup((const char **)tmp);
// 	export(shell);
// 	char	*expected[] = {"something=wrong", "this=correct", "some=none", NULL};
// 	TEST_ASSERT_NOT_NULL(shell->owned_envp);
// 	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, shell->owned_envp, 3);
// 	arr_free(arr);
// 	arr_free(command);
// 	clean_shell(shell);
// }

void	test_replace_using_update() {
	char	*env[] = {"something=wrong", "this=false", "some=none", NULL};
	char	**arr = arr_dup((const char **)env);
	update_variable(arr, "this", "correct");
	char	*expected[] = {"something=wrong", "this=correct", "some=none", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, arr, 4);
	arr_free(arr);
}

void	test_replace_using_update_overlap_key() {
	char	*env[] = {"something=wrong", "this=false", "some=none", NULL};
	char	**arr = arr_dup((const char **)env);
	update_variable(arr, "thia", "correct");
	char	*expected[] = {"something=wrong", "this=false", "some=none", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, arr, 4);
	arr_free(arr);
}
