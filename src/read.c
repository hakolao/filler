/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/09 13:15:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	read_map(t_app *app)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(1, &line)) == TRUE)
	{
		if (!read_map_line())
			return (FALSE);
		ft_strdel(&line);
	}
	if (ret == FALSE)
	{
		//At the end
	}
	ft_strdel(&line);
	return (TRUE);
}

static int	read_players(t_app *app)
{
	
}

int			*serialize_board(t_app *app)
{
	if (!(app->board = malloc(sizeof(*app->board))))
		return (FALSE);
	if (!read_players(app))
		return (FALSE);
	if (!read_map(app))
		return (FALSE);
	return (TRUE);
}