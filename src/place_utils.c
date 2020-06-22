/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:37:24 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/22 13:21:33 by ohakola          ###   ########.fr       */
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

int		is_closer(int *pos, int *other, int *target)
{
	return (distance(pos, target) < distance(other, target));
}
