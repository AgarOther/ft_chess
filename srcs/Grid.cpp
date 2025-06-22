/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:00:45 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 17:31:05 by scraeyme         ###   ########.fr       */
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

char Grid::getPieceAt(int x, int y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return ('X');
	return (_grid[y][x]);
}

static bool checkCheck(Grid &grid, std::pair<int, int> kingPos, char knight)
{
	int kingX = kingPos.first;
	int kingY = kingPos.second;

	for (int i = 0; i < 8; i++)
	{
		if (grid.getPieceAt(kingX + knightRadius[i].first, kingY + knightRadius[i].second) == knight)
			return (true);
	}
	return (false);
}

Player Grid::hasCheck()
{
	std::pair<int, int> whiteKingPos = Utils::getPosition(*this, 'k');
	std::pair<int, int> blackKingPos = Utils::getPosition(*this, 'K');

	return (checkCheck(*this, whiteKingPos, 'N') ? WHITE : checkCheck(*this, blackKingPos, 'n') ? BLACK : NONE);
}
