#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "background.hpp"
#include "hero.hpp"
#include "npc.hpp"

void StartAnimation(sf::RenderWindow &window, Background &background, Hero &hero, NPC &npc);
//void PreFightMenu(sf::RenderWindow &window, Background &background, FirstMenu &menu);
//bool FightCycle(sf::RenderWindow &window, FightScene &fight);
//void WinAnimation(sf::RenderWindow &window, FightScene &fight);
//void LooseAnimation(sf::RenderWindow &window, FightScene &fight);

int main()
{
//    video mode initiation
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(desktop, "Omae wa mou shinderu? - NANIII!!??", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled (true);
//    window.setFramerateLimit (60);
    sf::Vector2f resize_vector = sf::Vector2f((float)desktop.width/DefaultVideoWidth, 
                (float)desktop.height/DefaultVideoHeight);
    Background background("test/K3RpkJEqXeg.png", resize_vector);
    Hero hero("test/iii.png", resize_vector);
    NPC npc("test/jjj.png", resize_vector);
//    sf::Clock clock;
//    clock.restart();
//    FightScene fight(desktop, &background);
//    fight.setBackground("test/K3RpkJEqXeg.png");
//    fight.setHero("test/jjj.png");

//    Menu menu1();

    StartAnimation(window, background, hero, npc);
//    PreFightMenu(window, menu1);
//    FightCycle(window, fight);
    //...Win Or Loose Animation;

    return 0;
}

//    while (window.isOpen())
//    {
//        uint32_t time = clock.restart().asMicroseconds();
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            window.close();
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//        {
//            // Esc key is pressed: exit
//            window.close();
//        }
//
//        window.clear();
//        //window.draw(fight);
//        window.draw(background);
//        window.draw(hero);
//        window.display();
//    }
//
//    return 0;
//}

void StartAnimation(sf::RenderWindow &window, Background &background, Hero &hero, NPC &npc)
{
    sf::Clock clock;
    while (window.isOpen())
	{
        float time = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // Esc key is pressed: exit
            window.close();
        }

		window.clear();
        window.draw(background);
        window.draw(npc);
        window.draw(hero);
		window.display();
        if (hero.Action(time) && npc.Action(time) && hero.ChangeAction())
            return;
	}
    
    return;
}
/*
void PreFightMenu(sf::RenderWindow &window, Background &background, Menu &menu)
{
    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // Esc key is pressed: exit
            window.close();
        }

		window.clear();
        window.draw(background);
		window.display();
	}
    
    return;
}
*/
//bool FightCycle(sf::RenderWindow &window, FightScene &fight);
//void WinAnimation(sf::RenderWindow &window, FightScene &fight);
//void LooseAnimation(sf::RenderWindow &window, FightScene &fight);

