#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/simple.hpp>
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
	public virtual sanguis::server::entities::ifaces::with_angle,
	public sanguis::server::entities::simple,
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

	~spawn()
	override;
protected:
	spawn(
		sanguis::random_generator &,
		sanguis::creator::enemy_type,
		sanguis::creator::enemy_kind,
		sanguis::server::world::difficulty
	);
private:
	sanguis::server::center
	center() const
	override;

	sanguis::server::angle
	angle() const
	override;

	void
	angle(
		sanguis::server::angle
	)
	override;

	sanguis::server::entities::optional_transfer_result
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

	typedef
	fcppt::optional<
		sanguis::server::center
	>
	optional_center;

	typedef
	fcppt::optional<
		sanguis::server::angle
	>
	optional_angle;

	sanguis::random_generator &random_generator_;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::creator::enemy_kind const enemy_kind_;

	sanguis::server::world::difficulty const difficulty_;

	optional_center center_;

	optional_angle angle_;
};

}
}
}
}

#endif
