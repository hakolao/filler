/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/12 16:39:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "mlx.h"
# include <stdio.h>
# include <pthread.h>
# include "libft.h"

/*
** Key codes for event listening
*/
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_P 35
# define KEY_1 18
# define KEY_2 19
# define KEY_NUM_4 86
# define KEY_NUM_6 88
# define KEY_NUM_8 91
# define KEY_NUM_2 84
# define SCROLL_UP 5
# define SCROLL_DOWN 4
# define MOUSE_BUTTON_RIGHT 2
# define MOUSE_BUTTON_LEFT 1
# define MOUSE_BUTTON_MIDDLE 3
# define KEY_R 15
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_G 5
# define KEY_C 8
# define KEY_B 11
# define KEY_TAB 48
# define KEY_SHIFT 257
# define KEY_O 31

/*
** Color helpers
*/
# define CLAMP_0_255(color) (color > 255 ? 255 : color < 0 ? 0 : color)
# define ALPHA(a) ((a >> 24) & 255)
# define RED(r) ((r >> 16) & 255)
# define GREEN(g) ((g >> 8) & 255)
# define BLUE(b) (b & 255)
# define R(r) (CLAMP_0_255(r) & 255) << 16
# define G(g) (CLAMP_0_255(g) & 255) << 8
# define B(b) CLAMP_0_255(b) & 255
# define A(a) (CLAMP_0_255(a) & 255) << 24
# define COLOR(r, g, b, a) A(a) | R(r) | G(g) | B(b)
# define UI_COLOR COLOR(255, 255, 255, 0)
# define BACKGROUND_COLOR COLOR(0, 0, 0, 0)

# define WIDTH 1200
# define HEIGHT 1200
# define ASPECT_RATIO WIDTH / HEIGHT
# define THREADS 8

# define EMPTY -1
# define PLAYER_1 0
# define PLAYER_2 1
# define UNPLACED 2

# define PLAYER_1_COLOR COLOR(255, 0, 0, 0)
# define PLAYER_2_COLOR COLOR(0, 255, 0, 0)
# define EMPTY_COLOR COLOR(100, 100, 100, 0)


typedef struct		s_thread_params
{
	int					thread_i;
}					t_thread_params;

enum				e_strategy
{
	find_first
};

enum				e_alignment
{
	left,
	right,
	top,
	down
};

/*
** Scene contains all data the application needs inside its loop
*/

typedef struct		s_window
{
	int					id;
	void				*mlx_wdw;
	void				*frame;
	char				*frame_buf;
	int					screen_width;
	int					screen_height;
	int					pixel_bits;
	int					line_bytes;
	int					pixel_endian;
	int					redraw;
	int					ui_color;
	int					bg_color;
}					t_window;

typedef struct		s_cell
{
	int				x;
	int				y;
	int				color;
	int				id;
}					t_cell;

typedef struct		s_piece
{
	int				width;
	int				height;
	t_cell			**cells;
}					t_piece;

typedef struct		s_board
{
	int				width;
	int				height;
	t_cell			**cells;
}					t_board;

typedef struct		s_rect
{
	int				w;
	int				h;
	int				x;
	int				y;
}					t_rect;

typedef struct		s_app
{
	char				*name;
	t_window			*window;
	void				*mlx;
	int					show_guide;
	int					rows;
	int					cols;
	int					cell_size;
	int					player_1_cell_y;
	int					player_2_cell_y;
	int					player1_score;
	int					player2_score;
	char				*player1_name;
	char				*player2_name;
	int					is_player1;
	int					is_finished;
	enum e_strategy		strategy;
	t_piece				*current_piece;
	t_board				*board;
	t_rect				grid_bounds;
	t_rect				info_bounds;
	t_thread_params		**thread_params;
}					t_app;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_triangle
{
	t_point			a;
	t_point			b;
	t_point			c;
}					t_triangle;

/*
**	Window
*/

t_window			*new_window(t_app *app);

/*
** Input
*/

int					update_map(t_app *app);

/*
** Output
*/

int					place_piece(t_app *app);

/*
** Board
*/

int					init_new_piece(t_app *app, char *line);
int					init_new_board(t_app *app, char *line);
int					parse_board(t_app *app);

/*
** UI
*/

void				draw_paragraph(t_app *app, char *text, int xpos,
					int ypos);
void				draw_texts(t_app *app);
char				*guide(void);
void				draw_scores(t_app *app);

/*
** Draw
*/

int					draw(t_app *app);
void				draw_rectangle(t_app *app, t_rect *rect, int color);
void				draw_triangle(t_app *app, t_triangle *rect, int color);
void				draw_pyramid_shape(t_app *app, t_rect *rect, int color);
void				draw_info_panel(t_app *app);
void				draw_game(t_app *app);
int					set_grid_cell_render_dimensions(t_app *app);

/*
** Events
*/

int					handle_key_press(int key, void *param);
int					handle_key_release(int key, void *param);
int					handle_mouse_button_press(int key, int x, int y,
					void *param);
int					handle_mouse_button_release(int key, int x, int y,
					void *param);
int					handle_mouse_move(int x, int y, void *param);
int					handle_loop(void *params);
int					handle_exit_event(void *params);

/*
** Logging
*/

int					log_err(char *str, char *strerror);
int					log_perr(char *str);
void				debug_app(t_app *app);
void				debug_piece(t_piece *piece);
void				debug_board(t_board *board);
void				debug_board_piece_placing(t_board *board, t_piece *piece,
					int board_x, int board_y);

/*
** Threads
*/

void				work_parallel(int num_threads, void **thread_params,
					void (*worker_f)(void *params));
t_thread_params		**thread_params(t_app *app);

#endif
