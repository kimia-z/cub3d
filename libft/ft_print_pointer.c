/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pointer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 17:23:11 by rshaheen      #+#    #+#                 */
/*   Updated: 2023/12/02 17:17:18 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdint.h>

void	ft_pointer(void *ptr, size_t *counter)
{
	unsigned long long	ptr_adrs;
	char				*str;

	if (ptr == NULL)
	{
		ft_str("(nil)", counter);
		return ;
	}
	ptr_adrs = (unsigned long long)ptr;
	str = NULL;
	if (ptr_adrs)
	{
		ft_str("0x", counter);
		str = ft_convert(ptr_adrs, HEX_LOW_BASE);
	}
	if (str)
	{
		ft_str(str, counter);
		free(str);
	}
}
