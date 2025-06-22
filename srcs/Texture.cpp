/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:48:03 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 22:38:07 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Texture.hpp"
#include <cctype>

Texture::Texture(const std::string &filepath, bool smooth)
{
	FAILSAFE(_texture.loadFromFile(filepath), "texture");
	_texture.setSmooth(smooth);
	_texture.generateMipmap();
}

void Texture::loadPieces()
{
	
	std::string filename;
	std::string fileId;

	for (int i = 0; i < 14; i++)
	{
		filename = "resources/sprite/";
		fileId = texNames[i];
		fileId.append(".png");
		filename.append(fileId);
		pieceTextures.push_back(new Texture(filename));
	}
}

Texture *Texture::getPieceTexture(char piece)
{
	if (piece == '.')
		return (nullptr);
	for (int i = (!std::isupper(piece) ? 6 : 0); i < 12; i++)
	{
		if (texNames[i][1] == std::tolower(piece))
			return (pieceTextures[i]);
	}
	return (nullptr);
}

Texture *Texture::getPieceTexture(Piece piece, Player player)
{
	if (piece == EMPTY)
	{
		if (player == WHITE)
			return (pieceTextures[12]);
		else
			return (pieceTextures[13]);
	}
	size_t id = static_cast<size_t>(piece);
	if (player == BLACK)
		id += 6;
	if (pieceTextures.empty())
	{
		std::cerr << "Forgot to call Texture::loadPieces(). Exiting." << std::endl;
		exit(2);
	}
	if (id >= pieceTextures.size())
	{
		std::cerr << "Piece texture ID out of bounds (" << id << "). Falling back to 0." << std::endl;
		id = 0;
	}
	return (pieceTextures[id]);
}

void Texture::freePieces()
{
	for (size_t i = 0; i < pieceTextures.size(); i++)
		delete pieceTextures[i];
}
