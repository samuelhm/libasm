#include <stdio.h>
#include <stdlib.h>
extern int		ft_strlen(const char *s);
extern char		*ft_strcpy(char *dest, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);
extern int		ft_write(int fd, const void *buf, size_t count);
extern int		ft_read(int fd, void *buf, size_t count);
extern char		*ft_strdup(const char *s);

int main(void)
{
	int a = ft_strlen("Hello, World!");
	printf("Length of string: %d\n", a);
	char dest[100];
	char *result = ft_strcpy(dest, "Hello, World!");
	printf("Copied string: %s\n", result);
	int cmp_result = ft_strcmp("Hello", "World");
	if (cmp_result < 0)
		printf("\"Hello\" is less than \"World\"\n");
	else if (cmp_result > 0)
		printf("\"Hello\" is greater than \"World\"\n");
	else
		printf("\"Hello\" is equal to \"World\"\n");
	int write_result = ft_write(1, "Hello, World!\n", 14);
	printf("Bytes written: %d\n", write_result);
	int read_result = ft_read(0, dest, 100);
	printf("Bytes read: %d\n", read_result);
	char *dup_result = ft_strdup("Hello, World!");
	printf("Duplicated string: %s\n", dup_result);
	free(dup_result);
	return 0;
}
