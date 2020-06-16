/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/16 14:46:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void				draw_paragraph(t_app *app, char *text, int xpos,
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

void				draw_texts(t_app *app)
{
	if (app->board != NULL)
		draw_scores(app);
	if (app->is_finished)
		draw_paragraph(app, "GAME OVER!",
		app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_2_cell_y + 2 * app->cell_size);
}
