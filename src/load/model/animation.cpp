#include <sanguis/load/model/animation.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_series.hpp>
#include <sanguis/load/model/make_sound.hpp>
#include <sanguis/load/model/make_texture.hpp>
#include <sanguis/load/model/optional_sound.hpp>
#include <sanguis/load/resource/animation/series.hpp>


sanguis::load::model::animation::animation(
	sge::parse::json::object const &_json_object,
	sanguis::load::model::global_parameters const &_parameters
)
:
	texture_(
		sanguis::load::model::make_texture(
			_json_object,
			_parameters
		)
	),
	series_(
		sanguis::load::model::make_series(
			_json_object,
			_parameters,
			*texture_
		)
	),
	sound_(
		sanguis::load::model::make_sound(
			_json_object,
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
