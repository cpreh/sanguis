#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/animation_type_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/with_health.hpp>
#include <sanguis/client/draw2d/entities/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/healthbar_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/part_fwd.hpp>
#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
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
	public sanguis::client::draw2d::entities::container,
	public sanguis::client::draw2d::entities::with_health,
	public sanguis::client::draw2d::entities::with_weapon
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sanguis::client::draw2d::entities::model::parameters const &,
		fcppt::string const &name,
		sanguis::client::draw2d::entities::order_vector const &,
		sanguis::client::draw2d::entities::model::needs_healthbar,
		sanguis::client::draw2d::entities::model::decay_option
	);

	~object();

	// with_health overrides
	sanguis::client::max_health const
	max_health() const
	override;

	sanguis::client::health const
	health() const
	override;
protected:
	virtual
	void
	update();

	// with_orientation overrides
	virtual
	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	)
	override;

	using container::orientation;

	void
	orientation(
		sanguis::client::draw2d::sprite::rotation,
		sanguis::client::draw2d::sprite::index
	);

	// base overrides
	bool
	dead() const
	override;

	bool
	is_decayed() const
	override;

	virtual
	void
	on_die()
	override;

	// with_speed overrides
	virtual
	void
	speed(
		sanguis::client::draw2d::speed const &
	)
	override;

	using container::speed;

	sanguis::client::draw2d::entities::model::part &
	part(
		sanguis::client::draw2d::sprite::index const &
	);

	bool
	walking() const;

	bool
	has_health() const;
private:
	// with_health overrides
	void
	health(
		sanguis::client::health
	)
	override;

	void
	max_health(
		sanguis::client::max_health
	)
	override;

	// with_weapon overrides
	void
	weapon(
		sanguis::optional_primary_weapon_type
	)
	override;

	void
	attacking(
		bool
	)
	override;

	void
	reloading(
		bool
	)
	override;

	// own functions
	void
	change_animation();

	void
	change_animation(
		sanguis::animation_type
	);

	sanguis::animation_type
	animation() const;

	sanguis::animation_type
	fallback_anim(
		sanguis::animation_type
	) const;

	void
	update_healthbar();

	bool
	animations_ended() const;

	sanguis::diff_clock const &diff_clock_;

	bool
		attacking_,
		reloading_;

	sanguis::client::health health_;

	sanguis::client::max_health max_health_;

	fcppt::scoped_ptr<
		sanguis::client::draw2d::entities::model::healthbar
	> healthbar_;

	fcppt::scoped_ptr<
		sanguis::client::draw2d::entities::model::decay_time
	> decay_time_;

	sanguis::client::draw2d::entities::model::decay_option const decay_option_;

	typedef boost::ptr_vector<
		sanguis::client::draw2d::entities::model::part
	> part_vector;

	part_vector parts_;
};

}
}
}
}
}

#endif
