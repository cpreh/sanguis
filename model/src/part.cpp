#include <sanguis/model/exception.hpp>
#include <sanguis/model/optional_image.hpp>
#include <sanguis/model/part.hpp>
#include <sanguis/model/weapon_category_fwd.hpp>
#include <sanguis/model/weapon_category_map.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::model::part::part(
	sanguis::model::weapon_category_map &&_weapon_categories,
	sanguis::model::optional_image &&_image
)
:
	weapon_categories_(
		std::move(
			_weapon_categories
		)
	),
	image_(
		std::move(
			_image
		)
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
	fcppt::string const &_name
)
{
	return
		fcppt::container::find_exn(
			weapon_categories_,
			_name,
			[
				&_name
			]
			{
				return
					sanguis::model::exception{
						FCPPT_TEXT("No weapon category named ")
						+
						_name
					};
			}
		);
}

sanguis::model::weapon_category_map const &
sanguis::model::part::weapon_categories() const
{
	return
		weapon_categories_;
}
