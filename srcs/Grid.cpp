/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:45 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 18:03:19 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/Utils.hpp"
#include <Grid.hpp>
#include <algorithm>

Grid::Grid()
{
	std::copy(&startingGrid[0][0], &startingGrid[0][0] + 64, &_grid);
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
	int lookX = 0;
	int lookY = 0;
	Player opponent = INVERT_PLAYER(player);
	Direction direction;

	for (int i = 0; i < 7; i++)
	{
		direction = static_cast<Direction>(i);
		switch (direction)
		{
			case NORTH:
				lookY = -1;
				lookX = 0;
				break;
			case SOUTH:
				lookY = 1;
				lookX = 0;
				break;
			case EAST:
				lookY = 0;
				lookX = 1;
				break;
			case WEST:
				lookY = 0;
				lookX = -1;
				break;
			case NORTHWEST:
				lookY = -1;
				lookX = -1;
				break;
			case NORTHEAST:
				lookY = -1;
				lookX = 1;
				break;
			case SOUTHWEST:
				lookY = 1;
				lookX = -1;
				break;
			case SOUTHEAST:
				lookY = 1;
				lookX = 1;
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
		if (getPieceAt(kingX + knightRadius[i].first, kingY + knightRadius[i].second) == PIECE(KNIGHT, player) || hasDanger(kingPos, player))
			return (true);
	}
	return (false);
}

Player Grid::hasCheck()
{
	std::pair<short, short> whiteKingPos = Utils::getPosition(*this, 'k');
	std::pair<short, short> blackKingPos = Utils::getPosition(*this, 'K');

	return (checkCheck(whiteKingPos, WHITE) ? WHITE : checkCheck(blackKingPos, BLACK) ? BLACK : NONE);
}
