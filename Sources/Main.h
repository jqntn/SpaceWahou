#pragma once
#include "MathUtils.h"
#include "SFML/Audio.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#define EMSCRIPTEN_WIDTH 1920
#define EMSCRIPTEN_HEIGHT 1080
#ifdef EMSCRIPTEN
#define WINDOW_WIDTH_REF EMSCRIPTEN_WIDTH
#define WINDOW_HEIGHT_REF EMSCRIPTEN_HEIGHT
#define WINDOW_WIDTH_PTR EMSCRIPTEN_WIDTH
#define WINDOW_HEIGHT_PTR EMSCRIPTEN_HEIGHT
#else
#define WINDOW_WIDTH_REF (window.getSize().x)
#define WINDOW_HEIGHT_REF (window.getSize().y)
#define WINDOW_WIDTH_PTR (window->getSize().x)
#define WINDOW_HEIGHT_PTR (window->getSize().y)
#endif
// Julien: LOG MACRO
#ifdef EMSCRIPTEN
#define LOG(X)
#else
#define LOG(X) std::cout << X << std::endl;
#endif
// Julien: Utils
std::string
getAssetsPath();
// Julien: API
class Map;
class Object
{
public:
  std::string id;
  bool isActive = 1;
  Object();
  ~Object();
  virtual void Start(sf::RenderWindow* window) {};
  virtual void Update(sf::RenderWindow* window, float deltaTime) {};
  virtual void OnEvent(sf::RenderWindow* window,
                       sf::Event event,
                       float deltaTime) {};
};
class Object2
{
public:
  // std::string id;
  bool isActive = 1;
  Object2();
  virtual ~Object2();
  virtual void Start(sf::RenderWindow* window) {};
  virtual void Update(sf::RenderWindow* window, float deltaTime) {};
};
Object*
FindObject(std::string id);
bool
SetActive(void* object, bool isActive);
bool
DestroyObject(void* object);
bool
DestroyObject2(Object2* object2);
bool
MouseButtonDown(bool boule);
bool
MouseButtonUp(bool boule);
void
BeginGame(sf::RenderWindow& window, sf::Font police);
class Enemy;
std::vector<Enemy*>&
getEnemies();