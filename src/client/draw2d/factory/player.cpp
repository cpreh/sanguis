#include <sanguis/client/draw2d/factory/player.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::player(
	entities::model::parameters const &_param
)
{
	return
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::player
			>(
				_param
			)
		);
}
