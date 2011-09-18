#include <sanguis/client/draw2d/entities/model/parameters.hpp>

sanguis::client::draw2d::entities::model::parameters::parameters(
	sanguis::diff_clock const &_diff_clock,
	sprite::colored::system &_colored_system,
	sprite::normal::system &_normal_system,
	load::model::collection const &_collection
)
:
	diff_clock_(_diff_clock),
	colored_system_(_colored_system),
	normal_system_(_normal_system),
	collection_(_collection)
{}

sanguis::diff_clock const &
sanguis::client::draw2d::entities::model::parameters::diff_clock() const
{
	return diff_clock_;
}

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
