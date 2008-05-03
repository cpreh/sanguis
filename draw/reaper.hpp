#ifndef SANGUIS_DRAW_REAPER_HPP_INCLUDED
#define SANGUIS_DRAW_REAPER_HPP_INCLUDED

#include "player.hpp"

namespace sanguis
{
namespace draw
{

class reaper : public model 
{
public:
	reaper(entity_id id,player const &);
private:
	void update(time_type);
	const player &p;
	sge::space_unit current_health;
	sge::space_unit target_health;
	bool inited;
};

}
}

#endif
