#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/animation_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/healthbar_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/part_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/with_health.hpp>
#include <sanguis/client/draw2d/entities/with_weapon.hpp>
#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/health.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class object
:
	public container,
	public with_health,
	public with_weapon
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		model::parameters const &,
		fcppt::string const &name,
		entities::order_vector const &,
		needs_healthbar::type,
		decay_option::type
	);

	~object();

	// with_health overrides
	client::health const
	max_health() const;

	client::health const
	health() const;
protected:
	virtual void
	update();

	// with_orientation overrides
	virtual void
	orientation(
		sprite::rotation
	);

	using container::orientation;

	void
	orientation(
		sprite::rotation,
		sprite::index
	);

	// base overrides
	bool
	is_decayed() const;

	virtual void
	on_decay();

	// with_speed overrides
	virtual void
	speed(
		draw2d::speed const &
	);

	using container::speed;

	model::part &
	part(
		sprite::index const &
	);

	bool
	dead() const;

	bool
	walking() const;

	bool
	has_health() const;
private:
	// with_health overrides
	void
	health(
		client::health
	);

	void
	max_health(
		client::health
	);

	// with_weapon overrides
	void
	weapon(
		sanguis::weapon_type
	);

	void
	attacking(
		bool
	);

	void
	reloading(
		bool
	);

	// own functions
	void
	change_animation();

	void
	change_animation(
		animation_type::type
	);

	animation_type::type
	animation() const;

	animation_type::type
	fallback_anim(
		animation_type::type
	) const;

	void
	update_healthbar();

	bool
	animations_ended() const;

	sanguis::diff_clock const &diff_clock_;

	bool
		attacking_,
		reloading_;

	client::health
		health_,
		max_health_;

	fcppt::scoped_ptr<
		healthbar
	> healthbar_;

	fcppt::scoped_ptr<
		decay_time
	> decay_time_;

	decay_option::type const decay_option_;

	typedef boost::ptr_vector<
		model::part
	> part_vector;

	part_vector parts_;
};

}
}
}
}
}

#endif
