#include "part.hpp"
#include "find_texture.hpp"
#include "get_entry.hpp"
#include "global_parameters.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/algorithm/find_exn.hpp>
#include <sge/log/headers.hpp>
#include <sge/optional_impl.hpp>
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <boost/tr1/array.hpp>
#include <boost/foreach.hpp>
#include <iterator>
#include <utility>

namespace
{

typedef std::tr1::array<
	sge::string,
	sanguis::weapon_type::size
> weapon_type_array;

weapon_type_array const weapon_types = {
{
	SGE_TEXT("none"),
	SGE_TEXT("melee"),
	SGE_TEXT("pistol"),
	SGE_TEXT("dual_pistols"),
	SGE_TEXT("shotgun"),
	SGE_TEXT("rocket_launcher")
} };

sanguis::weapon_type::type
find_weapon_type(
	sge::string const &str)
{
	return static_cast<
		sanguis::weapon_type::type
	>(
		std::distance(
			weapon_types.begin(),
			sge::algorithm::find_exn(
				weapon_types.begin(),
				weapon_types.end(),
				str
			)
		)
	);
}

}

sanguis::load::model::weapon_category const &
sanguis::load::model::part::operator[](
	weapon_type::type const t) const
{
	category_map::const_iterator const it(
		categories.find(t));
	if(it != categories.end())
		return it->second;
	if(t == weapon_type::none)
		throw exception(
			SGE_TEXT("Unarmed weapon model missing in TODO")
		);
	return (*this)[weapon_type::none];
}

sanguis::load::model::part::part(
	sge::parse::json::object const &object,
	global_parameters const &param)
:
	categories()
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
		get_entry<
			sge::parse::json::array
		>(
			members,
			SGE_TEXT("weapon_categories")
		).elements
	)
	{
		sge::parse::json::member const &member(
			sge::parse::json::get<
				sge::parse::json::object
			>(
				r
			).members.at(0)
		);
			
		if(	
			categories.insert(
				std::make_pair(
					find_weapon_type(
						member.name
					),
					weapon_category(
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
					<< SGE_TEXT("Double insert in part!")
			);
	}
}
