/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:12:03 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 22:58:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_thread_params				**thread_params(t_app *app)
{
	t_thread_params			**params;
	int						i;

	(void)app;
	if (!(params = malloc(sizeof(*params) * THREADS)))
		return (NULL);
	i = 0;
	while (i < THREADS)
	{
		if (!(params[i] = malloc(sizeof(**params))))
			return (NULL);
		i++;
	}
	return (params);
}

/*
** This function performs parallel work (worker_f), which takes in
** an array of thread params (size of thread_params should be the
** same as number of threads). For example, see draw_mandelbrot.
** After the work, threads are joined back.
*/

void						work_parallel(int num_threads, void **thread_params,
							void (*worker_f)(void *params))
{
	pthread_t				threads[num_threads];
	int						i;

	i = 0;
	while (i < num_threads)
	{
		if (pthread_create(&threads[i], NULL, (void*)worker_f,
			thread_params[i]))
			log_perr("Something went wrong in thread creation.");
		i++;
	}
	i = 0;
	while (i < num_threads)
		pthread_join(threads[i++], NULL);
}
