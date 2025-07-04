/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:45 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/23 22:22:06 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/Utils.hpp"
#include "Grid.hpp"
#include "Texture.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <iostream>

Grid::Grid()
{
	std::copy(&startingGrid[0][0], &startingGrid[0][0] + 64, &_grid[0][0]);
	for (short x = 0; x < 8; x++)
	{
		for (short y = 0; y < 8; y++)
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
	short i;

	for (const auto &tile : _tiles)
		window.draw(tile);
	i = 0;
	for (short x = 0; x < 8; x++)
	{
		for (short y = 0; y < 8; y++)
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

bool Grid::checkDirection(short x, short y, Player player, std::vector<std::pair<int, int>> dirs)
{
	short qx;
	short qy;

	for (const auto& [dqx, dqy] : dirs)
	{
		qx = x;
		qy = y;
		while (qx >= 0 && qx < 8 && qy >= 0 && qy < 8)
		{
			qx += dqx;
			qy += dqy;
			if (!(qx >= 0 && qx < 8 && qy >= 0 && qy < 8))
				break;
			if (_grid[qy][qx] != PIECE(KING, player) && _grid[qy][qx] != '.')
				break;
			if (_grid[qy][qx] != '.')
				return (true);
		}
	}
	return (false);
}

bool Grid::hasDanger(const std::pair<short, short> &pos, Player player)
{
	short x;
	short y;
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
				Piece piece = Utils::getPiece(_grid[y][x]);
				switch (static_cast<short>(piece))
				{
					case PAWN:
					{
						if (player == WHITE)
						{
							if ((x + 1 < 8 && y + 1 < 8 && _grid[y + 1][x + 1] == PIECE(KING, WHITE))
									|| (x - 1 >= 0 && y + 1 < 8 && _grid[y + 1][x - 1] == PIECE(KING, WHITE)))
								return (true);
						}
						else
						{
							if ((x + 1 < 8 && y - 1 >= 0 && _grid[y - 1][x + 1] == PIECE(KING, BLACK))
									|| (x - 1 >= 0 && y - 1 >= 0 && _grid[y - 1][x - 1] == PIECE(KING, BLACK)))
								return (true);
						}
						break;
					}
					case QUEEN:
					{
						if (checkDirection(x, y, player, directions))
							return (true);
						break;
					}
					case ROOK:
					{
						if (checkDirection(x, y, player, rookDirections))
							return (true);
						break;
					}
					case BISHOP:
					{
						if (checkDirection(x, y, player, bishopDirections))
							return (true);
					}
				}
				std::cout << "Found danger for player " << (player == WHITE ? "White" : "Black") << " at x " << x << " | y " << y << " | piece " << _grid[y][x] << std::endl;
				break;
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

void Grid::handleInputs(sf::RenderWindow &window)
{
	static std::pair<short, short> pieceHeld = {-1, -1};
	static Player turn = WHITE;
	static sf::Sprite *currentPiece = nullptr;
	sf::Vector2<float> mousePos = WORLDPOS(window);
	short x;
	short y;
	Piece gridPiece;

	mousePos.x -= PIECE_OFFSET_X;
	mousePos.y -= PIECE_OFFSET_Y;
	x = static_cast<int>(mousePos.x) / 75;
	y = static_cast<int>(mousePos.y) / 75;
	if (x > 7 || x < 0 || y > 7 || y < 0)
		return;
	gridPiece = Utils::getPiece(_grid[y][x]);
	if ((gridPiece == EMPTY && pieceHeld.first == -1) || (pieceHeld.first == -1 && std::isupper(_grid[y][x]) && turn != WHITE && _grid[y][x] != '.')
			|| (pieceHeld.first == -1 && std::islower(_grid[y][x]) && turn != BLACK && _grid[y][x] != '.'))
		return;
	if (std::pair<short, short>(x, y) == pieceHeld || Utils::isOpponentPiece(_grid[y][x], turn) || gridPiece == EMPTY)
		pieceHeld = {-1, -1};
	else if (pieceHeld.first == -1 || (pieceHeld.first != -1 && _grid[y][x] != '.' && Utils::isOpponentPiece(gridPiece, turn)))
		pieceHeld = std::pair<short, short>(x, y);
	for (auto &piece : _pieces)
	{
		if (piece.getGlobalBounds().contains(WORLDPOS(window)))
		{
			if (currentPiece)
			{
				currentPiece->setScale(currentPiece->getScale().x - 0.05f, currentPiece->getScale().y - 0.05f);
				currentPiece->setPosition(currentPiece->getPosition().x + 3.25f, currentPiece->getPosition().y + 6.25f);
			}
			if (pieceHeld.first != -1)
			{
				piece.setScale(piece.getScale().x + 0.05f, piece.getScale().y + 0.05f);
				piece.setPosition(piece.getPosition().x - 3.25f, piece.getPosition().y - 6.25f);
				currentPiece = &piece;
			}
			else
				currentPiece = nullptr;
		}
	}
}
