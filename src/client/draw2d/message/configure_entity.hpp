#ifndef SANGUIS_CLIENT_DRAW2D_MESSAGE_CONFIGURE_ENTITY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_MESSAGE_CONFIGURE_ENTITY_HPP_INCLUDED

#include "dispatcher.hpp"
#include "../../../messages/move.hpp"
#include "../../../messages/rotate.hpp"
#include "../../../messages/max_health.hpp"
#include "../../../messages/health.hpp"
#include "../../../messages/speed.hpp"
#include "../../../messages/roles/angle.hpp"
#include "../../../messages/roles/center.hpp"
#include "../../../messages/roles/max_health.hpp"
#include "../../../messages/roles/health.hpp"
#include "../../../messages/roles/speed.hpp"
#include "../../../entity_id.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/utility/enable_if.hpp>

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
			messages::roles::center,
			messages::move
		>,
		boost::mpl::pair<
			messages::roles::angle,
			messages::rotate
		>,
		boost::mpl::pair<
			messages::roles::max_health,
			messages::max_health
		>,
		boost::mpl::pair<
			messages::roles::health,
			messages::health
		>,
		boost::mpl::pair<
			messages::roles::speed,
			messages::speed
		>
	> mapping;
public:
	typedef void result_type;

	configure_entity(
		dispatcher &_dispatcher,
		entity_id const _id,
		Message const &_message
	)
	:
		dispatcher_(_dispatcher),
		id_(_id),
		message_(_message)
	{}

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
	operator()(
		Role &
	) const
	{
		dispatcher_(
			typename boost::mpl::at<
				mapping,
				Role
			>::type(
				id_,
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
	operator()(
		Role &
	) const
	{
	}
private:
	dispatcher &dispatcher_;
	entity_id const id_;
	Message const &message_;
};

}
}
}
}

#endif
