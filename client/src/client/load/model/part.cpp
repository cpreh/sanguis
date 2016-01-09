#include <sanguis/exception.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/model/make_weapon_categories.hpp>
#include <sanguis/client/load/model/part.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sanguis/client/load/model/weapon_category_map.hpp>
#include <sanguis/client/load/model/weapon_category_unique_ptr.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/maybe.hpp>


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
		fcppt::optional::maybe(
			fcppt::container::find_opt_mapped(
				categories_,
				_type
			),
			[
				_type,
				this
			]()
			{
				sanguis::optional_primary_weapon_type const fallback{};

				if(
					_type
					==
					fallback
				)
					throw
						sanguis::exception{
							FCPPT_TEXT("Unarmed weapon model missing in TODO")
						};

				return
					fcppt::make_cref(
						(*this)[
							fallback
						]
					);
			},
			[](
				fcppt::reference_wrapper<
					sanguis::client::load::model::weapon_category_unique_ptr const
				> const _found
			)
			{
				return
					fcppt::make_cref(
						*_found.get()
					);
			}
		).get();
}
