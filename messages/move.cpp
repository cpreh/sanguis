#include "move.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::move)

sanguis::messages::move::move(
	const entity_id id,
	const ivector2_32& pos_)
: base(id),
  pos_(pos_)
{}

const sanguis::messages::ivector2_32& sanguis::messages::move::pos() const
{
	return pos_;
}
