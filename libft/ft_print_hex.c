/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hex.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 13:31:43 by rshaheen      #+#    #+#                 */
/*   Updated: 2023/11/24 21:12:45 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hex(unsigned long long num, size_t *counter, char *base)
{
	char	*str;

	str = NULL;
	str = ft_convert(num, base);
	if (str)
	{
		ft_str(str, counter);
		free(str);
	}
}
