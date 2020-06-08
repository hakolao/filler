/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:08:46 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/08 15:21:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				handle_exit_event(void *params)
{
	t_app		*app;

	app = (t_app*)params;
	mlx_destroy_window(app->mlx, app->window->mlx_wdw);
	exit(0);
	return (0);
}
