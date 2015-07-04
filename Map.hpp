//
// Created by levy_b on 6/3/15.
//

#ifndef CPP_BOMBERMAN_MAP_HPP
#define CPP_BOMBERMAN_MAP_HPP

#ifndef			MAP_HPP_
# define		MAP_HPP_

#include		"Cube.hpp"

class Map : public AObject
{
private:
	gdl::Texture _texture;
	gdl::Geometry _geometry;
	int	_x;
	int	_z;

public:
	Map(int const x, int const  z)
	{
		this->_x = x;
		this->_z = z;
	}
	virtual	~Map() { }
	bool		initialize()
	{
		if (_texture.load("./assets/sol.tga") == false)
		{
			std::cerr << "Cannot load the map texture" << std::endl;
			return (false);
		}

		_geometry.pushVertex(glm::vec3(_x, 0, 0));
		_geometry.pushVertex(glm::vec3(_x, 0, _z));
		_geometry.pushVertex(glm::vec3(0, 0, _z));
		_geometry.pushVertex(glm::vec3(0, 0, 0));

		_geometry.pushUv(glm::vec2(0.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 0.0f));
		_geometry.pushUv(glm::vec2(1.0f, 1.0f));
		_geometry.pushUv(glm::vec2(0.0f, 1.0f));

		_geometry.build();
		return (true);
	}

	void draw(gdl::AShader &shader, gdl::Clock const &clock)
	{
		(void)clock;
		_texture.bind();
		_geometry.draw(shader, getTransformation(), GL_QUADS);
	}
};

#endif		/* MAP_HPP_ */


#endif //CPP_BOMBERMAN_MAP_HPP
