#ifndef	MENU_HPP_
# define MENU_HPP_

#include "AObject.hpp"
#include "Core.hpp"

class	Menu : public gdl::Game
{
private:
  gdl::Clock		_clock;
  gdl::Input		_input;
  gdl::SdlContext	_context;
  gdl::BasicShader	_shader;
  int			    _deep;
  int			    _numberofplayer;
  int			    _pos;
  std::vector<AObject*> _level1;
  std::vector<AObject*> _level2;

public:
  Menu(gdl::Clock const &clock, gdl::Input const &input, gdl::SdlContext const &context, gdl::BasicShader const &shader);
  virtual	~Menu();
  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();
  int		getDeep();
  int		getNumberPlayer();
  int		getPos();
  void		setDeep(int);
  void		setNumberPlayer(int);
  void		setPos(int);
};

#endif
