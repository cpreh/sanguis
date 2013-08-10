#ifndef SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_WEAPON_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <sanguis/server/weapons/backswing_time.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/delayed_attack_fwd.hpp>
#include <sanguis/server/weapons/magazine_count.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/magazine_type.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/target_fwd.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <sanguis/server/weapons/states/backswing_fwd.hpp>
#include <sanguis/server/weapons/states/castpoint_fwd.hpp>
#include <sanguis/server/weapons/states/reloading_fwd.hpp>
#include <sanguis/server/weapons/states/ready_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_state_machine_decl.hpp>
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
			sanguis::server::weapons::states::ready
		>
{
	FCPPT_NONCOPYABLE(
		weapon
	);
protected:
	weapon(
		sanguis::diff_clock const &,
		sanguis::weapon_type,
		sanguis::server::weapons::range,
		sanguis::server::weapons::magazine_size,
		sanguis::server::weapons::magazine_count,
		sanguis::server::weapons::base_cooldown,
		sanguis::server::weapons::cast_point,
		sanguis::server::weapons::reload_time
	);
public:
	virtual
	~weapon() = 0;

	void
	attack(
		sanguis::server::entities::with_weapon &
	);

	void
	stop(
		sanguis::server::entities::with_weapon &
	);

	void
	update(
		sanguis::server::entities::with_weapon &
	);

	sanguis::weapon_type
	type() const;

	sanguis::server::weapons::magazine_size const
	magazine_size() const;

	bool
	in_range(
		sanguis::server::entities::base const &,
		sanguis::server::weapons::target
	) const;
protected:
	virtual
	void
	do_attack(
		sanguis::server::weapons::delayed_attack const &
	) = 0;

	bool
	usable() const;

	sanguis::diff_clock const &
	diff_clock() const;
private:
	friend class sanguis::server::weapons::states::ready;
	friend class sanguis::server::weapons::states::reloading;
	friend class sanguis::server::weapons::states::backswing;
	friend class sanguis::server::weapons::states::castpoint;

	void
	reset_magazine();

	void
	use_magazine_item();

	bool
	magazine_empty() const;

	void
	magazine_exhausted();

	sanguis::server::weapons::cast_point const
	cast_point() const;

	sanguis::server::weapons::backswing_time const
	backswing_time() const;

	sanguis::server::weapons::reload_time const
	reload_time() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::weapon_type const type_;

	sanguis::server::weapons::range const range_;

	sanguis::server::weapons::magazine_type magazine_used_;

	sanguis::server::weapons::magazine_count::value_type magazine_count_;

	sanguis::server::weapons::magazine_size const magazine_size_;

	sanguis::server::weapons::cast_point const cast_point_;

	sanguis::server::weapons::backswing_time const backswing_time_;

	sanguis::server::weapons::reload_time const reload_time_;

	fcppt::scoped_state_machine<
		sanguis::server::weapons::weapon
	> const scoped_machine_;
};

}
}
}

#endif
