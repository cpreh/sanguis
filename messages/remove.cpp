#include "remove.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::remove)

sanguis::messages::remove::remove(const entity_id id)
: base(id)
{}
