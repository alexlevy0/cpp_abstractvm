#include "Menu.hpp"
#include "Slide.hpp"
#include "Input.hh"

Menu::Menu(gdl::Clock const &clock, gdl::Input const &input, gdl::SdlContext const &context, gdl::BasicShader const &shader)
{
  _clock = clock;
  _input = input;
  _context = context;
  _shader = shader;
  _deep = 0;
  _pos = 0;
  _numberofplayer = 0;
}

Menu::~Menu()
{

}

int	Menu::getDeep()
{
  return (this->_deep);
}

int	Menu::getNumberPlayer()
{
  return (this->_numberofplayer);
}

int	Menu::getPos()
{
  return (this->_pos);
}

void	Menu::setDeep(int deep)
{
  _deep = deep;
}

void	Menu::setNumberPlayer(int nbr)
{
  _numberofplayer = nbr;
}

void	Menu::setPos(int pos)
{
  _pos = pos;
}

bool	Menu::initialize()
{
  // Caméra

  glm::mat4 projection;
  glm::mat4 transformation;
  
  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(0, 0, -50), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);

  // Slide
  AObject *menu1 = new Slide("./assets/MenuChoix1player.tga", 50, -50);
  if (menu1->initialize() == false)
    return false;
  _level1.push_back(menu1);
  AObject *menu2 = new Slide("./assets/MenuChoix2players.tga", 50, -50);
  if (menu2->initialize() == false)
    return false;
  _level1.push_back(menu2);
  AObject *menu3 = new Slide("./assets/MenuQuitter.tga", 50, -50);
  if (menu3->initialize() == false)
    return false;
  _level1.push_back(menu3);
  AObject *menu4 = new Slide("./assets/MenuMap1.tga", 50, -50);
  if (menu4->initialize() == false)
    return false;
  _level2.push_back(menu4);
  AObject *menu5 = new Slide("./assets/MenuMap2.tga", 50, -50);
  if (menu5->initialize() == false)
    return false;
  _level2.push_back(menu5);
  AObject *menu6 = new Slide("./assets/MenuMap3.tga", 50, -50);
  if (menu6->initialize() == false)
    return false;
  _level2.push_back(menu6);
  AObject *menu7 = new Slide("./assets/MenuMapRetour.tga", 50, -50);
  if (menu7->initialize() == false)
    return false;
  _level2.push_back(menu7);
  return true;
}

bool	Menu::update()
{
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  
  _context.updateClock(_clock);
  _context.updateInputs(_input);

  if (_input.getInput(SDLK_RIGHT, true))
    {
      this->setPos(this->getPos() + 1);
      if (this->getDeep() == 0)
	{
	  if (this->getPos() >= _level1.size())
	    this->setPos(0);
	}
      else
	{
	  if (this->getPos() >= _level2.size())
	    this->setPos(0);
	}
    }
  else if (_input.getKey(SDLK_LEFT, true))
    {
      this->setPos(this->getPos() - 1);
      if (this->getDeep() == 0)
	{
	  if (this->getPos() < 0)
	    this->setPos(_level1.size() - 1);
	}
      else
	{
	  if (this->getPos() < 0)
	    this->setPos(_level2.size() - 1);
	}
    }
  if (_input.getKey(SDLK_RETURN, true))
    {
      if (this->getDeep() == 0)
	{
	  if (this->getPos() == (_level1.size() - 1))
	    return false;
	  this->setNumberPlayer(this->getPos() + 1);
	  this->setDeep(1);
	  this->setPos(0);
	}
      else
	{
	  if (this->getPos() == (_level2.size() - 1))
	    {
	      this->setDeep(0);
	      this->setPos(0);
	    }
	  else
	    {
	      return false;
	    }
	}
    }
  return true;
}

void	Menu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  if (this->getDeep() == 0)
    _level1[this->getPos()]->draw(_shader, _clock);
  else
    _level2[this->getPos()]->draw(_shader, _clock);
  _context.flush();
}
