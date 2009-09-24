#include "weapon_category.hpp"
#include "base_animation_not_found.hpp"
#include "global_parameters.hpp"
#include "find_texture.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/filesystem/exists.hpp>
#include <sge/algorithm/find_exn.hpp>
#include <sge/log/headers.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <tr1/array>
#include <utility>
#include <iterator>

namespace
{

typedef std::tr1::array<
	sge::string,
	sanguis::animation_type::size
> animation_type_array;

animation_type_array const animation_types = {{
	SGE_TEXT("none"),
	SGE_TEXT("attacking"),
	SGE_TEXT("walking"),
	SGE_TEXT("dying"),
	SGE_TEXT("deploying"),
	SGE_TEXT("reloading")
}};

sanguis::animation_type::type
find_animation_type(
	sge::string const &str)
{
	return static_cast<
		sanguis::animation_type::type
	>(
		std::distance(
			animation_types.begin(),
			sge::algorithm::find_exn(
				animation_types.begin(),
				animation_types.end(),
				str
			)
		)
	);
}

}

sanguis::load::model::animation const &
sanguis::load::model::weapon_category::operator[](
	animation_type::type const anim) const
{
	animation_map::const_iterator const it(animations.find(anim));
	if(it != animations.end())
		return it->second;

	if(anim == animation_type::none)
		throw exception(
			SGE_TEXT("Default animation not found in TODO")
		);
	throw base_animation_not_found(
		anim);
}

sanguis::load::model::weapon_category::weapon_category(
	sge::parse::json::object const &object,
	global_parameters const &param)
:
	animations()
{
	sge::parse::json::member_vector const &members(
		object.members
	);

	optional_texture_identifier const texture(
		find_texture(
			members
		)
	);

	BOOST_FOREACH(
		sge::parse::json::element_vector::const_reference r,
		sge::parse::json::find_member<
			sge::parse::json::array
		>(
			members	,
			SGE_TEXT("animations")
		).elements
	)
	{
		sge::parse::json::member_vector const &inner_members(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				r
			).members
		);

		if(inner_members.size() != 1)
			throw exception(
				SGE_TEXT("inner members of the animation array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			inner_members[0]
		);

		if(
			animations.insert(
				std::make_pair(
					find_animation_type(
						member.name
					),
					animation(
						sge::parse::json::get<
							sge::parse::json::object
						>(
							member.value_
						),
						param.new_texture(
							texture
						)
					)
				)
			).second == false
		)
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< SGE_TEXT("Double insert in weapon_category!")
			);
	}
}
