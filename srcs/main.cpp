/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:54:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/22 21:31:28 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_chess.hpp"
#include <iostream>
#include "Grid.hpp"
#include <SFML/Window/Event.hpp>
unsigned int WINDOW_WIDTH = 1280;
unsigned int WINDOW_HEIGHT = 720;

int main()
{
	Grid grid;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ft_chess");
	std::cout << (grid.hasCheck() ? "Yes" : "No") << std::endl;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			
		}
		window.clear();
		window.display();
	}
}
