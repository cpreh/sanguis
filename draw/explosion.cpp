#include "explosion.hpp"
#include "../client/next_id.hpp"

sanguis::draw::explosion::explosion(
	draw::environment const &env,
	sge::sprite::point const &pos)
:
	entity(
		env,
		client::next_id())
{}

bool sanguis::draw::explosion::may_be_removed() const
{
	return true; // TODO
}
