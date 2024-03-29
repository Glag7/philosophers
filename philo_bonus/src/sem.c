/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:55:49 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/28 15:45:50 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sem_open_all(int n, sem_t **sems)
{
	int			i;
	static char	name[] = "/000_philo_run";

	i = 0;
	name[1] = '0';
	name[2] = '0';
	name[3] = '0';
	while (i < n)
	{
		sems[i] = sem_open(name, O_CREAT | O_EXCL, S_MOD, 1);
		if (name[3] == '9')
		{
			name[3] = '0';
			if (name[2] == '9')
			{
				name[2] = '0';
				name[1]++;
			}
			else
				name[2]++;
		}
		else
			name[3]++;
		i++;
	}
}

static void	sem_unlink_all(int n)
{
	int			i;
	static char	name[] = "/000_philo_run";

	i = 0;
	name[1] = '0';
	name[2] = '0';
	name[3] = '0';
	while (i < n)
	{
		sem_unlink(name);
		if (name[3] == '9')
		{
			name[3] = '0';
			if (name[2] == '9')
			{
				name[2] = '0';
				name[1]++;
			}
			else
				name[2]++;
		}
		else
			name[3]++;
		i++;
	}
}

static int	sem_checkall(int n, t_pdata *pdata)
{
	int	i;

	i = 0;
	if (pdata->forks == SEM_FAILED || pdata->eating == SEM_FAILED
		|| pdata->run == SEM_FAILED || pdata->end == SEM_FAILED
		|| pdata->pfork == SEM_FAILED)
		return (1);
	while (i < n)
	{
		if (pdata->run_n[i] == SEM_FAILED)
			return (1);
		i++;
	}
	return (0);
}

void	sem_close_all(t_pdata *pdata, int n)
{
	int	i;

	i = 0;
	if (pdata->forks != SEM_FAILED)
		sem_close(pdata->forks);
	if (pdata->pfork != SEM_FAILED)
		sem_close(pdata->pfork);
	if (pdata->eating != SEM_FAILED)
		sem_close(pdata->eating);
	if (pdata->run != SEM_FAILED)
		sem_close(pdata->run);
	if (pdata->end != SEM_FAILED)
		sem_close(pdata->end);
	while (i < n)
	{
		if (pdata->run_n[i] != SEM_FAILED)
			sem_close(pdata->run_n[i]);
		i++;
	}
}

int	init_sem(t_pdata *pdata)
{
	sem_unlink(FORKS);
	sem_unlink(PFORK);
	sem_unlink(RUN);
	sem_unlink(EATING);
	sem_unlink(END);
	pdata->forks = sem_open(FORKS, O_CREAT | O_EXCL, S_MOD, pdata->data.nphilo);
	pdata->pfork = sem_open(PFORK, O_CREAT | O_EXCL, S_MOD, 1);
	pdata->run = sem_open(RUN, O_CREAT | O_EXCL, S_MOD, 0);
	pdata->eating = sem_open(EATING, O_CREAT | O_EXCL, S_MOD, 0);
	pdata->end = sem_open(END, O_CREAT | O_EXCL, S_MOD, 0);
	sem_unlink(FORKS);
	sem_unlink(PFORK);
	sem_unlink(RUN);
	sem_unlink(EATING);
	sem_unlink(END);
	sem_unlink_all(pdata->data.nphilo);
	sem_open_all(pdata->data.nphilo, pdata->run_n);
	sem_unlink_all(pdata->data.nphilo);
	if (sem_checkall(pdata->data.nphilo, pdata))
	{
		ft_perror("Error while opening semaphores\n");
		free_philo(pdata);
		return (1);
	}
	return (0);
}
