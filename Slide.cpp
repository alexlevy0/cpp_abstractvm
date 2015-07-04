#include <iostream>
#include "Slide.hpp"

Slide::Slide(std::string const name, float const x, float const y)
{
  this->imagename = name;
  this->x = x;
  this->y = y;
}

Slide::~Slide()
{
}

std::string	Slide::getImagename()
{
  return (this->imagename);
}

double		Slide::getX()
{
  return (this->x);
}

double		Slide::getY()
{
  return (this->y);
}

bool		Slide::initialize()
{
  // On load la texture
  if (this->texture.load(this->imagename) == false)
    {
      std::cout << "Can't load " << this->imagename << std::endl;;
      return false;
    }
  // On la charge dans geometry
  this->geometry.pushVertex(glm::vec3(this->getX(), this->getY(), 25));
  this->geometry.pushVertex(glm::vec3(this->getX() - 100, this->getY(), 25));
  this->geometry.pushVertex(glm::vec3(this->getX() - 100, this->getY() + 100, 25));
  this->geometry.pushVertex(glm::vec3(this->getX(), this->getY() + 100, 25));
  this->geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->geometry.pushUv(glm::vec2(0.0f, 1.0f));
  this->geometry.build();

  /*
   this->geometry.pushVertex(glm::vec3(this->getX(), this->getY(), 25));
  this->geometry.pushVertex(glm::vec3(this->getX() + 100, this->getY(), 25));
  this->geometry.pushVertex(glm::vec3(this->getX() + 100, this->getY() + 100, 25));
  this->geometry.pushVertex(glm::vec3(this->getX(), this->getY() + 100, 25));
  */
  return true;
}

void		Slide::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  // On bind la texture pour dire que l'on veux l'utiliser
  this->texture.bind();
  // Et on dessine notre cube
  this->geometry.draw(shader, getTransformation(), GL_QUADS);
}
