#include "sprite_with_healthbar.hpp"
#include "../client/id_dont_care.hpp"

sanguis::draw::sprite_with_healthbar::sprite_with_healthbar(
	const entity_id id,
	const sge::math::vector2& speed,
	const sge::sprite::object& master_,
	const relative_pos::type relative,
	const sge::space_unit health,
	const sge::space_unit max_health)
: sprite(
	id,
	speed,
	master_,
	relative),
  healthbar_(
  	client::id_dont_care(),	
	master().pos(),
	master().size(),
  	health,
	max_health)
{}

void sanguis::draw::sprite_with_healthbar::health(
	const sge::space_unit health)
{
	healthbar_.health(health);
}

void sanguis::draw::sprite_with_healthbar::max_health(
	const sge::space_unit max_health)
{
	healthbar_.max_health(max_health);
}
