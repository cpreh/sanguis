#include "weapon_category.hpp"
#include <boost/array.hpp>
#include <utility>
#include <iterator>

sanguis::load::model::weapon_category::weapon_category(
	sge::path const& path)
{
	typedef boost::array<
		sge::string,
		sanguis::animation_type::size> animation_type_array;

	const animation_type_array animation_types = {
	{
		SGE_TEXT("none"),
		SGE_TEXT("attacking"),
		SGE_TEXT("walking"),
		SGE_TEXT("dying")
	} };

	for(animation_type_array::const_iterator it(animation_types.begin());
	    it != animation_types.end();
	    ++it)
	{
		const sge::path animation_path(path / *it);
		if(!boost::filesystem::exists(animation_path))
			continue;
		animations.insert(
			std::make_pair(
				static_cast<animation_type::type>(
					std::distance(
						static_cast<animation_type_array const&>(animation_types).begin(),
						it)),
				animation(
					animation_path)));
	}
}

sanguis::load::model::animation const&
sanguis::load::model::weapon_category::operator[](
	const animation_type::type anim) const
{
	const animation_map::const_iterator it(animations.find(anim));
	if(it == animations.end())
		throw sge::exception(SGE_TEXT("Animation not found in model!"));
	return it->second;
}
