/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/25 15:39:48 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/03/25 15:43:21 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atol(const char *nptr)
{
	int				i;
	long			sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr++ - '0');
	}
	return (sign * result);
}
