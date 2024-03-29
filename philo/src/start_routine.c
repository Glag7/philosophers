/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:31:55 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/21 18:32:13 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_)
{
	t_philo		*philo;
	t_pdata		*pdata;
	uint16_t	n;

	philo = philo_;
	pdata = philo->pdata;
	n = philo->num;
	pthread_mutex_lock(&pdata->run);
	pthread_mutex_unlock(&pdata->run);
	if (pdata->data.end || (pdata->data.eatstop && pdata->data.neat == 0))
		return (0);
	pdata->meals[n].lasteat = 0;
	routine_loop(philo, pdata, n, pdata->start);
	return (philo);
}
