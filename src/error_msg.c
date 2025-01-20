/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:07:02 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/20 15:22:19 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_msg(char *message)
{
	ft_putendl_fd("ERROR", 2);
	ft_putendl_fd(message, 2);
}
