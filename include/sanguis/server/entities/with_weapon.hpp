#ifndef SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/optional_weapon_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_weapon
:
	public virtual sanguis::server::entities::base,
	public virtual sanguis::server::entities::ifaces::with_angle,
	public virtual sanguis::server::entities::ifaces::with_id,
	public virtual sanguis::server::entities::ifaces::with_team
{
	FCPPT_NONCOPYABLE(
		with_weapon
	);
protected:
	with_weapon(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::server::weapons::unique_ptr &&start_weapon
	);

	~with_weapon();

	virtual
	void
	on_update()
	override;
public:
	void
	change_weapon(
		sanguis::weapon_type
	);

	void
	add_weapon(
		sanguis::server::weapons::unique_ptr &&
	);

	void
	remove_weapon(
		sanguis::weapon_type
	);

	void
	target(
		sanguis::server::vector const &
	);

	bool
	in_range(
		sanguis::server::vector const &
	) const;

	bool
	has_weapon() const;

	sanguis::server::weapons::weapon &
	active_weapon();

	sanguis::server::weapons::weapon const &
	active_weapon() const;

	void
	aggressive(
		bool
	);

	void
	attack_ready();

	void
	start_attacking();

	void
	start_reloading();

	void
	stop_reloading();

	sanguis::server::entities::property::always_max &
	attack_speed();

	sanguis::server::entities::property::always_max &
	reload_speed();
private:
	void
	stop_attacking();

	void
	attack_speed_change(
		sanguis::server::entities::property::value
	);

	void
	reload_speed_change(
		sanguis::server::entities::property::value
	);

	virtual
	void
	on_new_weapon(
		sanguis::weapon_type
	);

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	typedef boost::ptr_map<
		sanguis::weapon_type,
		sanguis::server::weapons::weapon
	> weapon_container;

	weapon_container weapons_;

	sanguis::optional_weapon_type weapon_;

	typedef fcppt::optional<
		sanguis::server::vector
	> optional_vector;

	optional_vector target_;

	bool
		attacking_,
		reloading_,
		attack_ready_,
		aggressive_;

	sanguis::server::entities::property::always_max
		attack_speed_,
		reload_speed_;

	fcppt::signal::scoped_connection const
		attack_speed_change_,
		reload_speed_change_;
};

}
}
}

#endif
