/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:54:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/06/23 21:20:20 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_chess.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "Grid.hpp"
#include "Texture.hpp"
#include <SFML/Window/Event.hpp>

unsigned int WINDOW_WIDTH = 1280;
unsigned int WINDOW_HEIGHT = 720;

int main()
{
	Texture::loadPieces();
	Grid grid;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ft_chess");
	Player hasCheck = grid.hasCheck();
	std::cout << (hasCheck == WHITE ? "White" : hasCheck == BLACK ? "Black" : "None") << std::endl;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				grid.handleInputs(window);
		}
		window.clear();
		grid.render(window);
		window.display();
	}
	Texture::freePieces();
}
