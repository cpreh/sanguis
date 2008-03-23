#include "rotate.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::rotate)

sanguis::messages::rotate::rotate(
	const entity_id id,
	const space_unit rot_)
: base(id),
  rot_(rot_)
{}

sanguis::messages::space_unit sanguis::messages::rotate::rot() const
{
	return rot_;
}
