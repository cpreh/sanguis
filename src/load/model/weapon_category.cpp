#include <sanguis/exception.hpp>
#include <sanguis/load/animation_type.hpp>
#include <sanguis/load/model/animation.hpp>
#include <sanguis/load/model/animation_map.hpp>
#include <sanguis/load/model/base_animation_not_found.hpp>
#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/model/make_animations.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/text.hpp>


sanguis::load::model::weapon_category::weapon_category(
	sge::parse::json::object const &_object,
	sanguis::load::model::global_parameters const &_param
)
:
	animations_(
		sanguis::load::model::make_animations(
			_object,
			_param
		)
	)
{
}

sanguis::load::model::weapon_category::~weapon_category()
{
}

sanguis::load::model::animation const &
sanguis::load::model::weapon_category::operator[](
	sanguis::load::animation_type const _anim
) const
{
	sanguis::load::model::animation_map::const_iterator const
		it(
			animations_.find(
				_anim
			)
		);

	if(
		it != animations_.end()
	)
		return *it->second;

	if(
		_anim == sanguis::load::animation_type::none
	)
		throw sanguis::exception(
			FCPPT_TEXT("Default animation not found in TODO")
		);

	throw sanguis::load::model::base_animation_not_found(
		_anim
	);
}

bool
sanguis::load::model::weapon_category::has_animation(
	sanguis::load::animation_type const _anim
) const
{
	return
		animations_.find(
			_anim
		)
		!=
		animations_.end();
}
