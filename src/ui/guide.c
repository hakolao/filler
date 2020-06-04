/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guide.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 22:09:12 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 16:50:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char			*guide(void)
{
	char	*guide;

	if ((guide = ft_strdup("USAGE Keys:\n"
			"----------\nESC: Exit all\n(x): Exit window\n")) == NULL)
		return (NULL);
	return (guide);
}

void			draw_paragraph(t_scene *scene, char *text, int xpos,
				int ypos)
{
	char	**split_text;
	int		i;

	if (!text || (split_text = ft_strsplit(text, '\n')) == NULL)
		return ;
	i = 0;
	while (split_text[i])
	{
		mlx_string_put(scene->mlx, scene->mlx_wdw, xpos,
			ypos + i * 20, scene->ui_color, split_text[i]);
		ft_strdel(&split_text[i++]);
	}
	free(split_text);
}
