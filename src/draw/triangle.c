/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 23:33:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/05 00:42:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static double	sign(t_triangle *triangle)
{
	return (triangle->a.x - triangle->c.x) * (triangle->b.y - triangle->c.y) -
			(triangle->b.x - triangle->c.x) * (triangle->a.y - triangle->c.y);
}

int				point_in_triangle(t_point *point, t_triangle *triangle)
{
	double	d1;
	double	d2;
	double	d3;
	int		has_neg;
	int		has_pos;

	d1 = sign(&(t_triangle){.a = *point, .b = triangle->a, .c = triangle->b});
	d2 = sign(&(t_triangle){.a = *point, .b = triangle->b, .c = triangle->c});
	d3 = sign(&(t_triangle){.a = *point, .b = triangle->c, .c = triangle->a});
	has_neg = (d1 < 0.) || (d2 < 0.) || (d3 < 0.);
	has_pos = (d1 > 0.) || (d2 > 0.) || (d3 > 0.);
	return (!(has_neg && has_pos));
}

void			draw_triangle(t_app *app, t_triangle *triangle, int color)
{
	int		pixel;
	int		y_min;
	int		y_max;
	int		x_min;
	int		x_max;
	int		y;
	int		x;

	y_min = ft_min_double((double[3]){triangle->a.y,
		triangle->b.y, triangle->c.y}, 3);
	y_max = ft_max_double((double[3]){triangle->a.y,
		triangle->b.y, triangle->c.y}, 3);
	x_min = ft_min_double((double[3]){triangle->a.x,
			triangle->b.x, triangle->c.x}, 3);
	x_max = ft_max_double((double[3]){triangle->a.x,
		triangle->b.x, triangle->c.x}, 3);
	y = y_min;
	while (y < y_min + y_max && y >= 0 && y < app->window->screen_height)
	{
		x = x_min;
		while (x < x_min + x_max && x >= 0 && x < app->window->screen_width)
		{
			if (point_in_triangle(&(t_point){.x = x, .y = y}, triangle))
			{
				pixel = y * app->window->line_bytes + x * 4;
				app->window->frame_buf[pixel] = BLUE(color);
				app->window->frame_buf[pixel + 1] = GREEN(color);
				app->window->frame_buf[pixel + 2] = RED(color);
				app->window->frame_buf[pixel + 3] = ALPHA(color);
			}
			x++;
		}
		y++;
	}
}
