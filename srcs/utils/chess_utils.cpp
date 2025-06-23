/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chess_utils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:08:58 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/23 20:08:48 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include <cctype>

bool Utils::isOpponentPiece(char piece, Player player)
{
	if (piece == '.')
		return (false);
	else if (player == WHITE && std::isupper(piece))
		return (false);
	else if (player == BLACK && std::islower(piece))
		return (false);
	return (true);
}

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
	return ('X');
}

Piece Utils::getPiece(char piece)
{
	switch (std::tolower(piece))
	{
		case 'p':
			return (PAWN);
		case 'r':
			return (ROOK);
		case 'n':
			return (KNIGHT);
		case 'b':
			return (BISHOP);
		case 'k':
			return (KING);
		case 'q':
			return (QUEEN);
		default:
			return (EMPTY);
	}
}

std::pair<short, short> Utils::getPosition(Grid &grid, Piece piece, Player player)
{
	char playerPiece = getPieceAsChar(piece) - (player == WHITE ? 32 : 0);
	for (short x = 0; x < 8; x++)
	{
		for (short y = 0; y < 8; y++)
		{
			if (grid.getGrid()[y][x] == playerPiece)
				return (std::pair<short, short>(x, y));
		}
	}
	return (std::pair<short, short>(-1, -1));
}
