#include <sanguis/exception.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/animation.hpp>
#include <sanguis/client/load/model/animation_unique_ptr.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/model/make_animations.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sanguis/model/weapon_category_fwd.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>


sanguis::client::load::model::weapon_category::weapon_category(
	sanguis::model::weapon_category const &_weapon_category,
	sanguis::client::load::model::global_parameters const &_param
)
:
	animations_(
		sanguis::client::load::model::make_animations(
			_weapon_category,
			_param
		)
	)
{
}

sanguis::client::load::model::weapon_category::~weapon_category()
{
}

sanguis::client::load::model::animation const &
sanguis::client::load::model::weapon_category::operator[](
	sanguis::client::load::animation_type const _anim
) const
{
	return
		fcppt::maybe(
			fcppt::container::find_opt_mapped(
				animations_,
				_anim
			),
			[
				this,
				_anim
			]()
			-> sanguis::client::load::model::animation const &
			{
				sanguis::client::load::animation_type const fallback(
					sanguis::client::load::animation_type::none
				);

				if(
					_anim
					==
					fallback
				)
					throw
						sanguis::exception{
							FCPPT_TEXT("Default animation missing in TODO")
						};

				return
					(*this)[
						fallback
					];
			},
			[](
				sanguis::client::load::model::animation_unique_ptr const &_animation
			)
			-> sanguis::client::load::model::animation const &
			{
				return
					*_animation;
			}
		);
}
