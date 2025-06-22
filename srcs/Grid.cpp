/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:45 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 21:36:51 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/Utils.hpp"
#include "Grid.hpp"
#include <algorithm>
#include <iostream>

Grid::Grid()
{
	std::copy(&startingGrid[0][0], &startingGrid[0][0] + 64, &_grid[0][0]);
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

bool Grid::hasDanger(std::pair<short, short> pos, Player player)
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
	std::pair<short, short> whiteKingPos = Utils::getPosition(*this, 'K');
	std::pair<short, short> blackKingPos = Utils::getPosition(*this, 'k');

	return (checkCheck(whiteKingPos, WHITE) ? WHITE : checkCheck(blackKingPos, BLACK) ? BLACK : NONE);
}
