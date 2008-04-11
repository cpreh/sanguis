#include "entity.hpp"
#include "../angle_vector.hpp"
#include <sge/math/vec_dim.hpp>

sanguis::server::entity::entity(
	const entity_id id_,
	const messages::pos_type &pos_,
	const messages::space_unit angle_,
	const messages::space_unit direction_,
	const messages::space_unit speed_)
: id_(id_),pos_(pos_),speed_(speed_),angle_(angle_),direction_(direction_)
{}

sanguis::entity_id sanguis::server::entity::id() const
{
	return id_;
}

sanguis::messages::pos_type sanguis::server::entity::center() const
{
	return pos() + dim()/static_cast<messages::space_unit>(2);
}

void sanguis::server::entity::pos(const messages::pos_type _pos) 
{ 
	pos_ = _pos;
}

sanguis::messages::pos_type sanguis::server::entity::pos() const
{
	return pos_;
}

sanguis::messages::pos_type sanguis::server::entity::abs_speed() const
{
	return angle_to_vector(direction_) * speed_ * max_speed();
}

sanguis::messages::space_unit sanguis::server::entity::speed() const
{
	return speed_;
}

void sanguis::server::entity::speed(const messages::space_unit _speed)
{
	speed_ = _speed;
}

sanguis::messages::space_unit sanguis::server::entity::angle() const
{
	return angle_;
}

void sanguis::server::entity::angle(const messages::space_unit _angle)
{
	angle_ = _angle;
}

sanguis::messages::space_unit sanguis::server::entity::direction() const
{
	return direction_;
}

void sanguis::server::entity::direction(const messages::space_unit _direction)
{
	direction_ = _direction;
}

sanguis::server::entity::~entity()
{}
