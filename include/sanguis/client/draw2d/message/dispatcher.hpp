#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_DISPATCHER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_DISPATCHER_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/client/draw2d/message/dispatcher_fwd.hpp>
#include <sanguis/client/draw2d/message/environment_fwd.hpp>
#include <sanguis/client/draw2d/entities/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/messages/add_aoe_projectile_fwd.hpp>
#include <sanguis/messages/add_enemy_fwd.hpp>
#include <sanguis/messages/add_friend_fwd.hpp>
#include <sanguis/messages/add_own_player_fwd.hpp>
#include <sanguis/messages/add_pickup_fwd.hpp>
#include <sanguis/messages/add_player_fwd.hpp>
#include <sanguis/messages/add_projectile_fwd.hpp>
#include <sanguis/messages/add_weapon_pickup_fwd.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/messages/change_weapon_fwd.hpp>
#include <sanguis/messages/change_world_fwd.hpp>
#include <sanguis/messages/die_fwd.hpp>
#include <sanguis/messages/experience_fwd.hpp>
#include <sanguis/messages/health_fwd.hpp>
#include <sanguis/messages/level_up_fwd.hpp>
#include <sanguis/messages/max_health_fwd.hpp>
#include <sanguis/messages/move_fwd.hpp>
#include <sanguis/messages/remove_fwd.hpp>
#include <sanguis/messages/rotate_fwd.hpp>
#include <sanguis/messages/speed_fwd.hpp>
#include <sanguis/messages/start_attacking_fwd.hpp>
#include <sanguis/messages/stop_attacking_fwd.hpp>
#include <sanguis/messages/start_reloading_fwd.hpp>
#include <sanguis/messages/stop_reloading_fwd.hpp>
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
		sanguis::messages::add_aoe_projectile const &
	);

	result_type
	operator()(
		sanguis::messages::add_enemy const &
	);

	result_type
	operator()(
		sanguis::messages::add_friend const &
	);

	result_type
	operator()(
		sanguis::messages::add_own_player const &
	);

	result_type
	operator()(
		sanguis::messages::add_pickup const &
	);

	result_type
	operator()(
		sanguis::messages::add_player const &
	);

	result_type
	operator()(
		sanguis::messages::add_projectile const &
	);

	result_type
	operator()(
		sanguis::messages::add_weapon_pickup const &
	);

	result_type
	operator()(
		sanguis::messages::change_weapon const &
	);

	result_type
	operator()(
		sanguis::messages::change_world const &
	);

	result_type
	operator()(
		sanguis::messages::die const &
	);

	result_type
	operator()(
		sanguis::messages::experience const &
	);

	result_type
	operator()(
		sanguis::messages::health const &
	);

	result_type
	operator()(
		sanguis::messages::level_up const &
	);

	result_type
	operator()(
		sanguis::messages::max_health const &
	);

	result_type
	operator()(
		sanguis::messages::move const &
	);

	result_type
	operator()(
		sanguis::messages::remove const &
	);

	result_type
	operator()(
		sanguis::messages::rotate const &
	);

	result_type
	operator()(
		sanguis::messages::start_attacking const &
	);

	result_type
	operator()(
		sanguis::messages::stop_attacking const &
	);

	result_type
	operator()(
		sanguis::messages::start_reloading const &
	);

	result_type
	operator()(
		sanguis::messages::stop_reloading const &
	);

	result_type
	operator()(
		sanguis::messages::speed const &
	);

	result_type
	process_default_msg(
		sanguis::messages::base const &
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
