/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_num.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 17:16:56 by rshaheen      #+#    #+#                 */
/*   Updated: 2023/12/04 16:23:05 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_num(int num, size_t *counter)
{
	if (num == -2147483648)
	{
		ft_c('-', counter);
		ft_num((num / 10) * -1, counter);
		ft_c('8', counter);
	}
	else if (num < 0)
	{
		ft_c('-', counter);
		ft_num(-num, counter);
	}
	else
	{
		if (num > 9)
			ft_num((num / 10), counter);
		ft_c(('0' + num % 10), counter);
	}
}
