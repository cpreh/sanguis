#ifndef SANGUIS_DRAW_REAPER_HPP_INCLUDED
#define SANGUIS_DRAW_REAPER_HPP_INCLUDED

#include "model.hpp"

namespace sanguis
{
namespace draw
{

class player;

class reaper : public model {
public:
	reaper(
		entity_id id,
		system &,
		player const &);
private:
	void update(time_type);
	player const &p;
	sge::space_unit current_health;
	sge::space_unit target_health;
	bool inited;
};

}
}

#endif
