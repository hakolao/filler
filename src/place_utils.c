/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:37:24 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/02 15:21:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		w_extra(t_piece *piece, enum e_alignment alignment)
{
	int		x;
	int		y;

	if (alignment == left)
	{
		x = -1;
		while (++x < piece->width)
		{
			y = -1;
			while (++y < piece->height)
				if (piece->cells[y][x].id == UNPLACED)
					return (x);
		}
	}
	x = piece->width;
	while (--x >= 0)
	{
		y = piece->height;
		while (--y >= 0)
			if (piece->cells[y][x].id == UNPLACED)
				return (piece->width - x);
	}
	return (x);
}

int		h_extra(t_piece *piece, enum e_alignment alignment)
{
	int		x;
	int		y;

	if (alignment == top)
	{
		y = -1;
		while (++y < piece->height)
		{
			x = -1;
			while (++x < piece->width)
				if (piece->cells[y][x].id == UNPLACED)
					return (y);
		}
	}
	y = piece->height;
	while (--y >= 0)
	{
		x = piece->width;
		while (--x >= 0)
			if (piece->cells[y][x].id == UNPLACED)
				return (piece->height - y);
	}
	return (y);
}

int		distance(int *pos, int *target)
{
	return (ft_sqrt((pos[0] - target[0]) * (pos[0] - target[0]) +
		(pos[1] - target[1]) * (pos[1] - target[1])));
}

int		*mass_center(t_app *app, int *com, int player)
{
	int		x;
	int		y;
	int		count;

	y = -1;
	count = 0;
	while (++y < app->board->height)
	{
		x = -1;
		while (++x < app->board->width)
		{
			if (app->board->cells[y][x].id == player)
			{
				com[0] += x;
				com[1] += y;
				count++;
			}
		}
	}
	com[0] /= count;
	com[1] /= count;
	return (com);
}

int		distance_from_enemy(t_app *app, int *pos)
{
	int		enemy;
	int		x;
	int		y;
	int		min_dist;
	int		dist;

	enemy = app->is_player1 ? PLAYER_2 : PLAYER_1;
	y = -1;
	min_dist = INT32_MAX;
	while (++y < app->board->height)
	{
		x = -1;
		while (++x < app->board->width)
		{
			if (app->board->cells[y][x].id == enemy)
			{
				dist = distance(pos, (int[2]){x, y});
				if (dist <= min_dist)
					min_dist = dist;
			}
		}
	}
	return (min_dist);
}
