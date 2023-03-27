#include "main.h"
/**
 * check_buffer_overflow - if writing over buffer space,
 * print everything then revert length back to 0 to write at buffer start
 * @buffer: buffer holding string to print
 * @len: position in buffer
 * Return: length position
 */
int check_buffer_overflow(char *buffer, int len)
{
	if (len > 1020)
	{
		write(1, buffer, len);
		len = 0;
	}
	return (len);
}
/**
 * _printf - mini printf version
 * @format: initial string with all identifiers
 * Return: strings with identifiers expanded
 */
int _printf(const char *format, ...)
{
	int len = 0, total_len = 0, i = 0, j = 0;
	va_list list;
	char *buffer, *str;
	char* (*f)(va_list);

	buffer = create_buffer();
	va_start(list, format);
	if (format[i] != '%') /* copy format into buffer until '%' */
	{
		buffer[len++] = format[i++];
		total_len++;
	}
	else /* if %, find function */
	{
		i++;
		if (format[i] == '%') /* handle double %'s */
		{
			buffer[len++] = format[i];
			total_len++;
		}
		else
		{
			f = get_func(format[i]); /* grab function */
			str = f(list);
			if (format[i] == 'c' && str[0] == '\0')
			{
				buffer[len++] = '\0';
				total_len++;
			}
				j = 0;
				while (str[j] != '\0')
				{
					buffer[len++] = str[j];
					total_len++;
					j++;
				}
				free(str);
		}
	}
	write_buffer(buffer, len, list);
	return (total_len);
}
