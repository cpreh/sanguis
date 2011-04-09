#include "perk_cast.hpp"
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>

sanguis::client::perk_container const
sanguis::client::perk_cast(
	messages::types::enum_vector const &_perks
)
{
	perk_container target;

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
