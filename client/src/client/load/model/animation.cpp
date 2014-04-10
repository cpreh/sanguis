#include <sanguis/client/load/model/animation.hpp>
#include <sanguis/client/load/model/global_parameters.hpp>
#include <sanguis/client/load/model/make_series.hpp>
#include <sanguis/client/load/model/make_sound.hpp>
#include <sanguis/client/load/model/make_texture.hpp>
#include <sanguis/client/load/model/optional_sound.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sanguis/model/animation.hpp>


sanguis::client::load::model::animation::animation(
	sanguis::model::animation const &_animation,
	sanguis::client::load::model::global_parameters const &_parameters
)
:
	texture_(
		sanguis::client::load::model::make_texture(
			_parameters
		)
	),
	series_(
		sanguis::client::load::model::make_series(
			_animation,
			_parameters,
			*texture_
		)
	),
	sound_(
		sanguis::client::load::model::make_sound(
			_animation.animation_sound(),
			_parameters.sounds()
		)
	)
{
}

sanguis::client::load::model::animation::~animation()
{
}

sanguis::client::load::resource::animation::series const &
sanguis::client::load::model::animation::series() const
{
	return
		series_;
}

sanguis::client::load::model::optional_sound const &
sanguis::client::load::model::animation::sound() const
{
	return
		sound_;
}
