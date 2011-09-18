#ifndef SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_WEAPON_HPP_INCLUDED

#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/property/always_max.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
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
	public virtual base,
	public virtual ifaces::with_angle
{
	FCPPT_NONCOPYABLE(
		with_weapon
	);
protected:
	with_weapon(
		sanguis::diff_clock const &,
		weapons::unique_ptr start_weapon
	);

	~with_weapon();

	virtual void
	on_update();
public:
	void
	change_weapon(
		weapon_type::type
	);

	void
	add_weapon(
		weapons::unique_ptr
	);

	void
	remove_weapon(
		weapon_type::type
	);

	void
	target(
		server::vector const &
	);

	bool
	in_range(
		server::vector const &
	) const;

	bool
	has_weapon() const;

	weapons::weapon &
	active_weapon();

	weapons::weapon const &
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

	property::always_max &
	attack_speed();

	property::always_max &
	reload_speed();
private:
	void stop_attacking();

	void
	attack_speed_change(
		property::value
	);

	void
	reload_speed_change(
		property::value
	);

	virtual void
	on_new_weapon(
		weapon_type::type
	);

	sanguis::diff_clock const &diff_clock_;

	typedef boost::ptr_map<
		weapon_type::type,
		weapons::weapon
	> weapon_container;

	weapon_container weapons_;

	weapon_type::type weapon_;

	typedef fcppt::optional<
		server::vector
	> optional_vector;

	optional_vector target_;

	bool
		attacking_,
		reloading_,
		attack_ready_,
		aggressive_;

	property::always_max
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