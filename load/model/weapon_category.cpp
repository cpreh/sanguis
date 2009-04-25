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
	sge::parse::json::value const &val,
	global_parameters const &param)
:
	animations()
{
	BOOST_FOREACH(
		sge::parse::json::array::element_vector::const_reference r,
		boost::get<
			sge::parse::json::array
		>(
			array_it->value_
		).elements
	)
	{
		if(
			animations.insert(
				std::make_pair(
					r.name,
					animation(
						r.value,
						param
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
