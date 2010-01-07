#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_DISPATCHER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_DISPATCHER_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "../entities/auto_ptr.hpp"
#include "../entities/base_fwd.hpp"
#include "../../../messages/add_aoe_projectile.hpp"
#include "../../../messages/add_enemy.hpp"
#include "../../../messages/add_friend.hpp"
#include "../../../messages/add_pickup.hpp"
#include "../../../messages/add_player.hpp"
#include "../../../messages/add_projectile.hpp"
#include "../../../messages/add_weapon_pickup.hpp"
#include "../../../messages/base_fwd.hpp"
#include "../../../messages/change_weapon.hpp"
#include "../../../messages/experience.hpp"
#include "../../../messages/health.hpp"
#include "../../../messages/level_up.hpp"
#include "../../../messages/max_health.hpp"
#include "../../../messages/move.hpp"
#include "../../../messages/remove.hpp"
#include "../../../messages/resize.hpp"
#include "../../../messages/rotate.hpp"
#include "../../../messages/start_attacking.hpp"
#include "../../../messages/stop_attacking.hpp"
#include "../../../messages/start_reloading.hpp"
#include "../../../messages/stop_reloading.hpp"
#include "../../../messages/speed.hpp"
#include "../../../entity_id.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace message
{

class dispatcher
{
	FCPPT_NONCOPYABLE(dispatcher)
public:
	explicit dispatcher(
		environment &
	);

	~dispatcher();

	typedef void result_type;

	result_type;
	operator()(
		messages::add_aoe_projectile const &
	);

	result_type
	operator()(
		messages::add_enemy const &
	);

	result_type
	operator()(
		messages::add_friend const &
	);

	result_type
	operator()(
		messages::add_pickup const &
	);

	result_type
	operator()(
		messages::add_player const &
	);

	result_type
	operator()(
		messages::add_projectile const &
	);

	result_type
	operator()(
		messages::add_weapon_pickup const &
	);

	result_type
	operator()(
		messages::change_weapon const &
	);

	result_type
	operator()(
		messages::experience const &
	);

	result_type
	operator()(
		messages::health const &
	);

	result_type
	operator()(
		messages::level_up const &
	);

	result_type
	operator()(
		messages::max_health const &
	);

	result_type
	operator()(
		messages::move const &
	);

	result_type
	operator()(
		messages::remove const &
	);

	result_type
	operator()(
		messages::resize const &
	);

	result_type
	operator()(
		messages::rotate const &
	);

	result_type
	operator()(
		messages::start_attacking const &
	);

	result_type
	operator()(
		messages::stop_attacking const &
	);

	result_type
	operator()(
		messages::start_reloading const &
	);

	result_type
	operator()(
		messages::stop_reloading const &
	);

	result_type
	operator()(
		messages::speed const &
	);

	void
	process_default_msg(
		messages::base const &
	);
private:
	template<
		typename Msg
	>
	void
	configure_new_object(
		entities::auto_ptr,
		Msg const &
	);

	draw2d::entities::base &
	entity(
		entity_id
	);
	
	environment &env_;
};

}
}
}
}

#endif
