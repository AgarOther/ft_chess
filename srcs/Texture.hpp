/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:48:14 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 22:32:03 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ft_chess.hpp"
#include "utils/Utils.hpp"

const std::string texNames[14] = {"wp", "wr", "wn", "wb", "wk", "wq",
										"bp", "br", "bn", "bb", "bk", "bq",
										"tileW", "tileB"};

class Texture
{
	public:
		Texture(const std::string &filepath, bool smooth = true);
		operator const sf::Texture&() const { return (_texture); }
		const sf::Texture *ptr() const { return (&_texture); }
		const sf::Texture tex() const { return (_texture); }

		static void loadPieces();
		static void freePieces();
		static Texture *getPieceTexture(Piece piece, Player player);
		static Texture *getPieceTexture(char piece);
	private:
		sf::Texture _texture;
};

static std::vector<Texture *> pieceTextures;
