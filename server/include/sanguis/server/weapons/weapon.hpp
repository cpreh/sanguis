#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/magazine_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/optional_with_weapon_ref.hpp>
#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/attack_result_fwd.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/target_fwd.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <sanguis/server/weapons/attributes/optional_accuracy.hpp>
#include <sanguis/server/weapons/attributes/optional_magazine_size.hpp>
#include <sanguis/server/weapons/states/backswing_fwd.hpp>
#include <sanguis/server/weapons/states/castpoint_fwd.hpp>
#include <sanguis/server/weapons/states/idle_fwd.hpp>
#include <sanguis/server/weapons/states/reloading_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state_machine.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

class weapon
:
	public
		boost::statechart::state_machine<
			sanguis::server::weapons::weapon,
			sanguis::server::weapons::states::idle
		>
{
	FCPPT_NONCOPYABLE(
		weapon
	);
protected:
	weapon(
		sanguis::random_generator &,
		sanguis::weapon_type,
		sanguis::server::weapons::attributes::optional_accuracy,
		sanguis::server::weapons::range,
		sanguis::server::weapons::attributes::optional_magazine_size,
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::optional_reload_time
	);
public:
	~weapon()
	override = 0;

	void
	owner(
		sanguis::server::entities::optional_with_weapon_ref const &
	);

	void
	attack();

	void
	reload();

	void
	stop();

	void
	update();

	void
	tick(
		sanguis::duration const &
	);

	sanguis::weapon_type
	type() const;

	sanguis::server::weapons::attributes::optional_magazine_size const
	magazine_size() const;

	bool
	in_range(
		sanguis::server::weapons::target
	) const;

	bool
	owner_target_in_range() const;

	bool
	usable() const;

	sanguis::weapon_description
	description() const;
protected:
	virtual
	sanguis::server::weapons::attack_result
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	) = 0;

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::random_generator &
	random_generator() const;
private:
	sanguis::server::entities::with_weapon &
	owner() const;

	void
	weapon_status(
		sanguis::weapon_status
	);

	virtual
	sanguis::weapon_attribute_vector
	attributes() const = 0;

	friend class sanguis::server::weapons::states::idle;
	friend class sanguis::server::weapons::states::reloading;
	friend class sanguis::server::weapons::states::backswing;
	friend class sanguis::server::weapons::states::castpoint;

	void
	reset_magazine();

	void
	use_magazine_item();

	bool
	magazine_empty() const;

	sanguis::server::weapons::attributes::optional_accuracy const
	accuracy() const;

	sanguis::server::weapons::cast_point const
	cast_point() const;

	sanguis::server::weapons::backswing_time const
	backswing_time() const;

	sanguis::server::weapons::optional_reload_time const
	reload_time() const;

	sanguis::magazine_remaining const
	magazine_remaining() const;

	void
	update_magazine_remaining();

	sanguis::diff_clock diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::weapon_type const type_;

	sanguis::server::weapons::attributes::optional_accuracy const accuracy_;

	sanguis::server::weapons::range const range_;

	sanguis::magazine_type magazine_used_;

	sanguis::server::weapons::attributes::optional_magazine_size const magazine_size_;

	sanguis::server::weapons::cast_point const cast_point_;

	sanguis::server::weapons::backswing_time const backswing_time_;

	sanguis::server::weapons::optional_reload_time const reload_time_;

	sanguis::server::entities::optional_with_weapon_ref owner_;
};

}
}
}

#endif
