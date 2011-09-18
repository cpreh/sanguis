#include <sanguis/server/entities/pickups/monster.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/load/friend_name.hpp>
#include <sanguis/load/context.hpp>
#include <sanguis/duration_second.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::entities::pickups::monster::monster(
	sanguis::diff_clock const &_diff_clock,
	server::environment::load_context &_load_context,
	team::type const _team,
	friend_type::type const _ftype
)
:
	pickup(
		_diff_clock,
		pickup_type::monster,
		_load_context,
		_team,
		optional_dim()
	),
	diff_clock_(_diff_clock),
	ftype_(_ftype)
{
}

sanguis::server::entities::pickups::monster::~monster()
{
}

void
sanguis::server::entities::pickups::monster::do_pickup(
	base &_receiver
)
{
	this->environment().insert(
		entities::unique_ptr(
			new entities::friend_(
			//fcppt::make_unique_ptr<
//				entities::friend_
//			>(
				fcppt::cref(
					diff_clock_
				),
				ftype_,
				this->environment().load_context(),
				damage::no_armor(),
				server::health(100),
				entities::movement_speed(2),
				ai::create_simple(
					diff_clock_,
					_receiver.link()
				),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						fcppt::cref(
							diff_clock_
						),
						weapons::range(2),
						weapons::base_cooldown(
							sanguis::duration_second(
								1.f
							)
						),
						weapons::damage(5)
					)
				)
			)
		),
		entities::insert_parameters_center(
			this->center()
		)
	);
}
