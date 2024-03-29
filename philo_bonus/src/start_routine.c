/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:49:42 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/28 16:29:58 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	checkdeath_loop(t_pdata *pdata)
{
	static int		i = -1;
	struct timeval	cur;
	uint64_t		time;

	gettimeofday(&cur, NULL);
	time = (cur.tv_sec - pdata->start.tv_sec) * 1e6
		+ cur.tv_usec - pdata->start.tv_usec;
	if (time > pdata->data.tdie + pdata->meal.lasteat)
	{
		printp(time, pdata->n, DIE);
		while (++i < pdata->data.nphilo)
			if (i != pdata->n)
				sem_wait(pdata->run_n[i]);
		sem_post(pdata->end);
		i = -1;
		while (++i < pdata->data.nphilo)
			sem_post(pdata->eating);
		return (1);
	}
	return (0);
}

static void	*checkdeath(void *pdata_)
{
	t_pdata			*pdata;

	pdata = pdata_;
	while (1)
	{
		sem_wait(pdata->run);
		sem_wait(pdata->run_n[pdata->n]);
		if (pdata->data.end)
		{
			sem_post(pdata->run_n[pdata->n]);
			sem_post(pdata->run);
			return (0);
		}
		if (checkdeath_loop(pdata))
		{
			return (0);
		}
		sem_post(pdata->run_n[pdata->n]);
		sem_post(pdata->run);
		usleep(1000);
	}
}

static void	*start_routine_thread(void *pdata_)
{
	t_pdata			*pdata;

	pdata = pdata_;
	sem_wait(pdata->run);
	sem_post(pdata->run);
	routine(pdata, pdata->n, pdata->run_n[pdata->n], pdata->run);
	return (0);
}

static inline void	wait_clean(t_pdata *pdata)
{
	int	i;

	i = 0;
	sem_post(pdata->eating);
	sem_wait(pdata->end);
	pdata->data.end = 1;
	while (i < pdata->data.nphilo * 2)
	{
		sem_post(pdata->run_n[pdata->n]);
		i++;
	}
	sem_post(pdata->run);
	sem_post(pdata->run);
	sem_post(pdata->end);
	pthread_join(pdata->thread[0], NULL);
	pthread_join(pdata->thread[1], NULL);
	free_philo(pdata);
	exit(0);
}

void	start_routine(t_pdata *pdata)
{
	if (pdata->data.eatstop && pdata->data.neat == 0)
	{
		sem_post(pdata->eating);
		free_philo(pdata);
		exit(0);
	}
	if (pthread_create(pdata->thread + 1, NULL, &checkdeath, pdata))
	{
		ft_perror("Error while starting thread\n");
		dec_sems_except(pdata, pdata->n);
		sem_post(pdata->eating);
		sem_post(pdata->end);
		clean_exit(pdata, 1);
	}
	if (pthread_create(pdata->thread, NULL, &start_routine_thread, pdata))
	{
		ft_perror("Error while starting thread\n");
		dec_sems_except(pdata, pdata->n);
		sem_post(pdata->eating);
		pdata->data.end = 1;
		sem_post(pdata->end);
		pthread_join(pdata->thread[1], NULL);
		clean_exit(pdata, 1);
	}
	wait_clean(pdata);
}
