#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* mandatory functions */
extern int		ft_strlen(const char *s);
extern char		*ft_strcpy(char *dest, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);
extern int		ft_write(int fd, const void *buf, size_t count);
extern int		ft_read(int fd, void *buf, size_t count);
extern char		*ft_strdup(const char *s);

/* bonus typedef (same as subject) */
typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

/* bonus functions */
extern int		ft_atoi_base(char *str, char *base);
extern void		ft_list_push_front(t_list **begin_list, void *data);
extern int		ft_list_size(t_list *begin_list);
extern void		ft_list_sort(t_list **begin_list, int (*cmp)(void *, void *));
extern void		ft_list_remove_if(t_list **begin_list, void *data_ref,
				int (*cmp)(void *, void *), void (*free_fct)(void *));

/* -------------------------------------------------------------------------- */
/* helpers                                                                     */
/* -------------------------------------------------------------------------- */

static int	test_atoi_base(char *str, char *base, int expected, char *desc)
{
	int	ret;

	ret = ft_atoi_base(str, base);
	if (ret == expected)
	{
		printf("[OK]    ft_atoi_base(\"%s\", \"%s\") = %d\n", str, base, ret);
		return (1);
	}
	printf("[FAIL]  ft_atoi_base(\"%s\", \"%s\") = %d (expected %d)  -- %s\n",
		str, base, ret, expected, desc);
	return (0);
}

static void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

static int	int_cmp(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
}

static void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d -> ", *(int *)lst->data);
		lst = lst->next;
	}
	printf("NULL\n");
}

static int	list_to_array(t_list *lst, int *arr, int max)
{
	int	i;

	i = 0;
	while (lst && i < max)
	{
		arr[i++] = *(int *)lst->data;
		lst = lst->next;
	}
	return (i);
}

static void	int_free(void *data)
{
	free(data);
}

/* -------------------------------------------------------------------------- */
/* ft_atoi_base tests                                                          */
/* -------------------------------------------------------------------------- */

static void	tests_atoi_base(void)
{
	int	passed = 0;
	int	total = 0;

	printf("=== ft_atoi_base ===\n");
	printf("-- basic --\n");
	total++; passed += test_atoi_base("42", "0123456789", 42, "decimal");
	total++; passed += test_atoi_base("-42", "0123456789", -42, "negative decimal");
	total++; passed += test_atoi_base("0", "0123456789", 0, "zero");
	total++; passed += test_atoi_base("101010", "01", 42, "binary");
	total++; passed += test_atoi_base("2a", "0123456789abcdef", 42, "hex lowercase");
	total++; passed += test_atoi_base("2A", "0123456789ABCDEF", 42, "hex uppercase");
	total++; passed += test_atoi_base("-2a", "0123456789abcdef", -42, "negative hex");
	total++; passed += test_atoi_base("52", "01234567", 42, "octal");
	total++; passed += test_atoi_base("+42", "0123456789", 42, "explicit positive");
	printf("-- whitespace skip --\n");
	total++; passed += test_atoi_base("   \t\n 42", "0123456789", 42, "spaces+tab+nl");
	total++; passed += test_atoi_base("  -42", "0123456789", -42, "negative with spaces");
	printf("-- multiple signs --\n");
	total++; passed += test_atoi_base("--42", "0123456789", 0, "double minus");
	total++; passed += test_atoi_base("+-42", "0123456789", 0, "plus then minus");
	total++; passed += test_atoi_base("-+42", "0123456789", 0, "minus then plus");
	total++; passed += test_atoi_base("++42", "0123456789", 0, "double plus");
	printf("-- invalid base --\n");
	total++; passed += test_atoi_base("42", "", 0, "empty base");
	total++; passed += test_atoi_base("42", "0", 0, "single char base");
	total++; passed += test_atoi_base("42", "01234567890", 0, "duplicate char");
	total++; passed += test_atoi_base("42", "012+456", 0, "base with +");
	total++; passed += test_atoi_base("42", "012-456", 0, "base with -");
	total++; passed += test_atoi_base("42", "012 456", 0, "base with space");
	total++; passed += test_atoi_base("42", "\t1234", 0, "base with tab");
	total++; passed += test_atoi_base("42", "1234\n", 0, "base with newline");
	total++; passed += test_atoi_base("z", "01", 0, "char not in base");
	printf("-- result: %d/%d\n", passed, total);
}

/* -------------------------------------------------------------------------- */
/* ft_list_push_front + ft_list_size tests                                     */
/* -------------------------------------------------------------------------- */

static void	tests_push_and_size(void)
{
	t_list	*lst = NULL;
	int		*a, *b, *c;

	printf("\n=== ft_list_push_front + ft_list_size ===\n");
	a = malloc(sizeof(int)); *a = 10;
	b = malloc(sizeof(int)); *b = 20;
	c = malloc(sizeof(int)); *c = 30;

	printf("push 10, 20, 30\n");
	ft_list_push_front(&lst, a);
	ft_list_push_front(&lst, b);
	ft_list_push_front(&lst, c);

	printf("list: ");
	print_list(lst);

	int size = ft_list_size(lst);
	printf("size: %d (expected 3): %s\n", size, size == 3 ? "OK" : "FAIL");

	printf("empty list size: %d (expected 0): %s\n",
		ft_list_size(NULL), ft_list_size(NULL) == 0 ? "OK" : "FAIL");

	t_list	*single = NULL;
	int		*d = malloc(sizeof(int)); *d = 99;
	ft_list_push_front(&single, d);
	printf("single element size: %d (expected 1): %s\n",
		ft_list_size(single), ft_list_size(single) == 1 ? "OK" : "FAIL");

	free_list(lst);
	free_list(single);
}

