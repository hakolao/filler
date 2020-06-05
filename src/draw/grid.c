/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:35:03 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/05 14:50:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	draw_grid(t_app *app, t_rect *bounds, int cols, int rows)
{
	int		y;
	int		x;
	int		y_padding;
	int		x_padding;
	t_rect	cell;

	y_padding = 2;
	x_padding = 2 * ASPECT_RATIO;
	y = bounds->y;
	int i = 0;
	while (y < bounds->y + bounds->h && y >=0 && y < app->window->screen_height)
	{
		x = bounds->x;
		while (x < bounds->x + bounds->w && x >=0 && x < app->window->screen_width)
		{
			cell = (t_rect){
				.w = bounds->w / cols - x_padding,
				.h = bounds->h * ASPECT_RATIO / rows - y_padding,
				.x = x + x_padding,
				.y = y + y_padding};
			//ToDo: If empty, draw rectangle
			//ToDo: Else, draw game piece
			draw_rectangle(app, &cell, COLOR(100, 100, 100, 0));
			//ToDo: Define game piece color based on which player it is
			// draw_game_piece(app, &cell, COLOR(255, 0, 0, 0));
			x += cell.w + x_padding;
		}
		y += cell.y + y_padding;
	}
}
