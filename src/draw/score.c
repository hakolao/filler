/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:43:56 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/16 17:19:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			gen_letters(int letters[10][9][6])
{
	number_0(letters);
	number_1(letters);
	number_2(letters);
	number_3(letters);
	number_4(letters);
	number_5(letters);
	number_6(letters);
	number_7(letters);
	number_8(letters);
	number_9(letters);
}

static void			draw_letter(t_app *app, int x_pos, int y_pos, char digit)
{
	int		letters[10][9][6];
	int		x;
	int		y;
	int		c_height;
	int		c_width;

	if (!ft_isdigit(digit))
		return ;
	gen_letters(letters);
	y = -1;
	c_height = app->cell_size / 9;
	c_width = app->cell_size / 6;
	while (++y < 9)
	{
		x = -1;
		while (++x < 6)
		{
			if (letters[digit - 48][y][x])
				draw_rectangle(app, &(t_rect){
					.w = c_width, .h = c_height,
					.x = x_pos + x * c_width, .y = y_pos + y * c_height
				}, COLOR(255, 255, 255, 0));
		}
	}
}

static void			draw_score(t_app *app, int x_pos, int y_pos, char *score)
{
	int		x;
	int		y;
	int		len;
	int		i;

	len = ft_strlen(score);
	i = 0;
	y = y_pos;
	while (y < y_pos + app->cell_size)
	{
		x = x_pos;
		while (x < x_pos + app->cell_size * len)
		{
			draw_letter(app, x, y, score[i]);
			i++;
			x += app->cell_size;
		}
		y += app->cell_size;
	}
}

void				assign_ints(int ints[6], int *arr)
{
	ints[0] = arr[0];
	ints[1] = arr[1];
	ints[2] = arr[2];
	ints[3] = arr[3];
	ints[4] = arr[4];
	ints[5] = arr[5];
}

void				draw_scores(t_app *app)
{
	char	*score1;
	char	*score2;

	if (!(score1 = ft_itoa(app->player1_score)) ||
		!(score2 = ft_itoa(app->player2_score)))
		return ;
	draw_score(app,
		app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_1_cell_y,
		score1);
	draw_score(app,
		app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_2_cell_y,
		score2);
	ft_strdel(&score1);
	ft_strdel(&score2);
}
