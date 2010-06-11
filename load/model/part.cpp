#include "part.hpp"
#include "find_texture.hpp"
#include "global_parameters.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/tr1/array.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <boost/foreach.hpp>
#include <iterator>
#include <utility>

namespace
{

typedef std::tr1::array<
	fcppt::string,
	sanguis::weapon_type::size
> weapon_type_array;

weapon_type_array const weapon_types = {
{
	FCPPT_TEXT("none"),
	FCPPT_TEXT("melee"),
	FCPPT_TEXT("pistol"),
	FCPPT_TEXT("dual_pistols"),
	FCPPT_TEXT("shotgun"),
	FCPPT_TEXT("rocket_launcher"),
	FCPPT_TEXT("grenade")
} };

sanguis::weapon_type::type
find_weapon_type(
	fcppt::string const &str)
{
	return static_cast<
		sanguis::weapon_type::type
	>(
		std::distance(
			weapon_types.begin(),
			fcppt::algorithm::find_exn(
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
	weapon_type::type const t
) const
{
	category_map::const_iterator const it(
		categories.find(t)
	);

	if(it != categories.end())
		return it->second;

	if(t == weapon_type::none)
		throw exception(
			FCPPT_TEXT("Unarmed weapon model missing in TODO")
		);

	return (*this)[weapon_type::none];
}

sanguis::load::model::part::part(
	sge::parse::json::object const &object,
	global_parameters const &param
)
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
		sge::parse::json::find_member_exn<
			sge::parse::json::array
		>(
			members,
			FCPPT_TEXT("weapon_categories")
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
				FCPPT_TEXT("inner members of the weapon category array have to contain exactly one element!")
			);

		sge::parse::json::member const &member(
			inner_members[0]
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
			FCPPT_LOG_WARNING(
				log(),
				fcppt::log::_
					<< FCPPT_TEXT("Double insert in part!")
			);
	}
}
