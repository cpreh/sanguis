#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_OBJECT_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_health.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/part_fwd.hpp>
#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/animation_type_fwd.hpp>
#include <sanguis/client/load/model/object_cref.hpp>
#include <sanguis/client/load/model/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client::draw2d::entities::model
{

class object
:
	public sanguis::client::draw2d::entities::container,
	public sanguis::client::draw2d::entities::ifaces::with_health,
	public sanguis::client::draw2d::entities::ifaces::with_weapon
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	using
	parameters_type
	=
	sanguis::client::draw2d::entities::model::parameters;

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
	[[nodiscard]]
	bool
	dead() const
	override;

	void
	pause(
		bool
	)
	override;

	[[nodiscard]]
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

	[[nodiscard]]
	sanguis::client::draw2d::entities::model::part &
	part(
		sanguis::client::draw2d::sprite::index const &
	);

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

	[[nodiscard]]
	sanguis::client::optional_health_pair
	health_pair() const;
private:
	using
	part_vector
	=
	std::vector<
		sanguis::client::draw2d::entities::model::part
	>;

	object(
		sanguis::client::draw2d::entities::model::parameters const &,
		sanguis::client::load::model::object_cref
	);

	object(
		sanguis::client::draw2d::entities::model::parameters const &,
		sanguis::client::load::model::object const &,
		part_vector &&
	);

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

	[[nodiscard]]
	sanguis::client::load::animation_type
	animation() const;

	[[nodiscard]]
	sanguis::client::load::animation_type
	fallback_anim(
		sanguis::client::load::animation_type
	) const;

	[[nodiscard]]
	bool
	animations_ended() const;

	sanguis::diff_clock_cref const diff_clock_;

	sanguis::weapon_status weapon_status_;

	sanguis::client::optional_health_pair health_pair_;

	using
	optional_decay_time
	=
	fcppt::optional::object<
		sanguis::client::draw2d::entities::model::decay_time
	>;

	optional_decay_time decay_time_;

	sanguis::client::draw2d::entities::model::decay_option const decay_option_;

	part_vector parts_;
};

}

#endif
