#ifndef SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SPAWNS_SPAWN_HPP_INCLUDED

#include <sanguis/random_generator_ref.hpp>
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
#include <sanguis/server/weapons/common_parameters.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sanguis::server::entities::spawns
{

class spawn
:
	public virtual sanguis::server::entities::ifaces::with_angle,
	public sanguis::server::entities::simple,
	public sanguis::server::entities::with_links
{
	FCPPT_NONMOVABLE(
		spawn
	);
public:
	virtual
	void
	unregister(
		sanguis::server::entities::base & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	~spawn()
	override;
protected:
	spawn(
		sanguis::random_generator_ref,
		sanguis::server::weapons::common_parameters const &,
		sanguis::creator::enemy_type,
		sanguis::creator::enemy_kind,
		sanguis::server::world::difficulty
	);
private:
	[[nodiscard]]
	sanguis::server::center
	center() const
	override;

	[[nodiscard]]
	sanguis::server::angle
	angle() const
	override;

	void
	angle(
		sanguis::server::angle
	)
	override;

	[[nodiscard]]
	sanguis::server::entities::optional_transfer_result
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	void
	update()
	override;

	[[nodiscard]]
	virtual
	sanguis::server::entities::spawns::size_type
	may_spawn() = 0;

	virtual
	void
	add_count(
		sanguis::server::entities::spawns::size_type
	) = 0;

	using
	optional_center
	=
	fcppt::optional::object<
		sanguis::server::center
	>;

	using
	optional_angle
	=
	fcppt::optional::object<
		sanguis::server::angle
	>;

	sanguis::random_generator_ref const random_generator_;

	sanguis::server::weapons::common_parameters const weapons_parameters_;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::creator::enemy_kind const enemy_kind_;

	sanguis::server::world::difficulty const difficulty_;

	optional_center center_;

	optional_angle angle_;
};

}

#endif
