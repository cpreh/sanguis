#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/optional_health_pair_fwd.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_health.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/healthbar_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/part_fwd.hpp>
#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/animation_type_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <memory>
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
	public sanguis::client::draw2d::entities::ifaces::with_health,
	public sanguis::client::draw2d::entities::ifaces::with_weapon
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef
	sanguis::client::draw2d::entities::model::parameters
	parameters_type;

	explicit
	object(
		sanguis::client::draw2d::entities::model::parameters const &
	);

	~object()
	override;
protected:
	void
	update()
	override;

	// with_orientation overrides
	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	)
	override;

	using sanguis::client::draw2d::entities::container::orientation;

	void
	orientation(
		sanguis::client::draw2d::sprite::rotation,
		sanguis::client::draw2d::sprite::index
	);

	// base overrides
	bool
	dead() const
	override;

	void
	pause(
		bool
	)
	override;

	bool
	is_decayed() const
	override;

	void
	on_die()
	override;

	// with_speed overrides
	void
	speed(
		sanguis::client::draw2d::speed const &
	)
	override;

	using sanguis::client::draw2d::entities::container::speed;

	sanguis::client::draw2d::entities::model::part &
	part(
		sanguis::client::draw2d::sprite::index const &
	);

	bool
	walking() const;

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

	sanguis::client::optional_health_pair const
	health_pair() const;
private:
	// with_weapon overrides
	void
	weapon(
		sanguis::optional_primary_weapon_type
	)
	override;

	void
	weapon_status(
		sanguis::weapon_status
	)
	override;

	// own functions
	void
	change_animation();

	void
	change_animation(
		sanguis::client::load::animation_type
	);

	sanguis::client::load::animation_type
	animation() const;

	sanguis::client::load::animation_type
	fallback_anim(
		sanguis::client::load::animation_type
	) const;

	bool
	animations_ended() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::weapon_status weapon_status_;

	std::unique_ptr<
		sanguis::client::draw2d::entities::model::healthbar
	> healthbar_;

	std::unique_ptr<
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
