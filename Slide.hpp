#ifndef SLIDE_HPP_
# define SLIDE_HPP_

#include <iostream>
#include "AObject.hpp"

class	Slide : public	AObject
{
private:
  gdl::Texture		texture;
  gdl::Geometry		geometry;
  std::string		imagename;
  double			x;
  double		y;

public:
  Slide(std::string const name, float const x, float const y);
  ~Slide();
  std::string	getImagename();
  double getX();
  double getY();
  bool		initialize();
  void		draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif
