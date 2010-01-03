#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_DISPATCHER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_DISPATCHER_HPP_INCLUDED

#include "message_environment_fwd.hpp"
#include "../messages/add_aoe_projectile.hpp"
#include "../messages/add_enemy.hpp"
#include "../messages/add_friend.hpp"
#include "../messages/add_pickup.hpp"
#include "../messages/add_player.hpp"
#include "../messages/add_projectile.hpp"
#include "../messages/add_weapon_pickup.hpp"
#include "../messages/change_weapon.hpp"
#include "../messages/experience.hpp"
#include "../messages/health.hpp"
#include "../messages/level_up.hpp"
#include "../messages/max_health.hpp"
#include "../messages/move.hpp"
#include "../messages/remove.hpp"
#include "../messages/resize.hpp"
#include "../messages/rotate.hpp"
#include "../messages/start_attacking.hpp"
#include "../messages/stop_attacking.hpp"
#include "../messages/start_reloading.hpp"
#include "../messages/stop_reloading.hpp"
#include "../messages/speed.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{

class message_dispatcher
{
public:
	explicit message_dispatcher(
		message_environment const &
	);

	typedef void result_type;

	result_type;
	operator()(
		messages::add_aoe_projectile const &
	);

	result_type
	operator()(
		messages::add_enemy const &
	);

	void operator()(messages::add_friend const &);
	void operator()(messages::add_pickup const &);
	void operator()(messages::add_player const &);
	void operator()(messages::add_projectile const &);
	void operator()(messages::add_weapon_pickup const &);
	void operator()(messages::change_weapon const &);
	void operator()(messages::experience const &);
	void operator()(messages::health const &);
	void operator()(messages::level_up const &);
	void operator()(messages::max_health const &);
	void operator()(messages::move const &);
	void operator()(messages::remove const &);
	void operator()(messages::resize const &);
	void operator()(messages::rotate const &);
	void operator()(messages::start_attacking const &);
	void operator()(messages::stop_attacking const &);
	void operator()(messages::start_reloading const &);
	void operator()(messages::stop_reloading const &);
	void operator()(messages::speed const &);

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
		entity_auto_ptr,
		Msg const &
	);

	draw::entity &
	entity(
		entity_id
	);
	
	draw::entity const &
	entity(
		entity_id
	) const;

	message_environment const &env_;
};

}
}
}

#endif
