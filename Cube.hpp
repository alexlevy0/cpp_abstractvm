#ifndef		CUBE_HPP_
#define		CUBE_HPP_

#include	"AObject.hpp"

class Cube : public AObject
{
private:
  gdl::Texture	  _texture;
  gdl::Geometry   _geometry;
  double	      _x;
  double	      _z;
  std::string	  _path;
  e_bloc	      _type;

public:
  Cube(int const x, int const z, const std::string &path, e_bloc const type)
  {
    _x = x;
    _z = z;
    _path = path;
    _type = type;
  }
  virtual	~Cube() {

  }
  void		setType(e_bloc const type) {
    this->_type = type;
  }
  e_bloc	getType() const {
    return (this->_type);
  }
  void		setX(double const &dir) {
    this->_x = this->_x + dir;
  }
  void		setZ(double const &dir) {
    this->_z = this->_z + dir;
  }
  bool		initialize() {
    if (_texture.load(_path) == false) {
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }
    //ajouter un vertex à votre instance de l’objet Geometry
    _geometry.pushVertex(glm::vec3(this->_x, 0, this->_z));
    _geometry.pushVertex(glm::vec3(this->_x, 1, this->_z));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 1, this->_z)); //+1 ? pourquoi
    _geometry.pushVertex(glm::vec3(this->_x + 1, 0, this->_z));

    //set les coordonnées relatives de texture sur la surface.
    _geometry.pushUv(glm::vec2(0.0f, 0.0f)); //haut gauche
    _geometry.pushUv(glm::vec2(1.0f, 0.0f)); //bas gauche
    _geometry.pushUv(glm::vec2(1.0f, 1.0f)); //bas droite
    _geometry.pushUv(glm::vec2(0.0f, 1.0f)); //haut droite
/**/
    _geometry.pushVertex(glm::vec3(this->_x, 0, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x, 1, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 1, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 0, this->_z + 1));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
/**/
    _geometry.pushVertex(glm::vec3(this->_x, 0, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x, 1, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x, 1, this->_z));
    _geometry.pushVertex(glm::vec3(this->_x, 0, this->_z));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
/**/
    _geometry.pushVertex(glm::vec3(this->_x + 1, 0, this->_z));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 1, this->_z));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 1, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 0, this->_z + 1));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
/**/
    _geometry.pushVertex(glm::vec3(this->_x, 0, this->_z));
    _geometry.pushVertex(glm::vec3(this->_x, 1, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 1, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 0, this->_z));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
/**/
    _geometry.pushVertex(glm::vec3(this->_x, 1, this->_z + 1));
    _geometry.pushVertex(glm::vec3(this->_x, 1, this->_z));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 1, this->_z));
    _geometry.pushVertex(glm::vec3(this->_x + 1, 1, this->_z + 1));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
/**/
    _geometry.build();
    return (true);
  }

  void draw(gdl::AShader &shader, gdl::Clock const &clock)
  {
    (void)clock;

    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
  double	getX() const
  {
    return (this->_x);
  }
  double	getZ() const
  {
    return (this->_z);
  }
};

#endif		/* CUBE_HPP_ */
