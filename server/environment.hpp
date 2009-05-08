#ifndef SANGUIS_SERVER_ENVIRONMENT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_HPP_INCLUDED

#include "send_callback.hpp"
#include "insert_callback.hpp"
#include "exp_callback.hpp"
#include "level_callback.hpp"
#include "load_callback.hpp"
#include "spawn_pickup_callback.hpp"
#include "pickup_chance_callback.hpp"
#include <sge/collision/world_fwd.hpp>

namespace sanguis
{
namespace server
{
struct environment
{
	environment(
		send_callback const &,
		insert_callback const &,
		exp_callback const &,
		level_callback const &,
		load_callback const &,
		spawn_pickup_callback const &,
		pickup_chance_callback const &,
		sge::collision::world_ptr);
	
	send_callback const &
	send() const;

	insert_callback const &
	insert() const;

	exp_callback const &
	exp() const;

	level_callback const &
	level() const;

	load_callback const &
	load() const;

	spawn_pickup_callback const &
	spawn_pickup() const;

	pickup_chance_callback const &
	pickup_chance() const;

	sge::collision::world_ptr const
	collision() const;
private:
	send_callback const send_;
	insert_callback const insert_;
	exp_callback const exp_;
	level_callback const level_;
	load_callback const load_;
	spawn_pickup_callback const spawn_pickup_;
	pickup_chance_callback const pickup_chance_;
	sge::collision::world_ptr const collision_;
};
}
}

#endif
