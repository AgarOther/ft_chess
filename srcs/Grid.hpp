/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:58:21 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 21:36:42 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <utility>
#include <vector>

enum Player
{
	NONE,
	WHITE,
	BLACK
};

enum Piece
{
	EMPTY,
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	KING,
	QUEEN
};

const std::vector<std::pair<int, int>> directions = {
			{ 0, -1 }, // NORTH
			{ 0,  1 }, // SOUTH
			{ 1,  0 }, // EAST
			{-1,  0 }, // WEST
			{-1, -1 }, // NORTHWEST
			{ 1, -1 }, // NORTHEAST
			{-1,  1 }, // SOUTHWEST
			{ 1,  1 }  // SOUTHEAST
    	};

constexpr char startingGrid[8][8] = {
            {'r','n','b','q','k','b','n','r'},
            {'p','p','p','p','p','p','p','p'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'.','.','.','.','.','.','.','.'},
            {'P','P','P','P','P','P','P','P'},
            {'R','N','B','Q','K','B','N','R'}
        };

constexpr std::pair<short, short> knightRadius[8] = {
	{-1, -2},
	{ 1, -2},
	{-1,  2},
	{ 1,  2},
	{ 2,  1},
	{ 2, -1},
	{-2,  1},
	{-2, -1},
};

class Grid
{
	public:
		Grid();
		~Grid();

		Player hasCheck();
		char (*getGrid())[8];
		char getPieceAt(short x, short y) const;
	private:
		char _grid[8][8];
		bool checkCheck(const std::pair<short, short> &kingPos, Player player);
		bool hasDanger(std::pair<short, short> pos, Player player);
};
