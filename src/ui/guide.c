/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:09:12 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 17:54:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			draw_paragraph(t_app *app, char *text, int xpos,
				int ypos)
{
	char	**split_text;
	int		i;

	if (!text || (split_text = ft_strsplit(text, '\n')) == NULL)
		return ;
	i = 0;
	while (split_text[i])
	{
		mlx_string_put(app->mlx, app->window->mlx_wdw, xpos,
			ypos + i * 20, app->window->ui_color, split_text[i]);
		ft_strdel(&split_text[i++]);
	}
	free(split_text);
}
