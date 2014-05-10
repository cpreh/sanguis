#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_CONFIGURE_ENTITY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_CONFIGURE_ENTITY_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/client/draw2d/message/dispatcher.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/server/change_weapon.hpp>
#include <sanguis/messages/server/move.hpp>
#include <sanguis/messages/server/rotate.hpp>
#include <sanguis/messages/server/speed.hpp>
#include <sanguis/messages/server/weapon_status.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace message
{

template<
	typename Message
>
class configure_entity
{
	FCPPT_NONASSIGNABLE(
		configure_entity
	);

	typedef boost::mpl::map<
		boost::mpl::pair<
			sanguis::messages::roles::center,
			sanguis::messages::server::move
		>,
		boost::mpl::pair<
			sanguis::messages::roles::angle,
			sanguis::messages::server::rotate
		>,
		boost::mpl::pair<
			sanguis::messages::roles::speed,
			sanguis::messages::server::speed
		>,
		boost::mpl::pair<
			sanguis::messages::roles::primary_weapon,
			sanguis::messages::server::change_weapon
		>,
		boost::mpl::pair<
			sanguis::messages::roles::weapon_status,
			sanguis::messages::server::weapon_status
		>
	> mapping;
public:
	typedef void result_type;

	configure_entity(
		sanguis::client::draw2d::message::dispatcher &_dispatcher,
		entity_id const _id,
		Message const &_message
	)
	:
		dispatcher_(
			_dispatcher
		),
		id_(
			_id
		),
		message_(
			_message
		)
	{
	}

	template<
		typename Role
	>
	typename boost::enable_if<
		boost::mpl::has_key<
			mapping,
			Role
		>,
		result_type
	>::type
	operator()() const
	{
		dispatcher_(
			typename boost::mpl::at<
				mapping,
				Role
			>::type(
				sanguis::messages::roles::entity_id{} =
					id_,
				Role{} =
					message_. template get<
						Role
					>()
			)
		);
	}

	template<
		typename Role
	>
	typename boost::disable_if<
		boost::mpl::has_key<
			mapping,
			Role
		>,
		result_type
	>::type
	operator()() const
	{
	}
private:
	sanguis::client::draw2d::message::dispatcher &dispatcher_;

	entity_id const id_;

	Message const &message_;
};

}
}
}
}

#endif
