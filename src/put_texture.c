/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 19:07:23 by mkopiika          #+#    #+#             */
/*   Updated: 2019/07/28 19:42:15 by mkopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		print_column_pixels(t_var_ray *r, t_var_tx p, int ray)
{
	int			y;
	Uint32		color;

	y = 0;
	while (y < r->from_to.x)
	{
		p.d_srf[(y * W) + ray] = RF;
		y++;
	}
	y = r->from_to.x;
	while (y < r->from_to.y)
	{
		p.z = y * 256 - H * 128 + r->hig_w * 128;
		p.txtr.y = ((p.z * p.size.y) / r->hig_w) / 256;
		color = p.d_img[p.size.y * p.txtr.y + p.txtr.x];
		p.d_srf[y * W + ray] = color;
		y++;
	}
	y = r->from_to.y;
	while (y < H)
	{
		p.d_srf[(y * W) + ray] = FLR;
		y++;
	}
}

void			select_texture(t_sdl *sdl, t_var_ray *r, t_var_tx *p, t_maze m)
{
	p->d_img = sdl->image[0 + m.sgn_t]->pixels;
	if (r->offcut_s == 1)
	{
		if ((r->ray_d.y < 0 && r->ray_d.x >= 0)
			|| (r->ray_d.y < 0 && r->ray_d.x < 0))
			p->d_img = sdl->image[1 + m.sgn_t]->pixels;
		if ((r->ray_d.y >= 0 && r->ray_d.x >= 0)
			|| (r->ray_d.y >= 0 && r->ray_d.x < 0))
			p->d_img = sdl->image[2 + m.sgn_t]->pixels;
	}
	if ((r->ray_d.y < 0 && r->ray_d.x >= 0)
		|| (r->ray_d.y >= 0 && r->ray_d.x >= 0))
		if (r->offcut_s == 0)
			p->d_img = sdl->image[3 + m.sgn_t]->pixels;
}

void			put_texture(int ray, t_var_ray *r, t_sdl *sdl, t_maze m)
{
	t_var_tx	p;

	p.size = (t_point_i){.x = 64, .y = 64};
	if (r->offcut_s == 0)
		p.x_bl = r->pos_pl.y + r->fsh * r->ray_d.y;
	else
		p.x_bl = r->pos_pl.x + r->fsh * r->ray_d.x;
	p.x_bl -= floor((p.x_bl));
	p.txtr.x = (int)(p.x_bl * (double)(p.size.x));
	if (r->offcut_s == 0 && r->ray_d.x > 0)
		p.txtr.x = p.size.x - p.txtr.x - 1;
	if (r->offcut_s == 1 && r->ray_d.y < 0)
		p.txtr.x = p.size.x - p.txtr.x - 1;
	p.d_srf = sdl->srf_ptr->pixels;
	select_texture(sdl, r, &p, m);
	print_column_pixels(r, p, ray);
}
