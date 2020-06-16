/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:24:13 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/16 16:25:29 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		number_0(int letters[10][9][6])
{
	assign_ints(letters[0][0], (int[6]){0, 0, 1, 1, 0, 0});
	assign_ints(letters[0][1], (int[6]){0, 1, 0, 0, 1, 0});
	assign_ints(letters[0][2], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[0][3], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[0][4], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[0][5], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[0][6], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[0][7], (int[6]){0, 1, 0, 0, 1, 0});
	assign_ints(letters[0][8], (int[6]){0, 0, 1, 1, 0, 0});
}

void		number_1(int letters[10][9][6])
{
	assign_ints(letters[1][0], (int[6]){0, 0, 1, 1, 0, 0});
	assign_ints(letters[1][1], (int[6]){0, 0, 0, 1, 0, 0});
	assign_ints(letters[1][2], (int[6]){0, 0, 0, 1, 0, 0});
	assign_ints(letters[1][3], (int[6]){0, 0, 0, 1, 0, 0});
	assign_ints(letters[1][4], (int[6]){0, 0, 0, 1, 0, 0});
	assign_ints(letters[1][5], (int[6]){0, 0, 0, 1, 0, 0});
	assign_ints(letters[1][6], (int[6]){0, 0, 0, 1, 0, 0});
	assign_ints(letters[1][7], (int[6]){0, 0, 0, 1, 0, 0});
	assign_ints(letters[1][8], (int[6]){0, 0, 0, 1, 0, 0});
}

void		number_2(int letters[10][9][6])
{
	assign_ints(letters[2][0], (int[6]){0, 0, 1, 1, 1, 0});
	assign_ints(letters[2][1], (int[6]){0, 1, 0, 0, 0, 1});
	assign_ints(letters[2][2], (int[6]){1, 0, 0, 0, 0, 1});
	assign_ints(letters[2][3], (int[6]){0, 0, 0, 0, 1, 0});
	assign_ints(letters[2][4], (int[6]){0, 0, 1, 1, 0, 0});
	assign_ints(letters[2][5], (int[6]){0, 1, 0, 0, 0, 0});
	assign_ints(letters[2][6], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[2][7], (int[6]){1, 0, 0, 0, 0, 0});
	assign_ints(letters[2][8], (int[6]){1, 1, 1, 1, 1, 1});
}

void		number_3(int letters[10][9][6])
{
	assign_ints(letters[3][0], (int[6]){1, 1, 1, 1, 1, 0});
	assign_ints(letters[3][1], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[3][2], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[3][3], (int[6]){0, 0, 0, 0, 1, 0});
	assign_ints(letters[3][4], (int[6]){0, 0, 1, 1, 0, 0});
	assign_ints(letters[3][5], (int[6]){0, 0, 0, 0, 1, 0});
	assign_ints(letters[3][6], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[3][7], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[3][8], (int[6]){1, 1, 1, 1, 1, 0});
}

void		number_4(int letters[10][9][6])
{
	assign_ints(letters[4][0], (int[6]){0, 1, 0, 0, 0, 1});
	assign_ints(letters[4][1], (int[6]){0, 1, 0, 0, 0, 1});
	assign_ints(letters[4][2], (int[6]){0, 1, 0, 0, 0, 1});
	assign_ints(letters[4][3], (int[6]){0, 1, 0, 0, 0, 1});
	assign_ints(letters[4][4], (int[6]){0, 1, 1, 1, 1, 1});
	assign_ints(letters[4][5], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[4][6], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[4][7], (int[6]){0, 0, 0, 0, 0, 1});
	assign_ints(letters[4][8], (int[6]){0, 0, 0, 0, 0, 1});
}

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
