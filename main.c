#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

extern int		ft_strlen(const char *s);
extern char		*ft_strcpy(char *dest, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);
extern int		ft_write(int fd, const void *buf, size_t count);
extern int		ft_read(int fd, void *buf, size_t count);
extern char		*ft_strdup(const char *s);

#define PASS printf("  [OK]\n")
#define FAIL printf("  [FAIL]\n")

/* -------------------------------------------------------------------------- */
/* ft_strlen                                                                   */
/* -------------------------------------------------------------------------- */

static void	test_strlen(void)
{
	printf("=== ft_strlen ===\n");

	printf("empty string: ft=%d lib=%zu",
		ft_strlen(""), strlen(""));
	((size_t)ft_strlen("") == strlen("")) ? PASS : FAIL;

	printf("short:        ft=%d lib=%zu",
		ft_strlen("42"), strlen("42"));
	((size_t)ft_strlen("42") == strlen("42")) ? PASS : FAIL;

	printf("long:         ft=%d lib=%zu",
		ft_strlen("Hello, World! 123456789"), strlen("Hello, World! 123456789"));
	((size_t)ft_strlen("Hello, World! 123456789") == strlen("Hello, World! 123456789")) ? PASS : FAIL;
}

/* -------------------------------------------------------------------------- */
/* ft_strcpy                                                                   */
/* -------------------------------------------------------------------------- */

static void	test_strcpy(void)
{
	char	ft_buf[256];
	char	lib_buf[256];
	char	*ft_ret;
	char	*lib_ret;

	printf("\n=== ft_strcpy ===\n");

	printf("hello:        ");
	ft_ret = ft_strcpy(ft_buf, "hello");
	lib_ret = strcpy(lib_buf, "hello");
	(ft_ret == ft_buf && strcmp(ft_buf, lib_buf) == 0) ? PASS : FAIL;

	printf("empty:        ");
	ft_ret = ft_strcpy(ft_buf, "");
	lib_ret = strcpy(lib_buf, "");
	(ft_ret == ft_buf && strcmp(ft_buf, lib_buf) == 0) ? PASS : FAIL;

	printf("long:         ");
	ft_ret = ft_strcpy(ft_buf, "Lorem ipsum dolor sit amet");
	lib_ret = strcpy(lib_buf, "Lorem ipsum dolor sit amet");
	(ft_ret == ft_buf && strcmp(ft_buf, lib_buf) == 0) ? PASS : FAIL;

	printf("return value: ");
	printf("ft=%p lib=%p %s",
		(void *)ft_ret, (void *)lib_ret,
		ft_ret == ft_buf ? "OK" : "FAIL");
	printf("\n");
}

/* -------------------------------------------------------------------------- */
/* ft_strcmp                                                                   */
/* -------------------------------------------------------------------------- */

typedef struct { char *s1; char *s2; } t_strcmp_test;

static void	test_strcmp(void)
{
	t_strcmp_test tests[] = {
		{"", ""},
		{"a", ""},
		{"", "a"},
		{"hello", "hello"},
		{"abc", "abd"},
		{"abd", "abc"},
		{"Hello", "Hello "},
		{"zzz", "aaa"},
		{0, 0}
	};
	int	i;

	printf("\n=== ft_strcmp ===\n");
	for (i = 0; tests[i].s1; i++)
	{
		int ft_ret = ft_strcmp(tests[i].s1, tests[i].s2);
		int lib_ret = strcmp(tests[i].s1, tests[i].s2);
		printf("\"%s\" vs \"%s\": ft=%d lib=%d",
			tests[i].s1, tests[i].s2, ft_ret, lib_ret);
		((ft_ret == lib_ret) ||
		 (ft_ret < 0 && lib_ret < 0) ||
		 (ft_ret > 0 && lib_ret > 0)) ? PASS : FAIL;
	}
}

