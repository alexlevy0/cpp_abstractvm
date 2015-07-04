#ifndef AOBJECT_HPP_
#define AOBJECT_HPP_

// Permet d'inclure la SDL 2
#include <SdlContext.hh>

// Inclus la bibliotheque de mathematiques
#include <cstdlib>
#include <Game.hh>
#include <Clock.hh>
#include <Input.hh>
#include <SdlContext.hh>
#include <Geometry.hh>
#include <Texture.hh>
#include <BasicShader.hh>
#include <Model.hh>
#include <OpenGL.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum    e_bloc
{
  BOX = 'c',
  WALL = 'w',
  FIRE = 'f'
};

// La classe abstraite representant un objet avec sa position, sa rotation et son echelle
class AObject
{
protected:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;

public:
  AObject() : _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1) {  }
  virtual ~AObject() {}
  virtual void	        setType() {}
  virtual e_bloc        getType() const {return (BOX);}
  virtual bool		check_place() {return (true);}
  virtual bool		find_place() {return (true);}
  virtual void		LoadMap(const std::string &str) { (void)str;}
  virtual double	getX() {return (0);}
  virtual double	getZ() {return (0);}
  virtual int		getx() const {return (0);}
  virtual int		getz() const {return (0);}
  virtual float		getTime() const {return (0.0f);}
  virtual void		setX(double const &dir) {(void) dir;}
  virtual void		setZ(double const &dir) {(void) dir;}
  virtual void		setMap() {}
  virtual void		setMode() {}
  virtual std::string	getMap() {return ("");}
  virtual int		getMode() const {return (0);}
  virtual int		getStep() const {return (0);}
  virtual int		getPlayer() const {return (0);}

  virtual bool      initialize() { return (true); }
  virtual bool		update(gdl::Clock const &clock, gdl::Input &input)
  {
    (void) clock;
    (void) input;
    return (true);
  }
  virtual void      draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
  void              translate(glm::vec3 const &v)
  {
    _position += v;
  }
  void              rotate(glm::vec3 const& axis, float angle)
  {
    _rotation += axis * angle;
  }
  void scale(glm::vec3 const& scale)
  {
    _scale *= scale;
  }
  glm::mat4   getTransformation()
  {
    glm::mat4 transform(1); // On cree une matrice identite
    // On applique ensuite les rotations selon les axes x, y et z
    transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));

    // On effectue ensuite la translation
    transform = glm::translate(transform, _position);

    // Et pour finir, on fait la mise a l'echelle
    transform = glm::scale(transform, _scale);

    return (transform);
  }

};

#endif /* !AOBJECT_HPP_ */