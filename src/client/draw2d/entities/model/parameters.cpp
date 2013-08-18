#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/colored/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/load/model/collection_fwd.hpp>


sanguis::client::draw2d::entities::model::parameters::parameters(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::client::sound_manager &_sound_manager,
	sanguis::client::draw2d::sprite::colored::system &_colored_system,
	sanguis::client::draw2d::sprite::normal::system &_normal_system,
	sanguis::load::model::collection const &_collection
)
:
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	sound_manager_(
		_sound_manager
	),
	colored_system_(
		_colored_system
	),
	normal_system_(
		_normal_system
	),
	collection_(
		_collection
	)
{
}

sanguis::diff_clock const &
sanguis::client::draw2d::entities::model::parameters::diff_clock() const
{
	return diff_clock_;
}

sanguis::client::sound_manager &
sanguis::client::draw2d::entities::model::parameters::sound_manager() const
{
	return sound_manager_;
}

sanguis::random_generator &
sanguis::client::draw2d::entities::model::parameters::random_generator() const
{
	return random_generator_;
}

sanguis::client::draw2d::sprite::colored::system &
sanguis::client::draw2d::entities::model::parameters::colored_system() const
{
	return colored_system_;
}

sanguis::client::draw2d::sprite::normal::system &
sanguis::client::draw2d::entities::model::parameters::normal_system() const
{
	return normal_system_;
}

sanguis::load::model::collection const &
sanguis::client::draw2d::entities::model::parameters::collection() const
{
	return collection_;
}
