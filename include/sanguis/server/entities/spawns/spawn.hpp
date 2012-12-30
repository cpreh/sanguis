#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/entity_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace spawns
{

class spawn
:
	public virtual sanguis::server::entities::base
{
	FCPPT_NONCOPYABLE(
		spawn
	);
public:
	virtual
	void
	unregister(
		sanguis::server::entities::base &
	);

	~spawn();
protected:
	spawn(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::enemy_type
	);
private:
	sanguis::entity_type
	type() const;

	sanguis::server::team
	team() const;

	sanguis::server::center const
	center() const;

	void
	on_update();

	virtual
	sanguis::server::entities::spawns::size_type
	may_spawn() = 0;

	virtual
	void
	add_count(
		sanguis::server::entities::spawns::size_type
	) = 0;

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::enemy_type const enemy_type_;
};

}
}
}
}

#endif
