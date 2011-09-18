#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/entity_type.hpp>
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
	public virtual entities::base
{
	FCPPT_NONCOPYABLE(
		spawn
	);
public:
	virtual void
	unregister(
		entities::base &
	);

	~spawn();
protected:
	spawn(
		sanguis::diff_clock const &,
		enemy_type::type
	);
private:
	entity_type::type
	type() const;

	server::team::type
	team() const;

	server::center const
	center() const;

	void
	on_update();

	virtual size_type
	may_spawn() = 0;

	virtual void
	add_count(
		size_type
	) = 0;

	sanguis::diff_clock const &diff_clock_;

	enemy_type::type const enemy_type_;
};

}
}
}
}

#endif