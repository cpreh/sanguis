#ifndef SANGUIS_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/object_fwd.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <sanguis/model/part_map.hpp>
#include <sanguis/model/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace model
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	SANGUIS_MODEL_SYMBOL
	object(
		sanguis::model::cell_size,
		sanguis::model::optional_animation_delay,
		sanguis::model::part_map &&,
		sanguis::model::optional_image_name const &
	);

	SANGUIS_MODEL_SYMBOL
	object(
		object &&
	);

	SANGUIS_MODEL_SYMBOL
	object &
	operator=(
		object &&
	);

	SANGUIS_MODEL_SYMBOL
	~object();

	SANGUIS_MODEL_SYMBOL
	sanguis::model::optional_animation_delay const
	animation_delay() const;

	SANGUIS_MODEL_SYMBOL
	void
	animation_delay(
		sanguis::model::optional_animation_delay
	);

	SANGUIS_MODEL_SYMBOL
	sanguis::model::part &
	part(
		fcppt::string const &
	);

	SANGUIS_MODEL_SYMBOL
	sanguis::model::part const &
	part(
		fcppt::string const &
	) const;

	SANGUIS_MODEL_SYMBOL
	sanguis::model::part &
	operator[](
		fcppt::string const &
	);

	SANGUIS_MODEL_SYMBOL
	sanguis::model::part_map const &
	parts() const;

	SANGUIS_MODEL_SYMBOL
	sanguis::model::cell_size const
	cell_size() const;

	SANGUIS_MODEL_SYMBOL
	sanguis::model::optional_image_name const &
	image_name() const;
private:
	sanguis::model::cell_size cell_size_;

	sanguis::model::optional_animation_delay animation_delay_;

	sanguis::model::part_map parts_;

	sanguis::model::optional_image_name image_name_;
};

}
}

#endif
