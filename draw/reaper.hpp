#ifndef SANGUIS_DRAW_REAPER_HPP_INCLUDED
#define SANGUIS_DRAW_REAPER_HPP_INCLUDED

#include "model.hpp"

namespace sanguis
{
namespace draw
{

class environment;

class reaper : public model {
public:
	reaper(
		draw::environment const &,
		entity_id id,
		draw::system &,
		model const &);
	void update(time_type);
private:
	model const &p;
	funit
		current_health,
		target_health;
	bool inited;
};

}
}

#endif
