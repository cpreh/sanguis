#include "part.hpp"
#include "split_first_slash.hpp"
#include "../../exception.hpp"
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <sge/filesystem/exists.hpp>
#include <boost/tr1/array.hpp>
#include <utility>
#include <iterator>

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
			SGE_TEXT("Unarmed weapon model missing in ")
			+ param.path().string()
		);
	return (*this)[weapon_type::none];
}

sanguis::load::model::part::part(
	global_parameters const &param)
:
	param(param),
	categories()
{}

void
sanguis::load::model::part::add(
	sge::parse::ini::entry_vector const &entries,
	sge::string const &header)
{
	split_pair const names(
		split_first_slash(
			header
		)
	);

	weapon_type_array::const_iterator const weapon_index(
		std::find(
			weapon_types.begin(),
			weapon_types.end(),
			names.first
		)
	);

	if(weapon_index == weapon_types.end())
		throw exception(
			SGE_TEXT("Invalid weapon_category ")
			+ names.first
		);

	weapon_type::type const type(
		static_cast<
			weapon_type::type
		>(
			std::distance(
				weapon_types.begin(),
				weapon_index
			)
		)
	);

	category_map::iterator it(
		categories.find(
			type
		)
	);

	if(it == categories.end())
	{
		std::pair<category_map::iterator, bool> const ret(
			categories.insert(
				std::make_pair(
					type,		
					weapon_category(
						param
					)
				)
			)
		);

		it = ret.first;
	}
	
	it->second.add(
		entries,
		names.second
	);
}
