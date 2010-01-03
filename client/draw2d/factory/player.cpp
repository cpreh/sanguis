#include "player.hpp"
#include "../player.hpp"

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::player(
	environment const &env,
	entity_id const id
)
{
	return entity_auto_ptr(
		new draw::player(
			env,
			id
		)
	);
}
