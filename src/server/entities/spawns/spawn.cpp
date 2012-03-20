#include <sanguis/server/entities/spawns/spawn.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/waves/spawn.hpp>
#include <fcppt/math/vector/object_impl.hpp>

void
sanguis::server::entities::spawns::spawn::unregister(
	entities::base &
)
{
}

sanguis::server::entities::spawns::spawn::~spawn()
{
}

sanguis::server::entities::spawns::spawn::spawn(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	enemy_type::type const _enemy_type
)
:
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

sanguis::entity_type::type
sanguis::server::entities::spawns::spawn::type() const
{
	return entity_type::spawn;
}

sanguis::server::team::type
sanguis::server::entities::spawns::spawn::team() const
{
	return server::team::monsters;
}

sanguis::server::center const
sanguis::server::entities::spawns::spawn::center() const
{
	return
		server::center(
			server::center::value_type::null() // FIXME!
		);
}

void
sanguis::server::entities::spawns::spawn::on_update()
{
	if(
		size_type const count_ =
			this->may_spawn()
	)
	{
		for(
			size_type i = 0;
			i < count_;
			++i
		)
			waves::spawn(
				diff_clock_,
				random_generator_,
				this->environment(),
				this->environment().load_context(),
				enemy_type_,
				this->link()
			);

		this->add_count(
			count_
		);
	}
}
