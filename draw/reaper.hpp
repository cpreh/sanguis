#ifndef SANGUIS_DRAW_REAPER_HPP_INCLUDED
#define SANGUIS_DRAW_REAPER_HPP_INCLUDED

#include "model.hpp"

namespace sanguis
{
namespace load
{
class context;
}
namespace draw
{

class reaper : public model {
public:
	reaper(
		load::context const &ctx,
		entity_id id,
		system &,
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
