#include "insert_default_properties.hpp"
#include "property.hpp"
#include "../../exception.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::property_map const
sanguis::server::entities::insert_default_properties(
	property_map const &m)
{
	static property_map const default_properties =
		boost::assign::map_list_of
		(
			property_type::attack_speed,
			property(static_cast<space_unit>(1))
		)
		(
			property_type::health,
			property(static_cast<space_unit>(1))
		)(
			property_type::movement_speed,
			property(static_cast<space_unit>(0))
		);

	if(default_properties.size() != property_type::size)
		throw exception(
			SGE_TEXT("Something is missing in the default_properties!")
		);

	property_map ret;

	BOOST_FOREACH(
		property_map::const_reference r,
		default_properties
	)
	{
		property_map::const_iterator const it(
			m.find(
				r.first
			)
		);

		if(it == m.end())
			ret.insert(r);
		else
			ret.insert(
				*it
			);
	}

	return ret;
}
