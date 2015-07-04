//
// Created by levy_b on 6/3/15.
//

#ifndef CPP_BOMBERMAN_COREMAP_H
#define CPP_BOMBERMAN_COREMAP_H

#include  <iostream>
#include  <vector>
#include  <fstream>
#include  "Core.hpp"


class CoreMap {
private:
	std::vector<std::vector<AObject*> >     _map;
	int			      			            _x;
	int						                _z;
	gdl::Texture					        _texture;
	gdl::Geometry					        _geometry;
	//float						            _speed;
	std::string					            _filename;

public:
	CoreMap(const std::string &);
	~CoreMap();
	int						                getX() const;
	int						                getZ() const;
	std::vector<std::vector<AObject*> >		getMap() const;
	void						            SetX(unsigned int const &);
	void						            SetZ(unsigned int const &);
	void						SetElement(const unsigned int &, const unsigned int &, AObject*);
	bool						loadmap();
};


#endif //CPP_BOMBERMAN_COREMAP_H
