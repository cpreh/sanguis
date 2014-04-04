#ifndef SANGUIS_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_MODEL_ANIMATION_HPP_INCLUDED

#include <sanguis/model/animation_fwd.hpp>
#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace model
{

class animation
{
	FCPPT_NONCOPYABLE(
		animation
	);
public:
	SANGUIS_MODEL_SYMBOL
	animation(
		sanguis::model::animation_range,
		sanguis::model::optional_animation_delay,
		sanguis::model::optional_animation_sound const &,
		sanguis::model::optional_image_name const &
	);

	SANGUIS_MODEL_SYMBOL
	animation(
		animation &&
	);

	SANGUIS_MODEL_SYMBOL
	animation &
	operator=(
		animation &&
	);

	SANGUIS_MODEL_SYMBOL
	~animation();

	SANGUIS_MODEL_SYMBOL
	sanguis::model::animation_range const
	animation_range() const;

	SANGUIS_MODEL_SYMBOL
	sanguis::model::optional_animation_delay const
	animation_delay() const;

	SANGUIS_MODEL_SYMBOL
	void
	animation_delay(
		sanguis::model::optional_animation_delay
	);

	SANGUIS_MODEL_SYMBOL
	sanguis::model::optional_animation_sound const
	animation_sound() const;

	SANGUIS_MODEL_SYMBOL
	void
	animation_sound(
		sanguis::model::optional_animation_sound const &
	);

	SANGUIS_MODEL_SYMBOL
	sanguis::model::optional_image_name const &
	image_name() const;
private:
	sanguis::model::animation_range animation_range_;

	sanguis::model::optional_animation_delay animation_delay_;

	sanguis::model::optional_animation_sound animation_sound_;

	sanguis::model::optional_image_name image_name_;
};

}
}

#endif
