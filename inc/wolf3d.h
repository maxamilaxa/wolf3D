/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:34:37 by mkopiika          #+#    #+#             */
/*   Updated: 2019/07/28 21:55:57 by mkopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include "SDL2/SDL.h"
# include "SDL2_image/SDL_image.h"
# include "SDL2_mixer/SDL_mixer.h"

# define W				1200
# define H				800
# define MD				400

# define RF				0x96e1ff
# define FLR			0x241d1a

# define FAIL_ARGC		20
# define FAIL_MALLOC	21
# define FAIL_NAME		22
# define FAIL_MAZE		23
# define FAIL_SDL		24
# define FAIL_INVAL		25

typedef struct		s_point_i
{
	int				x;
	int				y;
}					t_point_i;

typedef struct		s_point_d
{
	double			x;
	double			y;
}					t_point_d;

typedef struct		s_render
{
	double			now;
	double			past;
	double			render;
	double			rottn;
}					t_render;

typedef struct		s_sdl
{
	SDL_Window		*win_ptr;
	SDL_Surface		*srf_ptr;
	SDL_Surface		**image;
	Mix_Music		*audio;
}					t_sdl;

typedef struct		s_valid
{
	char			*str;
	int				length;
	struct s_valid	*nxt;
	struct s_valid	*prv;
}					t_valid;

typedef struct		s_maze
{
	int				sz;
	int				is_area;
	int				is_play;
	int				sgn_t;
	char			**maze;
	char			sym_wl;
	char			sym_fr;
	char			sym_pl;
	t_point_d		pos_pl;
	t_point_d		dirc_pl;
	t_point_d		proj_pl;
}					t_maze;

typedef struct		s_var_ray
{
	double			win_x;
	double			fsh;
	int				hig_w;
	int				offcut_s;
	t_point_i		maze_cor;
	t_point_i		from_to;
	t_point_i		move;
	t_point_d		pos_pl;
	t_point_d		dirc_pl;
	t_point_d		proj_pl;
	t_point_d		ray_d;
	t_point_d		delta;
	t_point_d		offcut;
}					t_var_ray;

typedef struct		s_var_tx
{
	double			x_bl;
	int				*d_srf;
	int				*d_img;
	int				z;
	t_point_i		size;
	t_point_i		txtr;
}					t_var_tx;

typedef struct		s_sign
{
	int				up;
	int				down;
	int				w;
	int				a;
	int				d;
	int				s;
	int				sh;
	int				rgt;
	int				lft;
}					t_sign;

typedef struct		s_data
{
	t_sdl			sdl;
	t_valid			*lst;
	t_maze			maze;
	t_sign			sgn;
}					t_data;

void				get_error(int fail);
void				game_loop(t_data *data);
void				maze_validation(int fd, t_data *data);
void				raycast_alg(t_data *data);
void				put_texture(int ray, t_var_ray *r, t_sdl *sdl, t_maze m);
void				key_events(t_sign sgn, t_maze *m, t_render *t);

#endif
