/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:15:55 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/15 17:51:44 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread/philo.h"

static void	start_threads(t_pdata *pdata, t_philo *philo, uint16_t len)
{
	int	i;
	int	j;
	int	err;

	i = 0;
	while (i < len)
	{
		err = pthread_create(pdata->threads + i, NULL, &routine, philo + i);
		if (err)
		{
			ft_perror("Error : cannot create threads\n");
			pdata->data.end = ERR_THREAD;
			break ;
		}
		i++;
	}
	j = 0;
	while (j < i)
	{
		pthread_join(pdata->threads[j], NULL);
		j++;
	}
}

static void	init_struct(t_pdata *pdata, t_philo *philo, uint16_t len)
{
	int	i;

	memset(pdata->forks, 1, pdata->data.nphilo * sizeof(*pdata->forks));
	memset(pdata->meals, 0, pdata->data.nphilo * sizeof(*pdata->meals));
	memset(pdata->threads, 0, pdata->data.nphilo * sizeof(*pdata->threads));
	i = 0;
	while (i < len)
	{
		philo[i].pdata = pdata;
		philo[i].num = i;
		i++;
	}
}

int	start_philo(t_data *data)
{
	t_pdata	pdata;
	t_philo	*philo;

	pdata.data = *data;
	pdata.forks = malloc(pdata.data.nphilo * sizeof(*pdata.forks));
	pdata.meals = malloc(pdata.data.nphilo * sizeof(*pdata.meals));
	pdata.threads = malloc(pdata.data.nphilo * sizeof(*pdata.threads));
	philo = malloc(pdata.data.nphilo * sizeof(*philo));
	if (!pdata.forks || !pdata.meals || !pdata.threads || !philo)
		ft_perror("Error: epic malloc fail\n");
	else
	{
		init_struct(&pdata, philo, pdata.data.nphilo);
		start_threads(&pdata, philo, pdata.data.nphilo);
	}
	free(pdata.forks);
	free(pdata.meals);
	free(pdata.threads);
	free(philo);
	if (!pdata.forks || !pdata.meals || !pdata.threads || !philo)
		return (ERR_AINTNOWAY);
	if (pdata.data.end == ERR_THREAD)
		return (ERR_THREAD);
	return (0);
}
