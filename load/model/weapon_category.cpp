#include "weapon_category.hpp"
#include "base_animation_not_found.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/text.hpp>
#include <boost/array.hpp>
#include <utility>
#include <iterator>

sanguis::load::model::weapon_category::weapon_category(
	sge::path const &path)
: path(path)
{
	typedef boost::array<
		sge::string,
		sanguis::animation_type::size> animation_type_array;

	animation_type_array const animation_types = {
	{
		SGE_TEXT("none"),
		SGE_TEXT("attacking"),
		SGE_TEXT("walking"),
		SGE_TEXT("dying"),
		SGE_TEXT("deploying"),
		SGE_TEXT("reloading")
	} };

	for(animation_type_array::const_iterator it(animation_types.begin());
	    it != animation_types.end();
	    ++it)
	{
		sge::path const animation_path(path / *it);
		if(!boost::filesystem::exists(animation_path))
			continue;
		
		if(animations.insert(
			std::make_pair(
				static_cast<animation_type::type>(
					std::distance(
						static_cast<animation_type_array const &>(
							animation_types).begin(),
						it)),
				animation(
					animation_path)))
		.second == false)
			throw sge::exception(
				SGE_TEXT("Double insert in model::weapon_category: ")
				+ animation_path.string());
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
		throw sge::exception(
			SGE_TEXT("Default animation not found in model in ")
			+ path.string());
	throw base_animation_not_found(
		anim);
}
