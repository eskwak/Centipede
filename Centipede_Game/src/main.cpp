/*
    Edward Kwak
    3/17/2025

    Main file for centipede game.
    Contains pre-game setup and main game loop.

*/

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Starship.h"
#include "Mushroom.h"
#include "Laser.h"
#include "Spider.h"
#include "Centipede.h"


int main() {

    /************************************************/
    /************************************************/
    //         SETUP FOR PRE-GAME ELEMENTS         
    /************************************************/
    /************************************************/
    

    // Using 1280x720 resolution given fullscreen gives inconsistent behavior.
    sf::VideoMode vm(1280, 720);
    sf::RenderWindow window(vm, "Centipede Game", sf::Style::Default);

    // Default to 120 fps.
    window.setFramerateLimit(120);

    // Setup background texture for start screen
    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/startScreen.png");

    // Set up start screen
    sf::Sprite startScreen;
    startScreen.setTexture(textureBackground);
    startScreen.setPosition(0, 0);
    startScreen.setScale(1.4f, 1.4f);

    // Clock set up for manual movements
    sf::Clock clock;

    // initialize score & number of lives left.
    int score = 0;
    int lives = 5;

    // create game texts
    sf::Text startScreenText;
    sf::Text scoreText;
    sf::Text livesText;
    sf::Text gameOverText;
    sf::Text winGameText;

    // create and load font
    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    // set fonts for game texts
    startScreenText.setFont(font);
    scoreText.setFont(font);
    livesText.setFont(font);
    gameOverText.setFont(font);
    winGameText.setFont(font);


    // initialize score & lives texts
    startScreenText.setString("Press ENTER to start");
    scoreText.setString("Score = " + std::to_string(score));
    livesText.setString("Lives = " + std::to_string(lives));

    startScreenText.setCharacterSize(45);
    scoreText.setCharacterSize(40);
    livesText.setCharacterSize(40);

    startScreenText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    livesText.setFillColor(sf::Color::White);
    gameOverText.setFillColor(sf::Color::Red);

    // set bounds & location for game texts
    sf::FloatRect textRect = startScreenText.getLocalBounds();
    startScreenText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    startScreenText.setPosition(1280 / 2.0f, 720 / 2.0f);
    scoreText.setPosition(10, 5);
    livesText.setPosition(320, 5);

    // game status flags
    bool acceptInput = false;
    bool startOfGame = true;
    bool gameStarted = false;
    bool gameOver = false;
    bool win = false;
    bool spaceBarPressed = false;
    bool spiderDestroyed = false;

    // setup starship
    Starship starship = Starship();

    sf::Texture starshipTexture;
    starshipTexture.loadFromFile("graphics/StarShip.png");

    sf::Sprite starshipSprite;
    starshipSprite.setTexture(starshipTexture);
    starshipSprite.setScale(1.5f, 1.5f);
    starshipSprite.setPosition(starship.getPosition());

    // setup mushrooms
    sf::Texture firstMushroomTexture;
    sf::Texture secondMushroomTexture;

    firstMushroomTexture.loadFromFile("graphics/Mushroom0.png");
    secondMushroomTexture.loadFromFile("graphics/Mushroom1.png");

    // list to store mushrooms
    std::vector<Mushroom> mushrooms;

    // generate 30 random mushrooms and store them
    for (int i = 0; i < 30; i++) {
        Mushroom tempMushroom = Mushroom(firstMushroomTexture, secondMushroomTexture, 1280, 900);
        mushrooms.push_back(tempMushroom);
    }

    // list to store laser
    std::vector<Laser> lasers;

    // Spider setup
    Spider spider;
    int spiderRespawnCount = 0;

    // Centipede Setup
    sf::Texture headTexture;
    sf::Texture bodyTexture;

    headTexture.loadFromFile("graphics/CentipedeHead.png");
    bodyTexture.loadFromFile("graphics/CentipedeBody.png");

    // initialize starting x-coordinate for centipede head.
    float startX = 550.0f;

    // create centipede head first
    Centipede head = Centipede(startX, 0.0f, true);
    head.setTexture(headTexture);

    // decrease starting x-coordinate for body elements
    startX -= 30.0f;

    // list to store centipede segments
    std::vector<Centipede> centipede;
    centipede.push_back(head);

    // create 11 centipede body segments (12 total segments including head)
    for (int i = 0; i < 11; i++) {
        Centipede body = Centipede(startX, 0.0f, false);
        body.setTexture(bodyTexture);
        startX -= 30.0f;
        centipede.push_back(body);
    }


    /************************************************/
    /************************************************/
    //               MAIN GAME LOOP
    /************************************************/
    /************************************************/

    while (window.isOpen()) {
        sf::Event event;

        // allow user inputs
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased) {
                acceptInput = true;
            }

            // add lasers to when space is pressed + make it so spacebar cannot be held down indefinitely
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && !spaceBarPressed) {
                    lasers.push_back(Laser(starship.getPosition().x + 10, starship.getPosition().y));
                    spaceBarPressed = true;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    spaceBarPressed = false;
                }
            }
        }

        // Setup for when player wins game.
        if (win == true) {
            window.clear();

            winGameText.setFont(font);
            winGameText.setCharacterSize(100);
            winGameText.setFillColor(sf::Color::Green);
            winGameText.setString("YOU WON!\nPress 'ENTER' to Quit");

            sf::FloatRect winGameTextRect = winGameText.getLocalBounds();
            winGameText.setOrigin(winGameTextRect.width / 2.0f, winGameTextRect.height / 2.0f);
            winGameText.setPosition(1280 / 2.0f, 720 / 2.0f);

            window.draw(winGameText);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
        }

        // Setup for when player loses game
        if (gameOver == true) {
            window.clear();

            // Set up game over text
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(100);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setString("GAME OVER!\nPress 'ENTER' to Quit");

            sf::FloatRect gameOverTextRect = gameOverText.getLocalBounds();
            gameOverText.setOrigin(gameOverTextRect.width / 2.0f, gameOverTextRect.height / 2.0f);
            gameOverText.setPosition(1280 / 2.0f, 720 / 2.0f);

            // display game over text
            window.draw(gameOverText);
            window.display();

            // Terminate game
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
        }

        // Terminate game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // Starting Game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && startOfGame) {
            startOfGame = false;
            gameStarted = true;
            window.clear();
        }

        // Starship movement conditions
        if (gameStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            starship.setStarshipMovingRight(true);
        }
        else {
            starship.setStarshipMovingRight(false);
        }
        if (gameStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            starship.setStarshipMovingLeft(true);
        }
        else {
            starship.setStarshipMovingLeft(false);
        }
        if (gameStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            starship.setStarshipMovingUp(true);
        }
        else {
            starship.setStarshipMovingUp(false);
        }
        if (gameStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            starship.setStarshipMovingDown(true);
        }
        else {
            starship.setStarshipMovingDown(false);
        }

        // set up time difference
        float deltaTime = clock.restart().asSeconds();

        // update centipede position
        for (auto& segment : centipede) {
            // left boundary
            if (segment.getPosition().x <= 0.0f) {
                segment.moveDown(30.0f);
            }
            // right boundary
            if (segment.getPosition().x >= 1280.0f) {
                segment.moveDown(30.0f);
            }
            // check if centipede has reached the bottom
            if (segment.getPosition().y >= 720.0f) {
                gameOver = true;
                break;
            }
            // if the centipede hits starship, game over
            if (segment.getSprite().getGlobalBounds().intersects(starshipSprite.getGlobalBounds())) {
                gameOver = true;
                break;
            }
            // check if the centipede has collided with a mushroom
            for (int i = 0; i < mushrooms.size(); i++) {
                if (segment.getSprite().getGlobalBounds().intersects(mushrooms[i].getBounds())) {
                    segment.moveDown(30.0f);
                    break;
                }
            }
            // move centipede horizontally
            segment.move(segment.getDirection() * 6.0f);
            segment.updatePosition();
        }

        // update starship position
        starship.update(deltaTime);
        starshipSprite.setPosition(starship.getPosition());

        // update spider position
        if (!spiderDestroyed) {
            spider.update(deltaTime);
            // check to see if spider collides with any mushrooms.
            for (int i = 0; i < mushrooms.size(); i++) {
                if (spider.getBounds().intersects(mushrooms[i].getBounds())) {
                    mushrooms.erase(mushrooms.begin() + i);
                    i--;
                }
            }
        }

        // Check for collisions between spider and starship
        if (!spiderDestroyed) {
            if (spider.getBounds().intersects(starshipSprite.getGlobalBounds())) {
                starship.resetPosition();
                lives--;
                livesText.setString("Lives = " + std::to_string(lives));

                // If the player runs out of lives, player loses game
                if (lives <= 0) {
                    gameOver = true;
                }
            }
        }

        // Check for collisions between laser and mushroom
        if (!lasers.empty()) {
            for (int i = 0; i < lasers.size(); i++) {
                // checks for laser collision with spider
                if (!spiderDestroyed) {
                    if (lasers[i].getBounds().intersects(spider.getSprite().getGlobalBounds())) {
                        score += 300;
                        lasers.erase(lasers.begin() + i);
                        i--;
                        spiderDestroyed = true;
                        scoreText.setString("Score = " + std::to_string(score));
                        break;
                    }
                }

                for (int j = 0; j < mushrooms.size(); j++) {
                    if (lasers[i].getBounds().intersects(mushrooms[j].getBounds())) {
                        // destroy the laser that collides in order to prevent it from passing through
                        lasers.erase(lasers.begin() + i);
                        i--;
                        if (mushrooms[j].getMushroomStatus() == true) {
                            mushrooms.erase(mushrooms.begin() + j);
                            score += 4;
                            scoreText.setString("Score = " + std::to_string(score));
                            j--;
                        }
                        else {
                            mushrooms[j].mushroomHit();
                            mushrooms[j].changeMushroomTexture();
                        }
                        break;
                    }
                }
            }
        }


        // update laser position
        if (!lasers.empty()) {
            for (auto& laser : lasers) {
                laser.update(deltaTime);
            }
            // check and handle lasers that move out of bounds.
            for (int i = 0; i < lasers.size(); i++) {
                if (lasers[i].getPosition().y < 0) {
                    lasers.erase(lasers.begin() + i);
                    i--;
                }
            }
        }

        // Check for collisions between centipede and laser
        if (!lasers.empty()) {
            for (int i = 0; i < lasers.size(); i++) {
                // if there are no lasers, no need to check
                if (lasers.size() == 0) {
                    break;
                }
                for (int j = 0; j < centipede.size(); j++) {
                    if (lasers[i].getBounds().intersects(centipede[j].getSprite().getGlobalBounds())) {
                        // increase score
                        if (centipede[j].checkIfHead()) {
                            score += 100;
                        }
                        else {
                            score += 10;
                        }
                        scoreText.setString("Score = " + std::to_string(score));
                        // destroy laser that has collided
                        if (lasers.size() == 1) {
                            lasers.pop_back();
                        }
                        else {
                            lasers.erase(lasers.begin() + i);
                            i--;
                        }
                        // if no more centipede segments, player wins game
                        if (centipede.size() == 1) {
                            win = true;
                        }
                        else {
                            // split centipede when a segment is hit in the middle
                            int currentDirection = centipede[j].getDirection();
                            int newDirection = -currentDirection;

                            std::vector<Centipede> newCentipede1(centipede.begin(), centipede.begin() + j);
                            std::vector<Centipede> newCentipede2(centipede.begin() + j + 1, centipede.end());


                            for (auto& segment : newCentipede1) {
                                segment.setDirection(currentDirection);
                            }

                            for (auto& segment : newCentipede2) {
                                segment.setDirection(newDirection);
                            }

                            centipede.erase(centipede.begin() + j);
                            j--;

                            if (!newCentipede2.empty()) {
                                if (newCentipede2[0].getDirection() == 1) {
                                    newCentipede2[newCentipede2.size() - 1].changeToHead();
                                    newCentipede2[newCentipede2.size() - 1].setTexture(headTexture);
                                }
                                else if (newCentipede2[0].getDirection() == -1) {
                                    newCentipede2[newCentipede2.size() - 1].changeToHead();
                                    newCentipede2[newCentipede2.size() - 1].setTexture(headTexture);
                                }
                            }

                            centipede.clear();


                            for (int i = 0; i < newCentipede1.size(); i++) {
                                centipede.push_back(newCentipede1[i]);
                            }
                            for (int j = newCentipede2.size() - 1; j >= 0; j--) {
                                centipede.push_back(newCentipede2[j]);
                            }

                            newCentipede1.clear();
                            newCentipede2.clear();
                        }
                        break;
                    }
                }
            }
        }

        // respawn spider after given period
        if (spiderDestroyed) {
            if (spiderRespawnCount >= 250) {
                spiderDestroyed = false;
                spiderRespawnCount = 0;


                sf::Texture tempSpiderTexture;
                tempSpiderTexture.loadFromFile("spider.png");
                spider.getSprite().setTexture(tempSpiderTexture);
                window.draw(spider.getSprite());
            }
            spiderRespawnCount++;
        }


        // clear window for each frame.
        window.clear();

        // start screen display
        if (startOfGame) {
            window.clear();
            window.draw(startScreen);
        }
        // mid-game display
        else {
            window.draw(scoreText);
            window.draw(livesText);
            window.draw(starshipSprite);
            for (auto& mushroom : mushrooms) {
                window.draw(mushroom.getSprite());
            }
            for (auto& laser : lasers) {
                window.draw(laser.getShape());
            }
            if (!spiderDestroyed) {
                window.draw(spider.getSprite());
            }
            for (auto& c : centipede) {
                window.draw(c.getSprite());
            }
        }

        // update game frame
        if (gameOver == false && win == false) {
            window.display();
        }
    }
    // End of game loop.

    return 0;
}