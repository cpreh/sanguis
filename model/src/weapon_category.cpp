#include <sanguis/model/animation_fwd.hpp>
#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/animation_name.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/weapon_category.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::model::weapon_category::weapon_category()
:
	animations_(),
	image_name_()
{
}

sanguis::model::weapon_category::weapon_category(
	sanguis::model::animation_map &&_animations,
	sanguis::model::optional_image_name const &_image_name
)
:
	animations_(
		std::move(
			_animations
		)
	),
	image_name_(
		_image_name
	)
{
	if(
		animations_.count(
			sanguis::model::animation_name(
				FCPPT_TEXT("none")
			)
		)
		==
		0u
	)
		throw
			sanguis::model::exception(
				FCPPT_TEXT("None animation not available!")
			);
}

SANGUIS_MODEL_SYMBOL
sanguis::model::weapon_category::weapon_category(
	weapon_category &&
) = default;

SANGUIS_MODEL_SYMBOL
sanguis::model::weapon_category &
sanguis::model::weapon_category::operator=(
	weapon_category &&
) = default;

sanguis::model::weapon_category::~weapon_category()
{
}

sanguis::model::animation &
sanguis::model::weapon_category::animation(
	sanguis::model::animation_name const &_name
)
{
	return
		fcppt::container::find_exn(
			animations_,
			_name,
			[
				&_name
			]
			{
				return
					sanguis::model::exception{
						FCPPT_TEXT("No animation named ")
						+
						_name.get()
					};
			}
		);
}

sanguis::model::animation const &
sanguis::model::weapon_category::animation(
	sanguis::model::animation_name const &_name
) const
{
	return
		const_cast<
			sanguis::model::weapon_category &
		>(
			*this
		).animation(
			_name
		);
}

void
sanguis::model::weapon_category::insert(
	sanguis::model::animation_name const &_name,
	sanguis::model::animation &&_animation
)
{
	FCPPT_ASSERT_ERROR(
		animations_.insert(
			std::make_pair(
				_name,
				std::move(
					_animation
				)
			)
		).second
	);
}

sanguis::model::animation_map &
sanguis::model::weapon_category::animations()
{
	return
		animations_;
}

sanguis::model::animation_map const &
sanguis::model::weapon_category::animations() const
{
	return
		animations_;
}

sanguis::model::optional_image_name const &
sanguis::model::weapon_category::image_name() const
{
	return
		image_name_;
}
