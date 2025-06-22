/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chess_utils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:08:58 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 17:47:28 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"

char Utils::getPieceAsChar(Piece piece)
{
	switch (piece)
	{
		case EMPTY:
			return ('.');
		case PAWN:
			return ('p');
		case ROOK:
			return ('r');
		case KNIGHT:
			return ('n');
		case BISHOP:
			return ('b');
		case KING:
			return ('k');
		case QUEEN:
			return ('q');
	}
}

std::pair<short, short> Utils::getPosition(Grid &grid, char piece)
{
	for (short x = 0; x < 8; x++)
	{
		for (short y = 0; y < 8; y++)
		{
			if (grid.getGrid()[y][x] == piece)
				return (std::pair<short, short>(x, y));
		}
	}
	return (std::pair<short, short>(-1, -1));
}
