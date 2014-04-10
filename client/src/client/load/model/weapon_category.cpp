#include <sanguis/exception.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/animation.hpp>
#include <sanguis/client/load/model/animation_map.hpp>
#include <sanguis/client/load/model/base_animation_not_found.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/model/make_animations.hpp>
#include <sanguis/client/load/model/weapon_category.hpp>
#include <sanguis/model/weapon_category_fwd.hpp>
#include <fcppt/text.hpp>


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
	sanguis::client::load::model::animation_map::const_iterator const it(
		animations_.find(
			_anim
		)
	);

	if(
		it
		!=
		animations_.end()
	)
		return
			*it->second;

	if(
		_anim
		==
		sanguis::client::load::animation_type::none
	)
		throw
			sanguis::exception(
				FCPPT_TEXT("Default animation not found in TODO")
			);

	throw
		sanguis::client::load::model::base_animation_not_found(
			_anim
		);
}

bool
sanguis::client::load::model::weapon_category::has_animation(
	sanguis::client::load::animation_type const _anim
) const
{
	return
		animations_.find(
			_anim
		)
		!=
		animations_.end();
}
