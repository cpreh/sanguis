#include "part.hpp"
#include "../../exception.hpp"
#include <sge/parse/json/array.hpp>
#include <sge/text.hpp>
#include <sge/string.hpp>
#include <boost/tr1/array.hpp>
#include <boost/variant/get.hpp>
#include <boost/foreach.hpp>
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
	sge::parse::json::value const &val,
	global_parameters const &param)
:
	categories()
{
	BOOST_FOREACH(
		sge::parse::json::array::element_vector::const_reference r,
		boost::get<
			sge::parse::json::array
		>(
			val
		).elements)
	{
		if(	
			categories.insert(
				std::make_pair(
					r.name,
					weapon_category(
						r.value_,
						param
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
