#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

int main()
{
	char   str[] = "abc\ndtd\ndd\0";
    char   *b;
    int    i = 0;

    b = ft_strchr(str,'d');
	b++;
    printf("%s\n", &b[i]);
}