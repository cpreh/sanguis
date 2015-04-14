#include <sanguis/exception.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/model/make_weapon_categories.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sanguis/client/load/model/weapon_category_map.hpp>
#include <sanguis/client/load/model/weapon_category_unique_ptr.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt.hpp>


sanguis::client::load::model::part::part(
	sanguis::model::part const &_part,
	sanguis::client::load::model::global_parameters const &_param
)
:
	categories_(
		sanguis::client::load::model::make_weapon_categories(
			_part,
			_param
		)
	)
{
}

sanguis::client::load::model::part::~part()
{
}

sanguis::client::load::model::weapon_category const &
sanguis::client::load::model::part::operator[](
	sanguis::optional_primary_weapon_type const _type
) const
{
	return
		fcppt::maybe(
			fcppt::container::find_opt(
				categories_,
				_type
			),
			[
				_type,
				this
			]()
			-> sanguis::client::load::model::weapon_category const &
			{
				if(
					!_type.has_value()
				)
					throw sanguis::exception(
						FCPPT_TEXT("Unarmed weapon model missing in TODO")
					);

				return
					(*this)[
						sanguis::optional_primary_weapon_type()
					];
			},
			[](
				sanguis::client::load::model::weapon_category_unique_ptr const &_found
			)
			-> sanguis::client::load::model::weapon_category const &
			{
				return
					*_found;
			}
		);
}
