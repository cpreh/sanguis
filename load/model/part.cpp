#include "part.hpp"
#include "../../exception.hpp"
#include <sge/string.hpp>
#include <sge/filesystem/exists.hpp>
#include <boost/array.hpp>
#include <utility>
#include <iterator>

sanguis::load::model::part::part(
	sge::filesystem::path const &path,
	resource::context const &ctx)
:
	path(path)
{
	typedef boost::array<
		sge::string,
		weapon_type::size
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

	for(weapon_type_array::const_iterator it(weapon_types.begin());
	    it != weapon_types.end();
	    ++it)
	{
		sge::filesystem::path const weapon_path(path / *it);
		if(!sge::filesystem::exists(weapon_path))
			continue;

		if(categories.insert(
			std::make_pair(
				static_cast<weapon_type::type>(
					std::distance(
						static_cast<weapon_type_array const &>(weapon_types).begin(),
						it)),
				weapon_category(
					weapon_path,
					ctx)))
		.second == false)
			throw exception(SGE_TEXT("Double insert in model::part: ") + weapon_path.string());
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
			SGE_TEXT("Unarmed weapon model missing in ")
			+ path.string());
	return (*this)[weapon_type::none];
}
