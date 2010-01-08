#include "player.hpp"
#include "../entities/player.hpp"

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::player(
	entities::model::parameters const &param_
)
{
	return entity_auto_ptr(
		new draw::player(
			param
		)
	);
}
