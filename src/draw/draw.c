/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 17:05:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			place_thread_frames(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		mlx_put_image_to_window(scene->mlx, scene->mlx_wdw,
			scene->thread_params[i]->frame, 0, i * HEIGHT / THREADS);
		i++;
	}
}

int					draw(t_scene *scene)
{
	mlx_clear_window(scene->mlx, scene->mlx_wdw);
	// Draw here
	//
	place_thread_frames(scene);
	draw_ui(scene);
	scene->redraw = FALSE;
	return (1);
}
