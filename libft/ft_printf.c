/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 17:29:36 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/04/24 17:11:29 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format(va_list ap, char *str, size_t *counter)
{
	if (*str == 'c')
		ft_c(va_arg(ap, int), counter);
	else if (*str == 's')
		ft_str(va_arg(ap, char *), counter);
	else if (*str == 'p')
		ft_pointer(va_arg(ap, void *), counter);
	else if (*str == 'i' || *str == 'd')
		ft_num(va_arg(ap, int), counter);
	else if (*str == 'u')
		ft_unsign(va_arg(ap, unsigned int), counter);
	else if (*str == 'x' || *str == 'X')
	{
		if (*str == 'X')
			ft_hex(va_arg(ap, unsigned int), counter, HEX_UPP_BASE);
		if (*str == 'x')
			ft_hex(va_arg(ap, unsigned int), counter, HEX_LOW_BASE);
	}
	else if (*str == '%')
		ft_c(*str, counter);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	size_t	counter;

	if (!str)
		return (0);
	counter = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_format(ap, (char *)str, &counter);
			if (*str == '\0')
				return (-1);
		}
		else
			ft_c(*str, &counter);
		str++;
	}
	va_end(ap);
	return (counter);
}

// #include "ft_printf.h"

// int	main(void)
// {
// char *s = "0yte\0rfghj";
// int myreturn = ft_printf("%%%%%%s\n");
// int realreturn = printf("%%%%%%s\n");
// printf("myreturn: %d\n", myreturn);
// printf("rereturn:%d\n", realreturn);

// myreturn = ft_printf("%s\n", s);
// realreturn = printf("%s\n", s);
// printf("myreturn: %d\n", myreturn);
// printf("rereturn:%d\n", realreturn);

// char ch = 'A';
// myreturn = ft_printf("myc: %c\n", ch);
// realreturn = printf("rec: %c\n", ch);
// printf("myreturn: %d\n", myreturn);
// printf("real returnval:%d\n", realreturn);

// int num = 34;
// myreturn = ft_printf("myIntiger: %d\n", num);
// realreturn = printf("reIntiger: %d\n", num);
// printf("myreturn: %d\n", myreturn);
// printf("realreturn:%d\n", realreturn);

//  void *ptr = (void*)0x123456;
// myreturn = ft_printf("myPointer: %p\n", ptr);
// realreturn = printf("rePointer: %p\n", ptr);
// printf("myreturn: %d\n", myreturn);
// printf("realreturn:%d\n", realreturn);

// unsigned int u_num = -123;
// myreturn = ft_printf("myUnsigned Integer: %u\n", u_num);
// realreturn = printf("reUnsigned Integer: %u\n", u_num);
// printf("myreturn: %d\n", myreturn);
// printf("realreturn:%d\n", realreturn);

// int hex_num = 24;
// myreturn = ft_printf("myHexadecimal low: %x\n", hex_num);
// realreturn = printf("reHexadecimal low: %x\n", hex_num);
// printf("myreturn: %d\n", myreturn);
// printf("realreturn:%d\n", realreturn);

// unsigned int hex_UP = 34 ;
// myreturn = ft_printf("myHexadecimal up: %X\n", hex_UP);
// realreturn = printf("reHexadecimal up: %X\n", hex_UP);
// printf("myreturn: %d\n", myreturn);
// printf("real returnval:%d\n", realreturn);
//  return 0;
// }