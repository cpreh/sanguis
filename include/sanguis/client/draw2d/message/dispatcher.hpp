#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_DISPATCHER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_DISPATCHER_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/client/draw2d/message/dispatcher_fwd.hpp>
#include <sanguis/client/draw2d/message/environment_fwd.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/messages/server/add_aoe_projectile_fwd.hpp>
#include <sanguis/messages/server/add_aura_fwd.hpp>
#include <sanguis/messages/server/add_buff_fwd.hpp>
#include <sanguis/messages/server/add_enemy_fwd.hpp>
#include <sanguis/messages/server/add_friend_fwd.hpp>
#include <sanguis/messages/server/add_own_player_fwd.hpp>
#include <sanguis/messages/server/add_pickup_fwd.hpp>
#include <sanguis/messages/server/add_player_fwd.hpp>
#include <sanguis/messages/server/add_projectile_fwd.hpp>
#include <sanguis/messages/server/add_weapon_pickup_fwd.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/change_weapon_fwd.hpp>
#include <sanguis/messages/server/change_world_fwd.hpp>
#include <sanguis/messages/server/die_fwd.hpp>
#include <sanguis/messages/server/health_fwd.hpp>
#include <sanguis/messages/server/max_health_fwd.hpp>
#include <sanguis/messages/server/move_fwd.hpp>
#include <sanguis/messages/server/remove_buff_fwd.hpp>
#include <sanguis/messages/server/remove_fwd.hpp>
#include <sanguis/messages/server/rotate_fwd.hpp>
#include <sanguis/messages/server/speed_fwd.hpp>
#include <sanguis/messages/server/weapon_status_fwd.hpp>
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
	FCPPT_NONCOPYABLE(
		dispatcher
	);
public:
	explicit
	dispatcher(
		sanguis::client::draw2d::message::environment &
	);

	~dispatcher();

	typedef void result_type;

	result_type
	operator()(
		sanguis::messages::server::add_aoe_projectile const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_aura const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_buff const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_enemy const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_friend const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_own_player const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_pickup const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_player const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_projectile const &
	);

	result_type
	operator()(
		sanguis::messages::server::add_weapon_pickup const &
	);

	result_type
	operator()(
		sanguis::messages::server::change_weapon const &
	);

	result_type
	operator()(
		sanguis::messages::server::change_world const &
	);

	result_type
	operator()(
		sanguis::messages::server::die const &
	);

	result_type
	operator()(
		sanguis::messages::server::health const &
	);

	result_type
	operator()(
		sanguis::messages::server::max_health const &
	);

	result_type
	operator()(
		sanguis::messages::server::move const &
	);

	result_type
	operator()(
		sanguis::messages::server::remove const &
	);

	result_type
	operator()(
		sanguis::messages::server::remove_buff const &
	);

	result_type
	operator()(
		sanguis::messages::server::rotate const &
	);

	result_type
	operator()(
		sanguis::messages::server::speed const &
	);

	result_type
	operator()(
		sanguis::messages::server::weapon_status const &
	);

	result_type
	process_default_msg(
		sanguis::messages::server::base const &
	);
private:
	template<
		typename Msg
	>
	void
	configure_new_object(
		sanguis::client::draw2d::entities::unique_ptr &&,
		Msg const &
	);

	sanguis::client::draw2d::entities::base &
	entity(
		sanguis::entity_id
	);

	sanguis::client::draw2d::message::environment &env_;
};

}
}
}
}

#endif
