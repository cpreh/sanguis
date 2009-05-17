#ifndef SANGUIS_DRAW_GRENADE_HPP_INCLUDED
#define SANGUIS_DRAW_GRENADE_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "model.hpp"

namespace sanguis
{
namespace draw
{

class grenade : public model {
public:
	grenade(
		draw::environment const &,
		entity_id,
		sge::string const &name);
private:
	void on_decay();
};

}
}

#endif
