#include "entity.hpp"
#include "../angle_vector.hpp"
#include <sge/math/vec_dim.hpp>

sanguis::server::entity::entity(
	const entity_id id_,
	const messages::pos_type &pos_,
	const messages::space_unit angle_,
	const messages::space_unit direction_,
	const messages::space_unit health_,
	const messages::space_unit max_health_,
	const team::type team_,
	const messages::space_unit speed_)
: id_(id_),pos_(pos_),speed_(speed_),angle_(angle_),direction_(direction_),health_(health_),max_health_(max_health_),team_(team_)
{}

sanguis::entity_id sanguis::server::entity::id() const
{
	return id_;
}

sanguis::server::team::type sanguis::server::entity::team() const
{
	return team_;
}

sanguis::messages::pos_type sanguis::server::entity::center() const
{
	return pos() + dim()/messages::mu(2);
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

sanguis::messages::space_unit sanguis::server::entity::max_health() const
{
	return max_health_;
}

void sanguis::server::entity::max_health(const messages::space_unit _max_health)
{
	max_health_ = _max_health;
}

sanguis::messages::space_unit sanguis::server::entity::health() const
{
	return health_;
}

void sanguis::server::entity::health(const messages::space_unit _health)
{
	health_ = _health;
}

sanguis::messages::space_unit sanguis::server::entity::direction() const
{
	return direction_;
}

void sanguis::server::entity::update(const time_type) {}

void sanguis::server::entity::direction(const messages::space_unit _direction)
{
	direction_ = _direction;
}

sanguis::server::entity::~entity()
{}
