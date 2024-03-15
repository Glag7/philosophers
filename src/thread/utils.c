/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:58:04 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/14 18:02:03 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread/philo.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_perror(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	write(2, s, len);
}
