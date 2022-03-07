/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:37:46 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/07 10:37:46 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error_exit_msg(void *ptr1, void *ptr2, char *msg)
{
	free(ptr1);
	free(ptr2);
	ft_printf("%s", msg);
	exit(1);
}
