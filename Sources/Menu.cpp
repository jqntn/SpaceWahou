#include "Menu.h"
Menu::Menu(sf::RenderWindow& window)
{
  if (!font.openFromFile(getAssetsPath() + "/SpaceAge.ttf")) {
  }
  menu[0].setFont(font);
  menu[0].setFillColor(sf::Color::White);
  menu[0].setString("Space Wahou");
  menu[0].setPosition(sf::Vector2f(
    (float)window.getSize().x / 2 -
      ((menu[0].getCharacterSize() * menu[0].getString().getSize()) / 2),
    (float)window.getSize().y / 4 * 1));
  menu[1].setFont(font);
  menu[1].setFillColor(sf::Color::Cyan);
  menu[1].setString("Play");
  menu[1].setPosition(sf::Vector2f(
    (float)window.getSize().x / 2 -
      ((menu[1].getCharacterSize() * menu[1].getString().getSize()) / 2),
    (float)window.getSize().y / 4 * 2));
  menu[2].setFont(font);
  menu[2].setFillColor(sf::Color::White);
  menu[2].setString("Quit");
  menu[2].setPosition(sf::Vector2f(
    (float)window.getSize().x / 2 -
      ((menu[2].getCharacterSize() * menu[2].getString().getSize()) / 2),
    (float)window.getSize().y / 4 * 3));
  menu[3].setFont(font);
  menu[3].setFillColor(sf::Color::White);
  menu[3].setString("Sound ON");
  menu[3].setPosition(sf::Vector2f((float)window.getSize().x / 4 * 0.1f,
                                   (float)window.getSize().y / 4 * 3.8f));
  selectedItemIndex = 1;
}
Menu::~Menu() {}
void
Menu::MoveUp()
{
  if (selectedItemIndex - 1 >= 1) {
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex--;
    menu[selectedItemIndex].setFillColor(sf::Color::Cyan);
  }
}
void
Menu::MoveDown()
{
  if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex++;
    menu[selectedItemIndex].setFillColor(sf::Color::Cyan);
  }
}
void
Menu::OnEventMenu(sf::RenderWindow* window, sf::Event event, float deltaTime)
{
  if (const sf::Event::KeyReleased* e = event.getIf<sf::Event::KeyReleased>()) {
    switch (e->code) {
      case sf::Keyboard::Key::Up:
        MoveUp();
        break;
      case sf::Keyboard::Key::Down:
        MoveDown();
        break;
      case sf::Keyboard::Key::Enter:
        switch (GetPressedItem()) {
          case 1:
            gameLaunched = true;
            isPaused = false;
            break;
          case 2:
            std::exit(0);
            break;
          case 3:
            if (soundON) {
              soundON = false;
              menu[3].setString("Sound OFF");
              if (nullptr == soundPlayer) {
                soundPlayer = new sf::Sound(buffer_tmp);
              }
              if (nullptr == soundEnemy) {
                soundEnemy = new sf::Sound(buffer_tmp);
              }
              if (nullptr == music) {
                music = new sf::Music();
              }
              soundPlayer->setVolume(0);
              soundEnemy->setVolume(0);
              music->setVolume(0);
            } else if (!soundON) {
              soundON = true;
              menu[3].setString("Sound ON");
              if (nullptr == soundPlayer) {
                soundPlayer = new sf::Sound(buffer_tmp);
              }
              if (nullptr == soundEnemy) {
                soundEnemy = new sf::Sound(buffer_tmp);
              }
              if (nullptr == music) {
                music = new sf::Music();
              }
              soundPlayer->setVolume(70);
              soundEnemy->setVolume(70);
              music->setVolume(70);
            }
            break;
        }
    }
  }
}
void
Menu::drawMenu(sf::RenderWindow& window)
{
  for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
    window.draw(menu[i]);
  }
}