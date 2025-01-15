/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 13:36:25 by rshaheen      #+#    #+#                 */
/*   Updated: 2023/12/02 16:49:52 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_str(char *str, size_t *counter)
{
	char	*temp;

	if (!str)
		str = "(null)";
	temp = str;
	while (*temp != '\0')
	{
		ft_c(*temp, counter);
		temp++;
	}
}
