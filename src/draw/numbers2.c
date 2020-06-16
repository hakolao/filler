/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:24:20 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/16 17:18:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		number_5(int letters[10][9][6])
{
	assign_ints(letters[5][0], (int[6]){1, 1, 1, 1, 1, 1});
	assign_ints(letters[5][1], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[5][2], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[5][3], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[5][4], (int[6]){0, 1, 1, 1, 0, 0});
	assign_ints(letters[5][5], (int[6]){0, 0, 0, 0, 1, 0});
	assign_ints(letters[5][6], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[5][7], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[5][8], (int[6]){1, 1, 1, 1, 1, 0});
}

void		number_6(int letters[10][9][6])
{
	assign_ints(letters[6][0], (int[6]){0, 1, 1, 1, 1, 1});
	assign_ints(letters[6][1], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[6][2], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[6][3], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[6][4], (int[6]){1, 1, 1, 1, 1, 0});
	assign_ints(letters[6][5], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[6][6], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[6][7], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[6][8], (int[6]){0, 1, 1, 1, 1, 0});
}

void		number_7(int letters[10][9][6])
{
	assign_ints(letters[7][0], (int[6]){1, 1, 1, 1, 1, 1});
	assign_ints(letters[7][1], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[7][2], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[7][3], (int[6]){0, 0, 0, 0, 1, 0});
	assign_ints(letters[7][4], (int[6]){0, 0, 0, 1, 0, 0});
	assign_ints(letters[7][5], (int[6]){0, 0, 1, 0, 0, 0});
	assign_ints(letters[7][6], (int[6]){0, 1, 0, 0, 0, 0});
	assign_ints(letters[7][7], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[7][8], (int[6]){1, 0, 0, 0, 0, 0});
}

void		number_8(int letters[10][9][6])
{
	assign_ints(letters[8][0], (int[6]){0, 1, 1, 1, 1, 0});
	assign_ints(letters[8][1], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[8][2], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[8][3], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[8][4], (int[6]){1, 1, 1, 1, 1, 0});
	assign_ints(letters[8][5], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[8][6], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[8][7], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[8][8], (int[6]){0, 1, 1, 1, 1, 0});
}

void		number_9(int letters[10][9][6])
{
	assign_ints(letters[9][0], (int[6]){0, 1, 1, 1, 1, 0});
	assign_ints(letters[9][1], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[9][2], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[9][3], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[9][4], (int[6]){0, 1, 1, 1, 1, 1});
	assign_ints(letters[9][5], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[9][6], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[9][7], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[9][8], (int[6]){1, 1, 1, 1, 1, 0});
}
