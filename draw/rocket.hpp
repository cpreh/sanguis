#ifndef SANGUIS_DRAW_ROCKET_HPP_INCLUDED
#define SANGUIS_DRAW_ROCKET_HPP_INCLUDED

#include "bullet.hpp"

namespace sanguis
{
namespace draw
{

class environment;

class rocket : public bullet {
public:
	rocket(
		draw::environment const &,
		entity_id id,
		sge::string const &name);
private:
	void on_decay();
};

}
}

#endif
