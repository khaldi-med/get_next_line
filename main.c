#include <fcntl.h>
#include <get_next_line.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5

char ft_get_line(char *str, int fd){
	char *buffer;
	int bit_read = 0;
	
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if(!buffer)
		return NULL;
	if(!str)
		str = ft_strdup("");
	²

	while((bit_read = read(fd, buffer, BUFFER_SIZE)){
		buffer[bit_read] = '\0';
		printf
	}
}
char *get_next_line(int fd){
	char *buffer;
	int bit_read = 0;
	if(!BUFFER_SIZE || read(fd, 0, 0) < 0)
		return NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if(!buffer)
		return NULL;

			
		
}


int	main(void)
{
	char	str[256];
	int		read_char;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	while ((read_char = read(fd, str, 5)))
	{
		str[read_char] = '\0';
		printf("red-> %s\n", str);
	}
	return (0);
}
