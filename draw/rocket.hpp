#ifndef SANGUIS_DRAW_ROCKET_HPP_INCLUDED
#define SANGUIS_DRAW_ROCKET_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "bullet.hpp"
#include "funit.hpp"

namespace sanguis
{
namespace draw
{

class rocket : public bullet {
public:
	rocket(
		draw::environment const &,
		entity_id id,
		sge::string const &name,
		funit aoe);
private:
	void on_decay();

	funit const aoe;
};

}
}

#endif
