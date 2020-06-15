/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:10:10 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 18:10:48 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			init_new_cell(t_cell *cell, int x, int y)
{
	cell->color = EMPTY_COLOR;
	cell->x = x;
	cell->y = y;
	cell->id = EMPTY;
}

int				parse_dimensions(int *height, int *width, int i, char *line)
{
	*height = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
	*width = ft_atoi(line + i);
	return (TRUE);
}
