/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:21:44 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/23 14:03:53 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	try_die(t_philo *philo, t_pdata *pdata,
	struct timeval start, uint16_t n)
{
	struct timeval	cur;
	uint64_t		time;

	while (1)
	{
		gettimeofday(&cur, NULL);
		time = (cur.tv_sec - start.tv_sec) * 1e6 + cur.tv_usec - start.tv_usec;
		if (philo->meal->lasteat + pdata->data.tdie < time)
		{
			pthread_mutex_lock(&pdata->run);
			if (pdata->data.end == 0 && pdata->eating)
				printp(time, n, DIE);
			pdata->data.end = 1;
			return (1);
		}
		pthread_mutex_lock(&philo->fork->mutex);
		if (!(philo->fork->clean ^ (n & 1)))
		{
			pthread_mutex_unlock(&philo->fork->mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->fork->mutex);
		usleep(100);
	}
}

static inline int	sleepp(t_philo *philo, t_pdata *pdata,
	uint64_t time, uint16_t n)
{
	pthread_mutex_lock(&pdata->run);
	if (pdata->data.end || pdata->eating == 0)
		return (1);
	printp(time, n, SLEEP);
	pthread_mutex_unlock(&pdata->run);
	if (time - philo->meal->lasteat + pdata->data.tsleep > pdata->data.tdie)
	{
		usleep(pdata->data.tdie - (time - philo->meal->lasteat));
		pthread_mutex_lock(&pdata->run);
		if (pdata->data.end == 0 && pdata->eating)
			printp(pdata->data.tdie + philo->meal->lasteat, n, DIE);
		pdata->data.end = 1;
		return (1);
	}
	usleep(pdata->data.tsleep);
	time += pdata->data.tsleep;
	pthread_mutex_lock(&pdata->run);
	if (pdata->data.end || pdata->eating == 0)
		return (1);
	printp(time, n, THINK);
	pthread_mutex_unlock(&pdata->run);
	return (0);
}

static inline int	eatp(t_philo *philo, t_pdata *pdata,
	uint64_t time, uint16_t n)
{
	pthread_mutex_lock(&pdata->run);
	if (pdata->data.end || pdata->eating == 0)
		return (1);
	printp(time, n, FORK);
	printp(time, n, FORK);
	printp(time, n, EAT);
	pthread_mutex_unlock(&pdata->run);
	if (pdata->data.teat >= pdata->data.tdie)
	{
		usleep(pdata->data.tdie);
		pthread_mutex_lock(&pdata->run);
		if (pdata->data.end == 0 && pdata->eating)
			printp(time + pdata->data.tdie, n, DIE);
		pdata->data.end = 1;
		return (1);
	}
	usleep(pdata->data.teat);
	if (n & 1)
		pthread_mutex_lock(&philo->fork->mutex);
	pthread_mutex_lock(&philo->nfork->mutex);
	if (!(n & 1))
		pthread_mutex_lock(&philo->fork->mutex);
	philo->fork->clean ^= 1;
	philo->nfork->clean ^= 1;
	return (0);
}

static inline void	finish_meal(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork->mutex);
	pthread_mutex_unlock(&philo->nfork->mutex);
	philo->meal->neat++;
}

void	routine_loop(t_philo *philo, t_pdata *pdata,
	uint16_t n, struct timeval start)
{
	struct timeval	cur;
	uint64_t		time;

	while (1)
	{
		if (try_die(philo, pdata, start, n))
			break ;
		gettimeofday(&cur, NULL);
		time = (cur.tv_sec - start.tv_sec) * 1e6 + cur.tv_usec - start.tv_usec;
		philo->meal->lasteat = time;
		if (eatp(philo, pdata, time, n))
			break ;
		finish_meal(philo);
		gettimeofday(&cur, NULL);
		time = (cur.tv_sec - start.tv_sec) * 1e6 + cur.tv_usec - start.tv_usec;
		if (pdata->data.eatstop && pdata->meals[n].neat == pdata->data.neat)
		{
			pthread_mutex_lock(&pdata->run);
			pdata->eating--;
			pthread_mutex_unlock(&pdata->run);
		}
		if (sleepp(philo, pdata, time, n))
			break ;
	}
	pthread_mutex_unlock(&pdata->run);
}
