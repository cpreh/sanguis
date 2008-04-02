#ifndef SANGUIS_DRAW_SIMPLE_CREEP_HPP_INCLUDED
#define SANGUIS_DRAW_SIMPLE_CREEP_HPP_INCLUDED

#include "sprite_with_healthbar.hpp"
#include <sge/string.hpp>
#include <sge/sprite/texture_animation.hpp>

namespace sanguis
{
namespace draw
{

class animation_pack;

class simple_creep : public sprite_with_healthbar {
public:
	simple_creep(
		entity_id id,
		sge::sprite::point const& pos,
		sge::math::vector2 const& speed,
		sge::sprite::rotation_type rot,
		animation_pack const& animations,
		sge::space_unit healt,
		sge::space_unit max_health
	);
private:
	sge::sprite::texture_animation
		walk_animation,
		attack_animation,
		die_animation;
};

}
}

#endif
