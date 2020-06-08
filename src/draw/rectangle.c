/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 23:26:31 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/08 15:24:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		draw_rectangle(t_app *app, t_rect *rect, int color)
{
	int		pixel;
	int		y;
	int		x;

	y = rect->y;
	while (y < rect->y + rect->h && y >= 0 && y < app->window->screen_height)
	{
		x = rect->x;
		while (x < rect->x + rect->w && x >= 0 && x < app->window->screen_width)
		{
			pixel = y * app->window->line_bytes + x * 4;
			app->window->frame_buf[pixel] = BLUE(color);
			app->window->frame_buf[pixel + 1] = GREEN(color);
			app->window->frame_buf[pixel + 2] = RED(color);
			app->window->frame_buf[pixel + 3] = ALPHA(color);
			x++;
		}
		y++;
	}
}

void		draw_pyramid_shape(t_app *app, t_rect *rect, int color)
{
	t_point	center;

	center = (t_point){.x = rect->x + rect->w / 2, .y = rect->y + rect->h / 2};
	draw_triangle(app, &(t_triangle){
			.a = (t_point){.x = rect->x, .y = rect->y},
			.b = (t_point){.x = rect->x + rect->w, .y = rect->y}, .c = center},
		color);
	draw_triangle(app, &(t_triangle){
			.a = (t_point){.x = rect->x + rect->w, .y = rect->y},
			.b = (t_point){.x = rect->x + rect->w, .y = rect->y + rect->h},
			.c = center},
		COLOR(RED(color) * 4 / 5, GREEN(color) * 4 / 5,
				BLUE(color) * 4 / 5, ALPHA(color) * 4 / 5));
	draw_triangle(app, &(t_triangle){
			.a = (t_point){.x = rect->x + rect->w, .y = rect->y + rect->h},
			.b = (t_point){.x = rect->x, .y = rect->y + rect->h}, .c = center},
		COLOR(RED(color) * 3 / 5, GREEN(color) * 3 / 5,
				BLUE(color) * 3 / 5, ALPHA(color) * 3 / 5));
	draw_triangle(app, &(t_triangle){
			.a = (t_point){.x = rect->x, .y = rect->y + rect->h},
			.b = (t_point){.x = rect->x, .y = rect->y}, .c = center},
		COLOR(RED(color) * 2 / 5, GREEN(color) * 2 / 5,
				BLUE(color) * 2 / 5, ALPHA(color) * 2 / 5));
}
