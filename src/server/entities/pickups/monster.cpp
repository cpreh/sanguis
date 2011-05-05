#include "monster.hpp"
#include "../insert_parameters_center.hpp"
#include "../friend.hpp"
#include "../../ai/create_simple.hpp"
#include "../../weapons/melee.hpp"
#include "../../environment/object.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../../load/friend_name.hpp"
#include "../../../load/context.hpp"
#include "../../../time_from_second.hpp"
#include <fcppt/function/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::entities::pickups::monster::monster(
	server::environment::load_context &_load_context,
	team::type const _team,
	friend_type::type const _ftype
)
:
	pickup(
		pickup_type::monster,
		_load_context,
		_team,
		optional_dim()
	),
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
				ftype_,
				this->environment().load_context(),
				damage::no_armor(),
				server::health(100),
				entities::movement_speed(2),
				ai::create_simple(
					_receiver.link()
				),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(2),
						weapons::base_cooldown(
							sanguis::time_from_second(
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
