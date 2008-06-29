#include "part.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <boost/array.hpp>
#include <utility>
#include <iterator>

sanguis::load::model::part::part(
	sge::path const& path)
: path(path)
{
	typedef boost::array<sge::string, weapon_type::size> weapon_type_array;
	const weapon_type_array weapon_types = {
	{
		SGE_TEXT("none"),
		SGE_TEXT("melee"),
		SGE_TEXT("pistol"),
		SGE_TEXT("dual_pistol")
	} };

	for(weapon_type_array::const_iterator it(weapon_types.begin());
	    it != weapon_types.end();
	    ++it)
	{
		const sge::path weapon_path(path / *it);
		if(!boost::filesystem::exists(weapon_path))
			continue;

		if(categories.insert(
			std::make_pair(
				static_cast<weapon_type::type>(
					std::distance(
						static_cast<weapon_type_array const &>(weapon_types).begin(),
						it)),
				weapon_category(weapon_path)))
		.second == false)
			throw sge::exception(SGE_TEXT("Double insert in model::part: ") + weapon_path.string());
	}
}

sanguis::load::model::weapon_category const&
sanguis::load::model::part::operator[](const weapon_type::type t) const
{
	const category_map::const_iterator it(categories.find(t));
	if(it != categories.end())
		return it->second;
	if(t == weapon_type::none)
		throw sge::exception(
			SGE_TEXT("Unarmed weapon model missing in ")
			+ path.string());
	return (*this)[weapon_type::none];
}
