#include "player.hpp"
#include "../entities/player.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::player(
	entities::model::parameters const &_param
)
{
	return
		entities::auto_ptr(
			new entities::player(
				_param
			)
		);
}
