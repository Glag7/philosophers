/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:58:04 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/28 15:48:47 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	free_philo(t_pdata *pdata)
{
	sem_close_all(pdata, pdata->data.nphilo);
	free(pdata->proc);
	free(pdata->run_n);
}

void	gettimeofday_adjust(struct timeval *tim, int nphilo)
{
	gettimeofday(tim, NULL);
	if (nphilo >= 175)
	{
		tim->tv_sec += tim->tv_usec >= 990000;
		if (tim->tv_usec < 990000)
			tim->tv_usec += 10000;
		else
			tim->tv_usec -= 990000;
	}
	else if (nphilo >= 140)
	{
		tim->tv_sec += tim->tv_usec >= 993000;
		if (tim->tv_usec < 993000)
			tim->tv_usec += 7000;
		else
			tim->tv_usec -= 993000;
	}
	else if (nphilo >= 100)
	{
		tim->tv_sec += tim->tv_usec >= 997000;
		if (tim->tv_usec < 997000)
			tim->tv_usec += 3000;
		else
			tim->tv_usec -= 997000;
	}
}
