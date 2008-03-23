#include "move.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::move)

sanguis::messages::move::move(
	const entity_id id,
	const pos_type& pos_)
: base(id),
  pos_(pos_)
{}

const sanguis::messages::pos_type& sanguis::messages::move::pos() const
{
	return pos_;
}
