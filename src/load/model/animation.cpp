#include <sanguis/load/model/animation.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_series.hpp>
#include <sanguis/load/model/make_sound.hpp>
#include <sanguis/load/model/make_texture.hpp>
#include <sanguis/load/model/optional_sound.hpp>
#include <sanguis/load/resource/animation/series.hpp>
#include <sanguis/model/animation.hpp>


sanguis::load::model::animation::animation(
	sanguis::model::animation const &_animation,
	sanguis::load::model::global_parameters const &_parameters
)
:
	texture_(
		sanguis::load::model::make_texture(
			_parameters
		)
	),
	series_(
		sanguis::load::model::make_series(
			_animation,
			_parameters,
			*texture_
		)
	),
	sound_(
		sanguis::load::model::make_sound(
			_animation.animation_sound(),
			_parameters.sounds()
		)
	)
{
}

sanguis::load::model::animation::~animation()
{
}

sanguis::load::resource::animation::series const &
sanguis::load::model::animation::series() const
{
	return
		series_;
}

sanguis::load::model::optional_sound const &
sanguis::load::model::animation::sound() const
{
	return
		sound_;
}
