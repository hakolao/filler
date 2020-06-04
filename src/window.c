/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:09:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 22:40:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int					scene_render_params(t_window *scene,
							void *mlx, void *mlx_wdw)
{
	scene->mlx = mlx;
	scene->mlx_wdw = mlx_wdw;
	scene->pixel_bits = 32;
	scene->line_bytes = scene->screen_width * 4;
	scene->pixel_endian = TRUE;
	scene->redraw = TRUE;
	scene->ui_color = UI_COLOR;
	return (TRUE);
}

t_window					*new_window(void *mlx)
{
	t_window		*scene;

	if (!(scene = (t_window*)malloc(sizeof(*scene))))
		return (NULL);
	scene->screen_width = WIDTH;
	scene->screen_height = HEIGHT;
	if (!(scene->mlx_wdw = mlx_new_window(mlx, scene->screen_width,
			scene->screen_height, "Filler")) ||
			!scene_render_params(scene, mlx, scene->mlx_wdw))
		return (NULL);
	scene->mlx = mlx;
	return (scene);
}