/* -------------------------------------------------------------------------- */
/* ft_write + ft_read                                                          */
/* -------------------------------------------------------------------------- */

static void	test_write(void)
{
	int		ft_ret, lib_ret, ft_err, lib_err;
	char	buf[6] = "hello";
	int		pipefd[2];

	printf("\n=== ft_write ===\n");

	printf("stdout:  ft=%d lib=%d",
		ft_write(1, "hello\n", 6), (int)write(1, "hello\n", 6));
	PASS;

	printf("pipe:    ");
	pipe(pipefd);
	ft_ret = ft_write(pipefd[1], buf, 5);
	lib_ret = write(pipefd[1], buf, 5);
	(ft_ret == lib_ret) ? PASS : FAIL;
	close(pipefd[0]);
	close(pipefd[1]);

	printf("bad fd:  ");
	errno = 0; ft_ret = ft_write(-1, "x", 1); ft_err = errno;
	errno = 0; lib_ret = write(-1, "x", 1);   lib_err = errno;
	(ft_ret == lib_ret && ft_err == lib_err)
		? printf(" ret=%d errno=%d OK\n", ft_ret, ft_err)
		: printf(" ft(ret=%d,errno=%d) lib(ret=%d,errno=%d) FAIL\n",
			ft_ret, ft_err, lib_ret, lib_err);
}

static void	test_read(void)
{
	int		ft_ret, lib_ret, ft_err, lib_err;
	char	ft_buf[32];
	char	lib_buf[32];
	int		pipefd[2];

	printf("\n=== ft_read ===\n");

	printf("pipe:    ");
	pipe(pipefd);
	write(pipefd[1], "XYZ", 3);
	close(pipefd[1]);
	ft_ret = ft_read(pipefd[0], ft_buf, 5);
	ft_buf[ft_ret] = 0;
	close(pipefd[0]);

	pipe(pipefd);
	write(pipefd[1], "XYZ", 3);
	close(pipefd[1]);
	lib_ret = read(pipefd[0], lib_buf, 5);
	lib_buf[lib_ret] = 0;
	close(pipefd[0]);

	(ft_ret == lib_ret && strcmp(ft_buf, lib_buf) == 0) ? PASS : FAIL;

	printf("bad fd:  ");
	errno = 0; ft_ret = ft_read(-1, ft_buf, 10); ft_err = errno;
	errno = 0; lib_ret = read(-1, lib_buf, 10);   lib_err = errno;
	(ft_ret == lib_ret && ft_err == lib_err)
		? printf(" ret=%d errno=%d OK\n", ft_ret, ft_err)
		: printf(" ft(ret=%d,errno=%d) lib(ret=%d,errno=%d) FAIL\n",
			ft_ret, ft_err, lib_ret, lib_err);
}

/* -------------------------------------------------------------------------- */
/* ft_strdup                                                                   */
/* -------------------------------------------------------------------------- */

static void	test_strdup(void)
{
	char	*ft_ret;
	char	*lib_ret;

	printf("\n=== ft_strdup ===\n");

	ft_ret = ft_strdup("hello world");
	lib_ret = strdup("hello world");
	printf("strdup:       ft=\"%s\" lib=\"%s\"",
		ft_ret, lib_ret);
	(ft_ret && lib_ret && strcmp(ft_ret, lib_ret) == 0) ? PASS : FAIL;
	free(ft_ret);
	free(lib_ret);

	ft_ret = ft_strdup("");
	lib_ret = strdup("");
	printf("empty:        ft=\"%s\" lib=\"%s\"",
		ft_ret, lib_ret);
	(ft_ret && lib_ret && strcmp(ft_ret, lib_ret) == 0) ? PASS : FAIL;
	free(ft_ret);
	free(lib_ret);
}

/* -------------------------------------------------------------------------- */
/* main                                                                        */
/* -------------------------------------------------------------------------- */

int	main(void)
{
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
	printf("\n=== all tests done ===\n");
	return (0);
}
