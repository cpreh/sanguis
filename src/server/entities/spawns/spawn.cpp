#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/enemies/spawn_owner.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/waves/spawn.hpp>


void
sanguis::server::entities::spawns::spawn::unregister(
	sanguis::server::entities::base &
)
{
}

sanguis::server::entities::spawns::spawn::~spawn()
{
}

sanguis::server::entities::spawns::spawn::spawn(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::enemy_type const _enemy_type
)
:
	sanguis::server::entities::base(),
	sanguis::server::entities::with_links(),
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	enemy_type_(
		_enemy_type
	)
{
}

sanguis::server::team
sanguis::server::entities::spawns::spawn::team() const
{
	// TODO: This is not needed!
	return sanguis::server::team::monsters;
}

sanguis::server::center const
sanguis::server::entities::spawns::spawn::center() const
{
	return
		sanguis::server::center(
			sanguis::server::center::value_type::null() // FIXME!
		);
}

void
sanguis::server::entities::spawns::spawn::on_update()
{
	if(
		sanguis::server::entities::spawns::size_type const count_ =
			this->may_spawn()
	)
	{
		for(
			size_type i = 0;
			i < count_;
			++i
		)
			sanguis::server::waves::spawn(
				diff_clock_,
				random_generator_,
				this->environment(),
				this->environment().load_context(),
				enemy_type_,
				sanguis::server::entities::enemies::spawn_owner(
					this->link()
				)
			);

		this->add_count(
			count_
		);
	}
}
