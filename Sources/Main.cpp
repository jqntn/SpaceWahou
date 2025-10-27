#include "Main.h"
#include "Background.h"
#include "Enemy.h"
#include "Map.h"
#include "Menu.h"
#include "UI.h"
Background* background;
Map* map;
UI* ui;
sf::Sound* soundPlayer = new sf::Sound();
sf::Sound* soundEnemy = new sf::Sound();
sf::Music* music = new sf::Music();
sf::Sound*
getSoundPlayer()
{
  return soundPlayer;
}
sf::Sound*
getSoundEnemy()
{
  return soundEnemy;
}
sf::Music*
getMusic()
{
  return music;
}
std::string
getAppPath()
{
  char cAppPath[MAX_PATH];
  GetModuleFileNameA(0, cAppPath, MAX_PATH);
  std::string sAppPath = cAppPath;
  char appNamePos = sAppPath.find_last_of("\\");
  return sAppPath.substr(0, appNamePos + 1);
}
std::string
getAssetsPath()
{
  return "Assets\\";
}
// Julien: API
std::vector<Object*> Objects;
std::vector<Object2*> Objects2;
Object::Object()
{
  Objects.push_back(this);
}
Object::~Object()
{
  Objects.erase(std::find(Objects.begin(), Objects.end(), this));
  Objects.shrink_to_fit();
}
Object2::Object2()
{
  Objects2.push_back(this);
}
Object2::~Object2()
{
  LOG(this);
  Objects2.erase(std::find(Objects2.begin(), Objects2.end(), this));
  Objects2.shrink_to_fit();
}
Object*
FindObject(std::string id)
{
  for (auto i : Objects)
    if (i->id == id)
      return i;
  return 0;
}
bool
SetActive(void* object, bool isActive)
{
  if (object) {
    ((Object*)object)->isActive = isActive;
    return 1;
  } else
    return 0;
}
std::vector<Object*> toDestroy;
std::list<Object2*> toDestroy2;
bool
DestroyObject(void* object)
{
  auto o = (Object*)object;
  auto i = std::find(Objects.begin(), Objects.end(), o);
  if (i != Objects.end()) {
    toDestroy.push_back(o);
    return 1;
  } else
    return 0;
}
bool
DestroyObject2(Object2* object2)
{
  auto o = object2;
  auto i = std::find(Objects2.begin(), Objects2.end(), o);
  auto j = std::find(toDestroy2.begin(), toDestroy2.end(), o);
  if (i != Objects2.end() && j == toDestroy2.end()) {
    toDestroy2.push_back(o);
    return 1;
  } else
    return 0;
}
bool
MouseButtonDown(bool boule)
{
  return boule;
}
bool
MouseButtonUp(bool boule)
{
  return boule;
}
void
BeginGame(sf::RenderWindow& window, sf::Font police)
{
}
std::vector<Enemy*> enemiesM;
std::vector<Enemy*>&
getEnemies()
{
  return enemiesM;
}
int
main()
{
  soundPlayer->setVolume(70);
  soundEnemy->setVolume(70);
  music->setVolume(70);
  // MouseCursor
  sf::CircleShape aimShape;
  float aimRadius = 10.0f;
  aimShape.setRadius(aimRadius);
  aimShape.setOrigin(aimRadius, aimRadius);
  aimShape.setFillColor(sf::Color::Transparent);
  aimShape.setOutlineColor(sf::Color::Red);
  aimShape.setOutlineThickness(2.0f);
  sf::ContextSettings settings;
  settings.antialiasingLevel = 4;
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
                          "SpaceWahou",
                          sf::Style::Fullscreen,
                          settings);
  window.setMouseCursorVisible(false);
  sf::Clock(clock);
  auto menu = new Menu(window);
  bool allCreated = false;
  background = new Background("background", &window);
  background->CreateStars(window);
  // background->CreateStars(window);
  // UIFonts
  sf::Font police;
  police.loadFromFile(getAssetsPath() + "\\SpaceAge.ttf");
  // MENU
  while (!menu->gameLaunched) {
    float deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          (event.type == sf::Event::KeyPressed &&
           event.key.code == sf::Keyboard::Escape)) {
        menu->gameLaunched = true;
        std::exit(0);
      }
      menu->OnEventMenu(&window, event, deltaTime);
    }
    window.clear();
    background->Update(&window, deltaTime);
    sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition(mousePositionInt);
    aimShape.setPosition(mousePosition);
    menu->drawMenu(window);
    window.display();
  }
  if (menu->gameLaunched && !allCreated) {
    map = new Map("Map", &window);
    Map::mape = map;
    ui = new UI("UI", &window, police);
    allCreated = true;
  }
  //
  while (window.isOpen()) {
    float deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    sf::Event event;
    while (window.pollEvent(event)) {
      if (!menu->isPaused) {
        if (event.type == sf::Event::Closed)
          std::exit(0);
        if (event.type == sf::Event::KeyPressed &&
            (event.key.code == sf::Keyboard::P ||
             event.key.code == sf::Keyboard::Escape))
          menu->isPaused = true;
        for (auto i : Objects)
          if (i->isActive)
            i->OnEvent(&window, event, deltaTime);
      } else {
        menu->OnEventMenu(&window, event, deltaTime);
      }
    }
    // Entities
    background->SpawnEntities(window, deltaTime);
    background->EndEntities(deltaTime);
    window.clear();
    // MouseCursor
    sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition(mousePositionInt);
    aimShape.setPosition(mousePosition);
    // Julien: Update Function
    if (!ui->loser && !menu->isPaused) {
      for (auto i : Objects)
        if (i->isActive)
          i->Update(&window, deltaTime);
      for (auto i : Objects2)
        if (i->isActive)
          i->Update(&window, deltaTime);
      for (auto i : toDestroy2) {
        LOG(i);
        delete i;
      }
      toDestroy2.clear();
      for (auto i : toDestroy) {
        LOG(i);
        delete i;
      }
      toDestroy.clear();
      map->SpawnEnemies(&window, deltaTime);
    } else if (menu->isPaused) {
      menu->drawMenu(window);
    } else if (ui->loser)
      ui->GameOver(&window);
    window.draw(aimShape);
    window.display();
  }
  background->DestroyEntities();
}