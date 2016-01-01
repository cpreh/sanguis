#include <sanguis/model/exception.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part.hpp>
#include <sanguis/model/weapon_category_fwd.hpp>
#include <sanguis/model/weapon_category_map.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::model::part::part()
:
	weapon_categories_(),
	image_name_()
{
}

sanguis::model::part::part(
	sanguis::model::weapon_category_map &&_weapon_categories,
	sanguis::model::optional_image_name const &_image_name
)
:
	weapon_categories_(
		std::move(
			_weapon_categories
		)
	),
	image_name_(
		_image_name
	)
{
}

sanguis::model::part::part(
	part &&
) = default;

sanguis::model::part &
sanguis::model::part::operator=(
	part &&
) = default;

sanguis::model::part::~part()
{
}

sanguis::model::weapon_category &
sanguis::model::part::weapon_category(
	sanguis::model::weapon_category_name const &_name
)
{
	return
		fcppt::optional::to_exception(
			fcppt::container::find_opt_mapped(
				weapon_categories_,
				_name
			),
			[
				&_name
			]
			{
				return
					sanguis::model::exception{
						FCPPT_TEXT("No weapon category named ")
						+
						_name.get()
					};
			}
		);
}

sanguis::model::weapon_category const &
sanguis::model::part::weapon_category(
	sanguis::model::weapon_category_name const &_name
) const
{
	return
		const_cast<
			sanguis::model::part &
		>(
			*this
		).weapon_category(
			_name
		);
}

sanguis::model::weapon_category &
sanguis::model::part::operator[](
	sanguis::model::weapon_category_name const &_name
)
{
	return
		weapon_categories_[
			_name
		];
}

sanguis::model::weapon_category_map &
sanguis::model::part::weapon_categories()
{
	return
		weapon_categories_;
}

sanguis::model::weapon_category_map const &
sanguis::model::part::weapon_categories() const
{
	return
		weapon_categories_;
}

sanguis::model::optional_image_name const &
sanguis::model::part::image_name() const
{
	return
		image_name_;
}
