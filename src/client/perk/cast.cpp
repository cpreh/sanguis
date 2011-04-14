#include "cast.hpp"
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>

sanguis::client::perk::container const
sanguis::client::perk::cast(
	messages::types::enum_vector const &_perks
)
{
	perk::container target;

	BOOST_FOREACH(
		messages::types::enum_vector::const_reference elem,
		_perks
	)
	{
		FCPPT_ASSERT(
			elem < perk_type::size
		);

		target.push_back(
			static_cast<
				perk_type::type
			>(
				elem
			)
		);
	}

	return target;
}
