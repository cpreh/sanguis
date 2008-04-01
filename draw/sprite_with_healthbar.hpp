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
		const sge::sprite::point& pos,
		const sge::sprite::dim& dim,
		sge::virtual_texture_ptr tex,
		sge::sprite::rotation_type angle,
		const sge::math::vector2& speed,
		const sge::space_unit z,
		sge::space_unit health);
	void health(sge::space_unit);	
private:
	healthbar health_;
};

}
}

#endif
