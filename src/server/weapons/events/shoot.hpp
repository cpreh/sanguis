#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_SHOOT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_SHOOT_HPP_INCLUDED

#include "shoot_fwd.hpp"
#include "../../entities/with_weapon_fwd.hpp"
#include "../../vector.hpp"
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/nonassignable.hpp>
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace events
{

class shoot
:
	public boost::statechart::event<
		shoot
	>
{
	FCPPT_NONASSIGNABLE(
		shoot
	);
public:
	shoot(
		entities::with_weapon &from,
		server::vector const &to
	);

	entities::with_weapon &
	from() const;

	server::vector const &
	to() const;
private:
	entities::with_weapon &from_;

	server::vector const to_;
};

}
}
}
}

#endif
