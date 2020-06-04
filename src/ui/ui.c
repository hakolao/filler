/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 16:49:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void				draw_ui(t_scene *scene)
{
	char	*guidestr;

	if (!scene->show_guide)
		return ;
	if (!(guidestr = guide()))
		return ;
	draw_paragraph(scene, guidestr, 10, 30);
	ft_strdel(&guidestr);
}
