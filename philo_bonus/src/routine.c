/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:51:27 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/28 16:15:56 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	try_eat(t_pdata *pdata, int n,
	sem_t *run_n, sem_t *run)
{
	struct timeval	cur;
	uint64_t		time;

	sem_wait(pdata->pfork);
	sem_wait(pdata->forks);
	sem_wait(pdata->forks);
	sem_post(pdata->pfork);
	sem_wait(run);
	sem_wait(run_n);
	if (pdata->data.end)
		return (1);
	gettimeofday(&cur, NULL);
	time = (cur.tv_sec - pdata->start.tv_sec) * 1e6
		+ cur.tv_usec - pdata->start.tv_usec;
	pdata->meal.lasteat = time;
	printp(time, n, FORK);
	printp(time, n, FORK);
	printp(time, n, EAT);
	sem_post(run_n);
	sem_post(run);
	usleep(pdata->data.teat);
	sem_post(pdata->forks);
	sem_post(pdata->forks);
	pdata->meal.neat += 1;
	return (0);
}

static inline int	try_sleep(t_pdata *pdata, int n,
	sem_t *run_n, sem_t *run)
{
	struct timeval	cur;
	uint64_t		time;

	sem_wait(run);
	sem_wait(run_n);
	if (pdata->data.end)
		return (1);
	gettimeofday(&cur, NULL);
	time = (cur.tv_sec - pdata->start.tv_sec) * 1e6
		+ cur.tv_usec - pdata->start.tv_usec;
	printp(time, n, SLEEP);
	sem_post(run_n);
	sem_post(run);
	usleep(pdata->data.tsleep);
	return (0);
}

void	routine(t_pdata *pdata, int n, sem_t *run_n, sem_t *run)
{
	struct timeval	cur;
	uint64_t		time;

	while (1)
	{
		if (try_eat(pdata, n, run_n, run))
			break ;
		if (pdata->data.eatstop && pdata->meal.neat == pdata->data.neat)
			sem_post(pdata->eating);
		if (try_sleep(pdata, n, run_n, run))
			break ;
		sem_wait(run);
		sem_wait(run_n);
		if (pdata->data.end)
			break ;
		gettimeofday(&cur, NULL);
		time = (cur.tv_sec - pdata->start.tv_sec) * 1e6
			+ cur.tv_usec - pdata->start.tv_usec;
		printp(time, n, THINK);
		sem_post(run_n);
		sem_post(run);
		usleep(500);
	}
	sem_post(run_n);
	sem_post(run);
}
