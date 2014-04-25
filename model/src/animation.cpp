#include <sanguis/model/animation.hpp>
#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/optional_image_name.hpp>


sanguis::model::animation::animation(
	sanguis::model::animation_range const _animation_range,
	sanguis::model::optional_animation_delay const _animation_delay,
	sanguis::model::optional_animation_sound const &_animation_sound,
	sanguis::model::optional_image_name const &_image_name
)
:
	animation_range_{
		_animation_range
	},
	animation_delay_{
		_animation_delay
	},
	animation_sound_{
		_animation_sound
	},
	image_name_{
		_image_name
	}
{
}

sanguis::model::animation::animation(
	animation const &
) = default;

sanguis::model::animation::animation(
	animation &&
) = default;

sanguis::model::animation &
sanguis::model::animation::operator=(
	animation const &
) = default;

sanguis::model::animation &
sanguis::model::animation::operator=(
	animation &&
) = default;

sanguis::model::animation::~animation()
{
}

sanguis::model::animation_range const
sanguis::model::animation::animation_range() const
{
	return
		animation_range_;
}

sanguis::model::optional_animation_delay const
sanguis::model::animation::animation_delay() const
{
	return
		animation_delay_;
}

void
sanguis::model::animation::animation_delay(
	sanguis::model::optional_animation_delay const _animation_delay
)
{
	animation_delay_ =
		_animation_delay;
}

sanguis::model::optional_animation_sound const
sanguis::model::animation::animation_sound() const
{
	return
		animation_sound_;
}

void
sanguis::model::animation::animation_sound(
	sanguis::model::optional_animation_sound const &_animation_sound
)
{
	animation_sound_ =
		_animation_sound;
}

sanguis::model::optional_image_name const &
sanguis::model::animation::image_name() const
{
	return
		image_name_;
}
