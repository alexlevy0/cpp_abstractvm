#ifndef __BOMBER_HPP__
#define __BOMBER_HPP__

#include <cstdlib>
#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <string>

//Permet d'inclure la SDL 2
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>
#include <sstream>
#include <OpenGL.hh>
// Inclus la bibliotheque de mathematiques
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "AObject.hpp"
#include "Cube.hpp"
#include	"Map.hpp"
#include	"CoreMap.hpp"
#include	"Menu.hpp"
#include    "Marvin.hpp"

class Core : public gdl::Game
{
public:
    Core();
    ~Core();
    virtual bool initialize();
    virtual bool update();
	virtual void draw();
	bool    start(void);

private:
	gdl::Clock			_clock;
	gdl::Input			_input;
	gdl::SdlContext		_context;
	gdl::BasicShader	_shader;

	AObject*                            _sol;
	std::vector<std::vector<AObject*> >	_map;
	std::vector<AObject*>			    _personnage;
	std::vector<AObject*>			    _bomb;
	int					                _zmax;
	int					                _xmax;
	float					            _speed;
	//std::vector<AObject*>   _objects;
};

#endif /*! __BOMBER_HPP__ */

