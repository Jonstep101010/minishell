#include "support_lib.c"
#include "unity.h"
#include "unset.c"
#include "find_key.c"
#include "arr_utils.c"
#include "check_key.c"
#include "occurs.c"
#include "free_strjoin.c"

void	test_remove_key_value() {
	char	*env[] = {"something=wrong", "this=false", "some=none", NULL};
	char	**arr = arr_dup((const char **)env);
	unset(((const char *[]){"unset", "this", NULL}), arr);
	if (!arr)
		TEST_FAIL();
	char	*expected[] = {"something=wrong", "some=none", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(expected, arr, 3);
	arr_free(arr);
}
