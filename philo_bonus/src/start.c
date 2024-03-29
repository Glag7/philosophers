/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:15:55 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/28 16:13:41 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_philo(pid_t *proc, int n, int err)
{
	int	i;

	if (err)
		n = err - 1;
	i = 0;
	while (i < n)
	{
		waitpid(proc[i], 0, 0);
		i++;
	}
}

static void	wait_meals(t_pdata *pdata)
{
	int	i;

	if (!pdata->data.eatstop || !pdata->data.neat)
		return ;
	i = 0;
	while (i < pdata->data.nphilo)
	{
		sem_wait(pdata->eating);
		i++;
	}
	sem_wait(pdata->run);
	i = 0;
	while (i < pdata->data.nphilo)
	{
		sem_wait(pdata->run_n[i]);
		i++;
	}
	sem_post(pdata->end);
}

static void	flood_forks(t_pdata *pdata)
{
	int	i;

	i = 0;
	if (!(pdata->data.eatstop && pdata->data.neat == 0))
	{
		sem_wait(pdata->end);
		sem_post(pdata->end);
	}
	while (i < pdata->data.nphilo * 4)
	{
		sem_post(pdata->pfork);
		sem_post(pdata->forks);
		i++;
	}
}

static int	start_forks(t_pdata *pdata)
{
	int	i;

	i = -1;
	while (++i < pdata->data.nphilo)
	{
		pdata->n = i;
		pdata->proc[i] = fork();
		if (pdata->proc[i] == -1)
		{
			ft_perror("Error while forking\n");
			dec_sems(pdata, i);
			sem_post(pdata->end);
			return (i + 1);
		}
		if (pdata->proc[i] == 0)
			start_routine(pdata);
	}
	i = -1;
	while (++i < pdata->data.nphilo)
		sem_wait(pdata->eating);
	sem_post(pdata->run);
	wait_meals(pdata);
	flood_forks(pdata);
	return (0);
}

int	start_philo(t_data *data)
{
	t_pdata	pdata;
	int		err;

	pdata.meal = (t_meal){0, 0};
	pdata.data = *data;
	pdata.proc = malloc(sizeof(pid_t) * pdata.data.nphilo);
	pdata.run_n = malloc(sizeof(sem_t *) * pdata.data.nphilo);
	if (pdata.proc == NULL || pdata.run_n == NULL)
	{
		free(pdata.proc);
		free(pdata.run_n);
		ft_perror("Epic malloc fail\n");
		return (ERR_AINTNOWAY);
	}
	if (init_sem(&pdata))
		return (ERR_SEM);
	gettimeofday_adjust(&pdata.start, pdata.data.nphilo);
	err = start_forks(&pdata);
	wait_philo(pdata.proc, pdata.data.nphilo, err);
	free_philo(&pdata);
	if (err)
		return (ERR_FORK);
	return (0);
}
