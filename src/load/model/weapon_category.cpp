#include <sanguis/animation_type.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/model/animation.hpp>
#include <sanguis/load/model/base_animation_not_found.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/weapon_category.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef std::array<
	fcppt::string,
	static_cast<
		std::size_t
	>(
		sanguis::animation_type::size
	)
> animation_type_array;

animation_type_array const animation_types{{
	FCPPT_TEXT("none"),
	FCPPT_TEXT("attacking"),
	FCPPT_TEXT("walking"),
	FCPPT_TEXT("dying"),
	FCPPT_TEXT("deploying"),
	FCPPT_TEXT("reloading")
}};

sanguis::animation_type
find_animation_type(
	fcppt::string const &_str
)
{
	return
		static_cast<
			sanguis::animation_type
		>(
			std::distance(
				animation_types.begin(),
				fcppt::algorithm::find_exn(
					animation_types.begin(),
					animation_types.end(),
					_str
				)
			)
		);
}

}

sanguis::load::model::animation const &
sanguis::load::model::weapon_category::operator[](
	sanguis::animation_type const _anim
) const
{
	animation_map::const_iterator const
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
		_anim == sanguis::animation_type::none
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
	sanguis::animation_type const _anim
) const
{
	animation_map::const_iterator const
		it(
			animations_.find(
				_anim
			)
		);

	return
		it != animations_.end();
}

sanguis::load::model::weapon_category::~weapon_category()
{
}

sanguis::load::model::weapon_category::weapon_category(
	sge::parse::json::object const &_object,
	sanguis::load::model::global_parameters const &_param
)
:
	animations_()
{
	sge::parse::json::member_map const &members(
		_object.members
	);

	optional_texture_identifier const texture(
		model::find_texture(
			members
		)
	);

	sge::parse::json::array const &animations_array(
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			members	,
			FCPPT_TEXT("animations")
		)
	);

	for(
		auto const &entry : animations_array.elements
	)
	{
		sge::parse::json::member_map const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				entry
			).members
		);

		if(
			inner_members.size() != 1
		)
			throw sanguis::exception(
				FCPPT_TEXT("inner members of the animation array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			*inner_members.begin()
		);

		if(
			fcppt::container::ptr::insert_unique_ptr_map(
				animations_,
				find_animation_type(
					member.first
				),
				fcppt::make_unique_ptr<
					sanguis::load::model::animation
				>(
					sge::parse::json::get<
						sge::parse::json::object
					>(
						member.second
					),
					_param.new_texture(
						texture
					)
				)
			).second == false
		)
			FCPPT_LOG_WARNING(
				log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in weapon_category!")
			);
	}
}
