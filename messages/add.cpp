#include "add.hpp"
#include "../archive.hpp"
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT(sanguis::messages::add)

sanguis::messages::add::add()
{}

sanguis::messages::add::add(
	const entity_id id,
	const entity_type::type type_,
	const ivector2_32& pos_,
	const idim2_32& sz_,
	const space_unit angle_,
	const vector2& speed_)
: base(id),
  type_(type_),
  pos_(pos_),
  sz_(sz_),
  angle_(angle_),
  speed_(speed_)
{}
	
sanguis::entity_type::type sanguis::messages::add::type() const
{
	return type_;
}

const sanguis::messages::ivector2_32& sanguis::messages::add::pos() const
{
	return pos_;
}

const sanguis::messages::idim2_32& sanguis::messages::add::sz() const
{
	return sz_;
}

sanguis::messages::space_unit sanguis::messages::add::angle() const
{
	return angle_;
}

const sanguis::messages::vector2& sanguis::messages::add::speed() const
{
	return speed_;
}
