#include "simple_creep.hpp"
#include "resource_factory.hpp"
#include "z_ordering.hpp"
#include "animation_pack.hpp"

sanguis::draw::simple_creep::simple_creep(
	const entity_id id,
	sge::sprite::point const& pos,
	sge::math::vector2 const& speed,
	const sge::sprite::rotation_type rot,
	animation_pack const& animations)
: sprite(
	id,
	speed,
	sge::sprite::object(
		pos,
		boost::none,
		boost::none,
		boost::none,
		z_ordering::player_upper, // FIXME
		rot),
	relative_pos::center),
  walk_animation(
  	resource::animation(
		animations.walk()),
	&at(0)),
  attack_animation(
  	resource::animation(
 	 	animations.attack()),
	&at(0)),
  die_animation(
  	resource::animation(
		animations.die()),
	&at(0))
{}
