#include "bullet.hpp"

void sanguis::server::bullet::update(const time_type delta)
{
	center_ += speed_ * delta;
}
