#include "weapon_category.hpp"
#include "base_animation_not_found.hpp"
#include "../../exception.hpp"
#include <sge/filesystem/exists.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <boost/tr1/array.hpp>
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
	global_parameters const &param)
:
	param(param),
	animations()
{}

void
sanguis::load::model::weapon_category::add(
	sge::parse::ini::entry_vector const &entries,
	sge::string const &header)
{
	animation_type_array::const_iterator const weapon_index(
		std::find(
			animation_types.begin(),
			animation_types.end(),
			header	
		)
	);

	if(weapon_index == animation_types.end())
		throw exception(
			SGE_TEXT("Invalid animation ")
			+ header
		);

	animation_type::type const type(
		static_cast<
			animation_type::type
		>(
			std::distance(
				animation_types.begin(),
				weapon_index
			)
		)
	);

	if(
		animations.insert(
			std::make_pair(
				type,		
				animation(
					param,
					entries
				)
			)
		).second == false
	)
		throw exception(
			SGE_TEXT("Double insert in load!")
		);
}
