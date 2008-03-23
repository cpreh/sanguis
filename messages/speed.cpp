#include "speed.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::speed)

sanguis::messages::speed::speed(
	const entity_id id,
	const vector2& speed_)
: base(id),
  speed_(speed_)
{}

const sanguis::messages::vector2& sanguis::messages::speed::get() const
{
	return speed_;
}
