#include "../shell.h"

/**
 * read_from_stdin - a function that reads a line from stdin
 * @line_buff: double pointer to the line buffer
 * @line_size: pointer to the line buffer size
 *
 * Return: number of characters read, or 0 if error occurs
 * Description:
 *		- Use a temporary buffer for reading a line from stdin.
 *		- When reading from stdin, the number of bytes read is the amount of
 *		  bytes specified in the LINE_BUFF_SIZE macro, minus 1 for a null byte.
 */
int read_from_stdin(char **line_buff, int *line_size)
{
	char tmp_buff[LINE_BUFF_SIZE] = {0};
	int bytes_read = READ_EOF, line_pos = 0;

	bytes_read = read(STDIN_FILENO, tmp_buff, LINE_BUFF_SIZE - 1);
	while (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		if (bytes_read >= (*line_size - line_pos))
		{
			*line_buff = _realloc(*line_buff, *line_size, *line_size + LINE_BUFF_SIZE);
			*line_size += LINE_BUFF_SIZE;
		}
		_memcpy(*line_buff + line_pos, tmp_buff, bytes_read);
		line_pos += bytes_read;
		if ((*line_buff)[line_pos - 1] == '\n')
		{
			(*line_buff)[line_pos - 1] = '\0';
			return (line_pos);
		}
		bytes_read = read(STDIN_FILENO, tmp_buff, LINE_BUFF_SIZE - 1);
	}
	return (bytes_read);
}

/**
 * read_from_file- a function that reads a line from a file
 * @fd: file descriptor
 * @line_buff: double pointer to the line buffer
 * @line_size: pointer to the line buffer size
 *
 * Return: number of characters read, or 0 if error occurs
 * Description:
 *		- Use a character as a buffer, for reading from a file
 *		- When reading from a file, we read character by character inorder to
 *		  find the newline character.
 */
int read_from_file(int fd, char **line_buff, int *line_size)
{
	char  ch;
	int bytes_read = READ_EOF, line_pos = 0;

	bytes_read = read(fd, &ch, 1);
	while (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		if (line_pos == *line_size - 1)
		{
			*line_buff = _realloc(*line_buff, *line_size, *line_size + LINE_BUFF_SIZE);
			*line_size += LINE_BUFF_SIZE;
		}
		(*line_buff)[line_pos++] = ch;
		if ((*line_buff)[line_pos - 1] == '\n')
		{
			(*line_buff)[line_pos - 1] = '\0';
			return (line_pos);
		}
		bytes_read = read(fd, &ch, 1);
	}
	return (bytes_read);
}

/**
 * read_line - a function that reads a line from a file descriptor
 * @fd: file descriptor
 * @line_buff: double pointer to the line buffer
 * @line_size: pointer to the line buffer size
 * @line_start: pointer to the next line start in the buffer
 * @line_pos: pointer to the next writing position in the buffer
 *
 * Return: number of characters read, or -1 if an error occured
 */
int read_line(int fd, char **line_buff, int *line_size,
		char **line_start, int *line_pos)
{
	int total_read = 0;

	if (fd == OPEN_ERR)
		return (READ_ERR);
	if (*line_buff == NULL)
	{
		*line_size = LINE_BUFF_SIZE;
		*line_buff = _realloc(*line_buff, 0, *line_size);
		if (*line_buff == NULL)
			return (READ_ERR);
		*line_start = *line_buff;
		*line_pos = 0;
	}
	total_read = read_line_buffer(fd, line_buff, line_size, line_start, line_pos);
	return (total_read);
}

/**
 * read_line_char - a function that reads a line one character at a time
 * @fd: file descriptor
 * @line_buff: double pointer to the line buffer
 * @line_size: pointer to the line buffer size
 *
 * Return: number of characters read, or -1 if an error occured
 * Description: The function terminates the last newline character, but also
 *              keep in mind that the newline character is counted as a byte
 *              read in the total number of bytes read.
 */
int read_line_char(int fd, char **line_buff, int *line_size)
{
	char ch;
	int bytes_read = READ_EOF, total_read = 0, pos = 0;

	bytes_read = read(fd, &ch, 1);
	while (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		if (pos == *line_size - 1)
		{
			*line_buff = _realloc(*line_buff, *line_size, *line_size + LINE_BUFF_SIZE);
			*line_size += LINE_BUFF_SIZE;
		}
		(*line_buff)[pos] = ch;
		total_read += bytes_read;
		if ((*line_buff)[pos] == '\n')
			break;
		++pos;
		bytes_read = read(fd, &ch, 1);
	}
	(*line_buff)[pos] = '\0';
	return (total_read);
}

/**
 * read_line_buffer - a function that reads a line by using a buffer to read
 *                    more than one character at a time.
 * @fd: file descriptor
 * @buff: double pointer to the line buffer
 * @size: pointer to the line buffer size
 * @start: pointer to the next line start in the buffer
 * @pos: pointer to the next writing position in the buffer
 *
 * Return: number of characters read, or -1 if an error occurs
 * Description:
 *       - The function uses a temporary buffer when using read system call,
 *         because using the allocated memory directly will cause memory errors
 */
int read_line_buffer(int fd, char **buff, int *size, char **start, int *pos)
{
	char tmp_buff[LINE_BUFF_SIZE] = {0}, *next_start, *end;
	int bytes_read = READ_EOF, total_read = 0;

	if (fd == OPEN_ERR)
		return (READ_ERR);
	if (*buff == NULL)
	{
		*size = LINE_BUFF_SIZE;
		*buff = _realloc(*buff, 0, *size);
		if (*buff == NULL)
			return (READ_ERR);
		*start = *buff;
		*pos = 0;
	}

	if (*start != *buff && **start != '\0')
	{
		end = _strchr(*start, '\n');
		if (end == NULL)
			end = _strchr(*start, '\0');
		total_read = end - *start + 1;
		next_start = *end == '\n' ? end + 1 : *buff;
		*pos = next_start == *buff ? 0 : *pos;
		*end = '\0';
		_strcpy(*buff, *start);
		*start = next_start;
		return (total_read);
	}

	bytes_read = read(fd, tmp_buff, LINE_BUFF_SIZE - 1);
	if (bytes_read >= *size - *pos)
	{
		*buff = _realloc(*buff, *size, *size + LINE_BUFF_SIZE);
		if (*buff == NULL)
			return (READ_ERR);
		*size += LINE_BUFF_SIZE;
	}
	_memcpy(*buff + *pos, tmp_buff, bytes_read);
	*pos += bytes_read;

	if (bytes_read != READ_EOF && bytes_read != READ_ERR)
	{
		end = _strchr(*start, '\n');
		if (end == NULL)
			end = _strchr(*start, '\0');
		total_read = end - *start + 1;
		next_start = *end == '\n' ? end + 1 : *buff;
		*pos = next_start == *buff ? 0 : *pos;
		*end = '\0';
		_strcpy(*buff, *start);
		*start = next_start;
		return (total_read);
	}
	return (total_read);
}
