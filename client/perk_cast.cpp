#include "perk_cast.hpp"
#include <fcppt/container/raw_vector.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>

sanguis::client::perk_container const sanguis::client::perk_cast(
	messages::types::enum_vector const &perks)
{
	perk_container target;
	BOOST_FOREACH(
		messages::types::enum_vector::const_reference r,
		perks)
	{
		FCPPT_ASSERT(r < perk_type::size);
		target.push_back(
			static_cast<perk_type::type>(
				r));
	}
	return target;
}
