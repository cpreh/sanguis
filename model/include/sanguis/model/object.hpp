#ifndef SANGUIS_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/object_fwd.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <sanguis/model/part_map.hpp>
#include <sanguis/model/part_name_fwd.hpp>
#include <sanguis/model/symbol.hpp>
#include <fcppt/noncopyable.hpp>


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
		sanguis::model::optional_image_name &&
	);

	SANGUIS_MODEL_SYMBOL
	object(
		object &&
	)
	noexcept;

	SANGUIS_MODEL_SYMBOL
	object &
	operator=(
		object &&
	)
	noexcept;

	SANGUIS_MODEL_SYMBOL
	~object();

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::optional_animation_delay
	animation_delay() const;

	SANGUIS_MODEL_SYMBOL
	void
	animation_delay(
		sanguis::model::optional_animation_delay
	);

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::part &
	part(
		sanguis::model::part_name const &
	);

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::part const &
	part(
		sanguis::model::part_name const &
	) const;

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::part &
	operator[](
		sanguis::model::part_name const &
	);

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::part_map &
	parts();

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::part_map const &
	parts() const;

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::cell_size
	cell_size() const;

	[[nodiscard]]
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
