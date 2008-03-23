#include <boost/serialization/export.hpp>
#include "base.hpp"

BOOST_CLASS_EXPORT(sanguis::messages::base)

sanguis::messages::base::base(const entity_id id_)
: id_(id_)
{}

sanguis::entity_id sanguis::messages::base::id() const
{
	return id_;
}

sanguis::messages::base::~base()
{}
