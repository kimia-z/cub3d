/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unsign.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:45:16 by rshaheen      #+#    #+#                 */
/*   Updated: 2023/12/05 19:30:12 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsign(unsigned int num, size_t *counter)
{
	char	*str;

	str = ft_convert(num, "0123456789");
	if (str)
	{
		ft_str(str, counter);
		free(str);
	}
}
