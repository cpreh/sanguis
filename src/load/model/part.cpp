#include <sanguis/exception.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/model/make_weapon_categories.hpp>
#include <sanguis/load/model/part.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <sanguis/load/model/weapon_category_map.hpp>
#include <fcppt/text.hpp>


sanguis::load::model::part::part(
	sanguis::model::part const &_part,
	sanguis::load::model::global_parameters const &_param
)
:
	categories_(
		sanguis::load::model::make_weapon_categories(
			_part,
			_param
		)
	)
{
}

sanguis::load::model::part::~part()
{
}

sanguis::load::model::weapon_category const &
sanguis::load::model::part::operator[](
	sanguis::optional_primary_weapon_type const _type
) const
{
	sanguis::load::model::weapon_category_map::const_iterator const it(
		categories_.find(
			_type
		)
	);

	if(
		it != categories_.end()
	)
		return
			*it->second;

	if(
		!_type
	)
		throw sanguis::exception(
			FCPPT_TEXT("Unarmed weapon model missing in TODO")
		);

	return
		(*this)[
			sanguis::optional_primary_weapon_type()
		];
}
