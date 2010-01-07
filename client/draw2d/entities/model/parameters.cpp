#include "parameters.hpp"

sanguis::client::draw2d::entities::model::parameters::parameters(
	sprite::colored::system &colored_system_,
	sprite::normal::system &normal_system_,
	load::model::collection const &collection_
)
:
	colored_system_(colored_system_),
	normal_system_(normal_system_),
	collection_(collection_)
{}

sanguis::client::draw2d::sprite::colored::system &
sanguis::client::draw2d::entities::model::parameters::colored_system() const
{
	return colored_system_;
}

sanguis::client::draw2d::sprite::normal::system &
sanguis::client::draw2d::entities::model::parameters::normal_system() const
{
	return normal_system_;
}

sanguis::load::model::collection const &
sanguis::client::draw2d::entities::model::parameters::collection() const
{
	return collection_;
}
