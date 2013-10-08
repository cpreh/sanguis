#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/spawns/size_type.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


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
	public virtual sanguis::server::entities::ifaces::with_angle,
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
		sanguis::creator::enemy_type,
		sanguis::server::world::difficulty
	);
private:
	sanguis::server::center const
	center() const
	override;

	sanguis::server::angle const
	angle() const
	override;

	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	void
	update()
	override;

	virtual
	sanguis::server::entities::spawns::size_type
	may_spawn() = 0;

	virtual
	void
	add_count(
		sanguis::server::entities::spawns::size_type
	) = 0;

	typedef fcppt::optional<
		sanguis::server::center
	> optional_center;

	typedef fcppt::optional<
		sanguis::server::angle
	> optional_angle;

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::server::world::difficulty const difficulty_;

	optional_center center_;

	optional_angle angle_;
};

}
}
}
}

#endif
