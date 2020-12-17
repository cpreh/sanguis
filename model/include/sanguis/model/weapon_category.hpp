#ifndef SANGUIS_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include <sanguis/model/animation_fwd.hpp>
#include <sanguis/model/animation_map.hpp>
#include <sanguis/model/animation_name_fwd.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/symbol.hpp>
#include <sanguis/model/weapon_category_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace model
{

class weapon_category
{
	FCPPT_NONCOPYABLE(
		weapon_category
	);
public:
	weapon_category();

	weapon_category(
		sanguis::model::animation_map &&,
		sanguis::model::optional_image_name &&
	);

	SANGUIS_MODEL_SYMBOL
	weapon_category(
		weapon_category &&
	)
	noexcept;

	SANGUIS_MODEL_SYMBOL
	weapon_category &
	operator=(
		weapon_category &&
	)
	noexcept;

	SANGUIS_MODEL_SYMBOL
	~weapon_category();

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::animation &
	animation(
		sanguis::model::animation_name const &
	);

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::animation const &
	animation(
		sanguis::model::animation_name const &
	) const;

	SANGUIS_MODEL_SYMBOL
	void
	insert(
		sanguis::model::animation_name const &,
		sanguis::model::animation &&
	);

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::animation_map &
	animations();

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::animation_map const &
	animations() const;

	[[nodiscard]]
	SANGUIS_MODEL_SYMBOL
	sanguis::model::optional_image_name const &
	image_name() const;
private:
	sanguis::model::animation_map animations_;

	sanguis::model::optional_image_name image_name_;
};

}
}

#endif
