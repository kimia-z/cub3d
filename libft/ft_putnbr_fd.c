/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:43:49 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/26 18:05:14 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_positive_number(int n, int fd)
{
	int	numdigits;
	int	temp;
	int	digit;

	numdigits = 1;
	temp = n;
	while (temp >= 10)
	{
		temp /= 10;
		numdigits *= 10;
	}
	temp = n;
	while (numdigits > 0)
	{
		digit = temp / numdigits;
		ft_putchar_fd(digit + '0', fd);
		temp %= numdigits;
		numdigits /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
		print_positive_number(n, fd);
	}
}

// int main()
// {
// 	ft_putnbr_fd(-15678, 1);
// }