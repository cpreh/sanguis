#ifndef SANGUIS_DRAW_SPRITE_WITH_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_WITH_HEALTHBAR_HPP_INCLUDED

#include "sprite.hpp"
#include "healthbar.hpp"

namespace sanguis
{
namespace draw
{

class sprite_with_healthbar : public sprite {
public:
	sprite_with_healthbar(
		entity_id,
		const sge::math::vector2& speed,
		const sge::sprite::object& master,
		relative_pos::type,
		sge::space_unit health,
		sge::space_unit max_health);
private:
	void health(sge::space_unit);
	void max_health(sge::space_unit);

	healthbar healthbar_;
};

}
}

#endif
