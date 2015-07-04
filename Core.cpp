#include 	"Core.hpp"

Core::Core()
{
    _speed = 5.0f;
}

Core::~Core()
{
    while (_personnage.size() > 0)
        _personnage.erase(_personnage.begin());
    /*
    while (_bomb.size() > 0)
        _bomb.erase(_bomb.begin());
    */
    for (size_t i = 0; i < _map.size(); ++i)
    {
        while (_map[i].size() > 0)
            _map[i].erase(_map[i].begin());
    }
    while (_map.size() > 0)
        _map.erase(_map.begin());
}

/* chargerez les différents assets (model 3D) */
bool    Core::initialize(void)
{
    if (!_context.start(800, 600, "My bomberman!")) // on cree une fenetre
      return false;

    // On active le test de profondeur d'OpenGL pour que les pixels que l'oeil ne voit pas ne s'affichent pas
    glEnable(GL_DEPTH_TEST);

    // On cree un shader, petit programme permettant de dessiner nos objets a l'ecran
    if (!_shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER) || !_shader.load("./shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
      return false;
    if (this->start() == false)
        return false;
    return true;
}

bool    Core::start()
{
    Menu  *menu = new Menu(_clock, _input, _context, _shader);
    if (menu->initialize() == false)
        return false;
    while (menu->update() == true)
        menu->draw();

    int numMap = menu->getPos() + 1;

    std::string map = "map2";
    CoreMap m(map);
    if (!m.loadmap())
        return (false);
    _zmax = m.getZ();
    _xmax = m.getX();
    _map = m.getMap();

    _sol = new Map(_xmax, _zmax);
    if (!_sol->initialize()) {
        return (false);
    }

    AObject *p = new Marvin(_map, _personnage, 1);
    if (!p->initialize())
        return (false);
    _personnage.push_back(p);

    if (menu->getNumberPlayer() == 2)
    {
        AObject *p2 = new Marvin(_map, _personnage, 2);
        if (!p2->initialize())
            return (false);
        _personnage.push_back(p2);
    }

    glm::mat4 projection;
    glm::mat4 transformation;
    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    double	x = p->getX();
    double	z = p->getZ();

    // La camera sera ici situee a la position 0, 20, -100 et regardera vers la position 0, 0, 0
//    transformation = glm::lookAt(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    transformation = glm::lookAt(glm::vec3(x, 10, z + 8), glm::vec3(x, 0, z), glm::vec3(0, 1, 0));

    _shader.bind();
    _shader.setUniform("view", transformation);
    _shader.setUniform("projection", projection);
  return (true);
}
bool    Core::update(void)
{
    if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
        return false;
    _context.updateClock(_clock);
    _context.updateInputs(_input);

    int dir = 0; //z   -1:AVANCE   +1:RECULE
    int dir2 = 0;// x  -1:GAUCHE   +1:DROITE
    int dir3 = 0; //z  -1:AVANCE   +1:RECULE
    int dir4 = 0; // x -1:GAUCHE   +1:DROITE

    if (_input.getKey(SDLK_UP))
        dir = -1;
    if (_input.getKey(SDLK_DOWN))
        dir = 1;
    if (_input.getKey(SDLK_LEFT))
        dir2 = -1;
    if (_input.getKey(SDLK_RIGHT)) {
        dir2 = 1;
    }

    if (_input.getKey(SDLK_z))
        dir3 = -1;
    if (_input.getKey(SDLK_s))
        dir3 = 1;
    if (_input.getKey(SDLK_q))
        dir4 = -1;
    if (_input.getKey(SDLK_d))
        dir4 = 1;

    if (dir != 0 || dir2 != 0)
        _personnage[0]->update(_clock, _input);
    if ((dir3 != 0 || dir4 != 0))
        _personnage[1]->update(_clock, _input);


    glm::mat4 projection;
    glm::mat4 transformation;

    double  x = _personnage[0]->getX();
    double  z = _personnage[0]->getZ();

    projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    //La position de la caméra (x,y,z)
    //Le point que l’on veut regarder
    //Un vecteur définissant dans quelle direction est le haut de la camera (0, 1, 0)

    transformation = glm::lookAt(glm::vec3(x, 10, z + 8), glm::vec3(x, 0, z), glm::vec3(0, 1, 0));

    _shader.bind();
    _shader.setUniform("view", transformation);
    _shader.setUniform("projection", projection);

    return (true);
}

void    Core::draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _shader.bind();
    _sol->draw(_shader, _clock);


    for (size_t i = 0; i < _personnage.size(); ++i) {
        _personnage[i]->draw(_shader, _clock);
    }
    for (size_t i = 0; i < _map.size(); ++i)
    {
        for (size_t j = 0; j < _map[i].size(); ++j)
            if (_map[i][j])
                _map[i][j]->draw(_shader, _clock);
    }

    _context.flush();
}
