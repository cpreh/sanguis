#include "weapon_category.hpp"
#include "base_animation_not_found.hpp"
#include "global_parameters.hpp"
#include "find_texture.hpp"
#include "animation/object.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <iterator>

namespace
{

typedef fcppt::container::array<
	fcppt::string,
	sanguis::animation_type::size
> animation_type_array;

animation_type_array const animation_types = {{
	FCPPT_TEXT("none"),
	FCPPT_TEXT("attacking"),
	FCPPT_TEXT("walking"),
	FCPPT_TEXT("dying"),
	FCPPT_TEXT("deploying"),
	FCPPT_TEXT("reloading")
}};

sanguis::animation_type::type
find_animation_type(
	fcppt::string const &_str
)
{
	return
		static_cast<
			sanguis::animation_type::type
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

sanguis::load::model::animation::object const &
sanguis::load::model::weapon_category::operator[](
	animation_type::type const _anim
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
		_anim == animation_type::none
	)
		throw sanguis::exception(
			FCPPT_TEXT("Default animation not found in TODO")
		);

	throw model::base_animation_not_found(
		_anim
	);
}

bool
sanguis::load::model::weapon_category::has_animation(
	animation_type::type const _anim
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
{}

sanguis::load::model::weapon_category::weapon_category(
	sge::parse::json::object const &_object,
	global_parameters const &_param
)
:
	animations_()
{
	sge::parse::json::member_vector const &members(
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
		sge::parse::json::element_vector::const_iterator it(
			animations_array.elements.begin()
		);
		it != animations_array.elements.end();
		++it
	)
	{
		sge::parse::json::member_vector const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				*it
			).members
		);

		if(
			inner_members.size() != 1
		)
			throw sanguis::exception(
				FCPPT_TEXT("inner members of the animation array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			inner_members[0]
		);

		if(
			fcppt::container::ptr::insert_unique_ptr_map(
				animations_,
				find_animation_type(
					member.name
				),
				fcppt::make_unique_ptr<
					animation::object
				>(
					sge::parse::json::get<
						sge::parse::json::object
					>(
						member.value
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
