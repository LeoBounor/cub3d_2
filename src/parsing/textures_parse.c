/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollon <jcollon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 10:07:01 by Leo               #+#    #+#             */
/*   Updated: 2023/06/13 14:45:28 by jcollon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_texture	init_texture(t_game *game, char *texture_path)
{
	t_texture	new;

	new.texture = mlx_xpm_file_to_image(game->mlx, texture_path, \
	&new.width_img, &new.height_img);
	if (!new.texture)
		if (clear_textures(game))
			return (free(texture_path), ft_err_map("Error loading texture\n", \
			game->fd_str, game), new);
	new.texture_addr = mlx_get_data_addr(new.texture, \
	&new.bits_per_pixel, &new.line_length, &new.endian);
	new.bits_per_pixel /= 8;
	free(texture_path);
	return (new);
}

void	load_texture(t_game *game, t_texture *texture, int *i)
{
	int	tmp;

	if (texture->texture != NULL && clear_textures(game))
		ft_err_map("Too many texture parameters\n", game->fd_str, game);
	*i += 3;
	skip_to_next_word(game->fd_str, i);
	tmp = *i;
	skip_to_eol_or_eof(game->fd_str, i);
	if (game->fd_str[*i] != '\n')
		*i -= 1;
	while ((game->fd_str[*i] == ' ' || game->fd_str[*i] == '\t') && *i > tmp)
		*i -= 1;
	*texture = init_texture(game, ft_substr(game->fd_str, tmp, *i - tmp + 1));
}
