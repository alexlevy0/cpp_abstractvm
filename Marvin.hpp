//
// Created by levy_b on 6/9/15.
//

#ifndef CPP_BOMBERMAN_MARVIN_H
#define CPP_BOMBERMAN_MARVIN_H

#include	<Model.hh>
#include	"Map.hpp"

enum	eDirection
{
	UP = 1,
	RIGHT = 2,
	LEFT = 3,
	DOWN = 4
};

class Marvin : public AObject {
private:
//	gdl::Texture		_texture;
	gdl::Model		    _model;
	float			    _speed;
	double		        _x;
	double		        _z;
	eDirection		    _dir;
	int			        _player;

public:
	Marvin(std::vector<std::vector<AObject*> > const &map, std::vector<AObject*> const &personnage, const int &player);
	~Marvin();
	bool		    initialize();
	virtual bool    update(gdl::Clock const &clock, gdl::Input &input);
	void            draw(gdl::AShader &shader, gdl::Clock const &clock);
	int	            getPlayer() const;
	int		        getAngle(eDirection const current_dir, eDirection const next_dir);
	bool	        find_place(std::vector<std::vector<AObject*> > const &map, std::vector<AObject*> const &personnage);
	bool            check_place(std::vector<AObject *> const &perso, const int &x, const int z);
	double	getX();
	double	getZ();
	void	setX(double const &x);
	void	setZ(double const &z);
};

#endif //CPP_BOMBERMAN_MARVIN_H