/* -------------------------------------------------------------------------- */
/* ft_list_sort tests                                                          */
/* -------------------------------------------------------------------------- */

static void	tests_sort(void)
{
	t_list	*lst = NULL;
	int		values[] = { 5, 3, 8, 1, 9, 2, 7, 4, 6 };
	int		arr[9];
	int		sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int		i, ok;

	printf("\n=== ft_list_sort ===\n");

	for (i = 0; i < 9; i++)
	{
		int	*num = malloc(sizeof(int));
		*num = values[i];
		ft_list_push_front(&lst, num);
	}

	printf("before sort: ");
	print_list(lst);

	ft_list_sort(&lst, int_cmp);

	printf("after sort:  ");
	print_list(lst);

	list_to_array(lst, arr, 9);
	ok = 1;
	for (i = 0; i < 9; i++)
		if (arr[i] != sorted[i])
			ok = 0;
	printf("correct order: %s\n", ok ? "OK" : "FAIL");

	printf("sort sorted list again: ");
	ft_list_sort(&lst, int_cmp);
	print_list(lst);

	t_list	*empty = NULL;
	ft_list_sort(&empty, int_cmp);
	printf("sort empty list (should not crash): OK\n");

	t_list	*single = NULL;
	int		*n = malloc(sizeof(int)); *n = 42;
	ft_list_push_front(&single, n);
	ft_list_sort(&single, int_cmp);
	printf("sort single element (%d): %s\n",
		*(int *)single->data, *(int *)single->data == 42 ? "OK" : "FAIL");

	free_list(lst);
	free_list(single);
}

/* -------------------------------------------------------------------------- */
/* ft_list_remove_if tests                                                     */
/* -------------------------------------------------------------------------- */

static void	tests_remove_if(void)
{
	t_list	*lst = NULL;
	int		i, arr[10];
	int		expected[] = { 1, 2, 4, 5 };

	printf("\n=== ft_list_remove_if ===\n");

	for (i = 5; i >= 1; i--)
	{
		int	*num = malloc(sizeof(int));
		*num = i;
		ft_list_push_front(&lst, num);
	}

	int	ref = 3;
	printf("list: ");
	print_list(lst);
	ft_list_remove_if(&lst, &ref, int_cmp, int_free);
	printf("removed 3: ");
	print_list(lst);

	list_to_array(lst, arr, 10);
	int	ok = 1;
	for (i = 0; i < 4; i++)
		if (arr[i] != expected[i])
			ok = 0;
	printf("correct: %s\n", ok ? "OK" : "FAIL");
	printf("correct size: %d (expected 4): %s\n",
		ft_list_size(lst), ft_list_size(lst) == 4 ? "OK" : "FAIL");

	printf("\nremove first element (1):\n");
	ref = 1;
	ft_list_remove_if(&lst, &ref, int_cmp, int_free);
	print_list(lst);

	printf("\nremove 2 and 4:\n");
	ref = 2;
	ft_list_remove_if(&lst, &ref, int_cmp, int_free);
	ref = 4;
	ft_list_remove_if(&lst, &ref, int_cmp, int_free);
	print_list(lst);
	printf("remaining size: %d (expected 1): %s\n",
		ft_list_size(lst), ft_list_size(lst) == 1 ? "OK" : "FAIL");

	printf("\nremove last element (5):\n");
	ref = 5;
	ft_list_remove_if(&lst, &ref, int_cmp, int_free);
	print_list(lst);
	printf("remaining size: %d (expected 0): %s\n",
		ft_list_size(lst), ft_list_size(lst) == 0 ? "OK" : "FAIL");

	printf("\nremove from empty list (should not crash):\n");
	ref = 1;
	ft_list_remove_if(&lst, &ref, int_cmp, int_free);
	printf("OK (no crash)\n");
}

/* -------------------------------------------------------------------------- */
/* mandatory quick check                                                       */
/* -------------------------------------------------------------------------- */

static void	mandatory_check(void)
{
	char	buf[100];

	printf("=== mandatory quick check ===\n");
	printf("ft_strlen(\"42\") = %d (expected 2): %s\n",
		ft_strlen("42"), ft_strlen("42") == 2 ? "OK" : "FAIL");
	ft_strcpy(buf, "hello");
	printf("ft_strcpy -> \"%s\" (expected \"hello\"): %s\n",
		buf, strcmp(buf, "hello") == 0 ? "OK" : "FAIL");
	printf("ft_strcmp(\"abc\", \"def\") = %d (expected <0): %s\n",
		ft_strcmp("abc", "def"), ft_strcmp("abc", "def") < 0 ? "OK" : "FAIL");
	ft_write(1, "  ft_write OK\n", 15);
	printf("ft_strdup(\"dup\") != NULL: %s\n",
		ft_strdup("dup") != NULL ? "OK" : "FAIL");
}

/* -------------------------------------------------------------------------- */
/* main                                                                        */
/* -------------------------------------------------------------------------- */

int	main(void)
{
	mandatory_check();
	tests_atoi_base();
	tests_push_and_size();
	tests_sort();
	tests_remove_if();
	printf("\n=== all bonus tests done ===\n");
	return (0);
}
