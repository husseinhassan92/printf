#inlude "main.h"

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

	if (format == NULL)
		return (-1);
	va_start(list, format);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			buffer[len++] = format[i++];
			total_len++;
		}
		else
		{
			i++;
			if (format[i] == '\0') /* handle single ending % */
			{
				va_end(list);
				free(buffer);
				return (-1);
			}
			if (format[i] == '%') /* handle double %'s */
			{
				buffer[len++] = format[i];
				total_len++;
			}
			else
			{
				f = get_func(format[i]); /* grab function */
				if (f == NULL)  /* handle fake id */
				{
					buffer[len++] = '%'; total_len++;
					buffer[len++] = format[i]; total_len++;
				}
				else /* return string, copy to buffer */
				{
					str = f(list);
					if (str == NULL)
					{
						va_end(list);
						free(buffer);
						return (-1);
					}
					if (format[i] == 'c' && str[0] == '\0')
					{
						len = check_buffer_overflow(buffer, len);
						buffer[len++] = '\0';
						total_len++;
					}
					j = 0;
					while (str[j] != '\0')
					{
						len = check_buffer_overflow(buffer, len);
						buffer[len++] = str[j];
						total_len++; j++;
					}
					free(str);
				}
			}
			i++;
		}
	}
	return (total_len);
}
int main(void)
{
	_printf("\n\n\nHere's some examples of what you could do with this custom_printf function!\n\n\n");
	sleep(1);
	_printf("\nPrinting Strings, Characters, and Numbers...... %s %c%drld\n\n", "Hello", 'W', 0);
	return (0);
}
