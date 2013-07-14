#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_links.hpp>
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
	public virtual sanguis::server::entities::base,
	public sanguis::server::entities::with_links
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
	// TODO: Get rid of this?
	sanguis::server::center const
	center() const
	override;

	void
	on_update()
	override;

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
