//
// Created by levy_b on 6/9/15.
//

#include "Marvin.hpp"

Marvin::Marvin(std::vector<std::vector<AObject*> > const &map, std::vector<AObject*> const &personnage, const int &player)
{
	if (!this->find_place(map, personnage))
	{
		std::cout << "cannot find a place for the player" << std::endl;
		return ;
	}
	scale(glm::vec3(0.0025, 0.0025, 0.0025));
	translate(glm::vec3(_x + 0.5, 0, _z + 0.5));
	_speed = 5.0;
	_player = player;
	_dir = DOWN;
}

Marvin::~Marvin() { }

bool		Marvin::initialize()
{
	if (_model.load("./assets/marvin_lite.fbx") == false) {
		std::cout << "Impossible de charger le model !" << std::endl;
		return (false);
	}
	_model.setCurrentAnim(0);
	return (true);
}

bool        Marvin::update(gdl::Clock const &clock, gdl::Input &input) {
	int		up;
	int		down;
	int		right;
	int		left;
	double posActuX;
	double posActuZ;

	posActuX = getX();
	posActuZ = getZ();

	if (_player == 2) {
		up = SDLK_z;
		down = SDLK_s;
		right = SDLK_d;
		left = SDLK_q;
	}
	if (_player == 1) {
		up = SDLK_UP;
		down = SDLK_DOWN;
		right = SDLK_RIGHT;
		left = SDLK_LEFT;
	}

	if (input.getKey(up))
	{
		if (_dir != UP)
		{
			setX(0);
			setZ(0);
			rotate(glm::vec3(0, 1, 0), this->getAngle(_dir, UP));
			_dir = UP;
			setX(posActuX);
			setZ(posActuZ);
		}
		this->setZ(this->_z - (static_cast<float>(clock.getElapsed()) * _speed));
		translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
	}

	if (input.getKey(down))
	{
		if (_dir != DOWN)
		{
			setX(0);
			setZ(0);

			rotate(glm::vec3(0, 1, 0), this->getAngle(_dir, DOWN));
			_dir = DOWN;
			setX(posActuX);
			setZ(posActuZ);

		}
		this->setZ(this->_z + (static_cast<float>(clock.getElapsed()) * _speed));
		translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
	}

	if (input.getKey(left))
	{
		if (_dir != LEFT)
		{
			setX(0);
			setZ(0);

			rotate(glm::vec3(0, 1, 0), this->getAngle(_dir, LEFT));
			_dir = LEFT;
			setX(posActuX);
			setZ(posActuZ);

		}
		this->setX(this->_x - (static_cast<float>(clock.getElapsed()) * _speed));
		translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
	}

	if (input.getKey(right))
	{
			if (_dir != RIGHT)
		{
			setX(0);
			setZ(0);
			rotate(glm::vec3(0, 1, 0), this->getAngle(_dir, RIGHT));
			_dir = RIGHT;
			setX(posActuX);
			setZ(posActuZ);

		}
		this->setX(this->_x + (static_cast<float>(clock.getElapsed()) * _speed));
		translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
	}
return (true);
}

bool    Marvin::check_place(std::vector<AObject *> const &perso, const int &x, const int z)
{
	for (size_t i = 0; i < perso.size(); ++i)
	{
		if (perso[i] && perso[i]->getX() == x && perso[i]->getZ() == z)
			return (false);
	}
	return (true);
}

bool	Marvin::find_place(std::vector<std::vector<AObject*> > const &map, std::vector<AObject*> const &personnage)
{
	for (unsigned int z = 0; z < map.size(); ++z)
	{
		for (unsigned int x = 0; x < map[z].size(); ++x)
		{
			int count_freecase = 0;

			if (x > 0 && !map[z][x - 1] && check_place(personnage, x - 1, z))
				count_freecase += 1;
			if (x < map[z].size() && !map[z][x + 1] && check_place(personnage, x + 1, z))
				count_freecase += 1;
			if (z > 0 && !map[z - 1][x] && check_place(personnage, x, z - 1))
				count_freecase += 1;
			if (z < map.size() && !map[z + 1][x] && check_place(personnage, x, z + 1))
				count_freecase += 1;
			if (count_freecase >= 2 && !map[z][x] && check_place(personnage, x, z))
			{
				_x = x;
				_z = z;
				return (true);
			}
		}
	}
return (false);
}

int		Marvin::getAngle(eDirection const current_dir, eDirection const next_dir)
{
	switch (current_dir)
	{
		case UP:
		{
			if (next_dir == RIGHT)
				return (-90);
			else if (next_dir == DOWN)
				return (180);
			else if (next_dir == LEFT)
				return (90);
		}
		case RIGHT:
		{
			if (next_dir == UP)
				return (90);
			else if (next_dir == DOWN)
				return (-90);
			else if (next_dir == LEFT)
				return (180);
		}
		case DOWN:
		{
			if (next_dir == UP)
				return (180);
			else if (next_dir == RIGHT)
				return (90);
			else if (next_dir == LEFT)
				return (-90);
		}
		case LEFT:
		{
			if (next_dir == UP)
				return (-90);
			else if (next_dir == DOWN)
				return (90);
			else if (next_dir == RIGHT)
				return (180);
		}
	}
	return (0);
}

void    Marvin::draw(gdl::AShader &shader, gdl::Clock const &clock) {
	_model.draw(shader, getTransformation(), clock.getElapsed());
}

int     Marvin::getPlayer() const {
	return (this->_player);
}

double	Marvin::getX() {
	return (this->_x);
}

double	Marvin::getZ() {
	return (this->_z);
}

void	Marvin::setX(double const &x) {
	this->_x = x;
}

void	Marvin::setZ(double const &z) {
	this->_z = z;
}
