/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 22:38:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			place_thread_frames(t_app *app)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		mlx_put_image_to_window(app->window->mlx, app->window->mlx_wdw,
			app->thread_params[i]->frame, 0, i * HEIGHT / THREADS);
		i++;
	}
}

int					draw(t_app *app)
{
	mlx_clear_window(app->window->mlx, app->window->mlx_wdw);
	// Draw here
	//
	place_thread_frames(app);
	draw_ui(app);
	app->window->redraw = FALSE;
	return (1);
}
