/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:45 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 22:34:27 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/Utils.hpp"
#include "Grid.hpp"
#include "Texture.hpp"
#include <algorithm>
#include <iostream>

Grid::Grid()
{
	std::copy(&startingGrid[0][0], &startingGrid[0][0] + 64, &_grid[0][0]);
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			sf::Sprite tile;
			sf::Sprite piece;
			tile.setPosition(x * 75 + PIECE_OFFSET_X, y * 75 + PIECE_OFFSET_Y);
			piece.setPosition(x * 75 + PIECE_OFFSET_X, y * 75 + PIECE_OFFSET_Y);
			tile.setScale(tile.getScale().x / 2, tile.getScale().y / 2);
			piece.setScale(piece.getScale().x / 2, piece.getScale().y / 2);
			if ((x + y) % 2 == 0)
				tile.setTexture(*Texture::getPieceTexture(Piece::EMPTY, WHITE), true);
			else
				tile.setTexture(*Texture::getPieceTexture(Piece::EMPTY, BLACK), true);
			_tiles.push_back(tile);
			_pieces.push_back(piece);
		}
	}
}

Grid::~Grid() {}

char (*Grid::getGrid())[8]
{
	return (_grid);
}

char Grid::getPieceAt(short x, short y) const
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return ('X');
	return (_grid[y][x]);
}

void Grid::render(sf::RenderWindow &window)
{
	int i;

	for (const auto &tile : _tiles)
		window.draw(tile);
	i = 0;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			Texture *tmp = Texture::getPieceTexture(_grid[y][x]);
			if (tmp)
			{
				_pieces[i].setTexture(*tmp, true);
				window.draw(_pieces[i]);
			}
			i++;
		}
	}
}

bool Grid::hasDanger(const std::pair<short, short> &pos, Player player)
{
	int x;
	int y;
	bool opponentPiece;

	for (const auto& [dx, dy] : directions)
	{
		x = pos.first;
		y = pos.second;
		while (x >= 0 && x < 8 && y >= 0 && y < 8)
		{
			x += dx;
			y += dy;
			if (!(x >= 0 && x < 8 && y >= 0 && y < 8))
				break;
			opponentPiece = Utils::isOpponentPiece(_grid[y][x], player);
			if (opponentPiece)
			{
				// Chess logic
				std::cout << "Found danger for player " << (player == WHITE ? "White" : "Black") << " at x " << x << " | y " << y << " | piece " << _grid[y][x] << std::endl;
				return (true);
			}
			else if (!opponentPiece && _grid[y][x] != '.')
				break;
		}
	}
	return (false);
}

bool Grid::checkCheck(const std::pair<short, short> &kingPos, Player player)
{
	short kingX = kingPos.first;
	short kingY = kingPos.second;

	for (short i = 0; i < 8; i++)
	{
		if (getPieceAt(kingX + knightRadius[i].first, kingY + knightRadius[i].second) == PIECE(KNIGHT, INVERT_PLAYER(player))
				|| hasDanger(kingPos, player))
			return (true);
	}
	return (false);
}

Player Grid::hasCheck()
{
	std::pair<short, short> whiteKingPos = Utils::getPosition(*this, KING, WHITE);
	std::pair<short, short> blackKingPos = Utils::getPosition(*this, KING, BLACK);

	return (checkCheck(whiteKingPos, WHITE) ? WHITE : checkCheck(blackKingPos, BLACK) ? BLACK : NONE);
}
