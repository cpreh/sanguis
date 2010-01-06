#ifndef SANGUIS_DRAW_CONFIGURE_ENTITY_HPP_INCLUDED
#define SANGUIS_DRAW_CONFIGURE_ENTITY_HPP_INCLUDED

#include "scene.hpp"
#include "../messages/pos.hpp"
#include "../messages/move.hpp"
#include "../messages/rotate.hpp"
#include "../messages/max_health.hpp"
#include "../messages/health.hpp"
#include "../messages/speed.hpp"
#include "../messages/dim.hpp"
#include "../messages/resize.hpp"
#include "../messages/roles/angle.hpp"
#include "../messages/roles/max_health.hpp"
#include "../messages/roles/health.hpp"
#include "../messages/roles/speed.hpp"
#include "../entity_id.hpp"
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/utility/enable_if.hpp>

namespace sanguis
{
namespace draw
{

template<
	typename Message
>
class configure_entity {
	typedef boost::mpl::map<
		boost::mpl::pair<
			messages::pos,
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
		>,
		boost::mpl::pair<
			messages::dim,
			messages::resize
		>
	> mapping;
public:
	typedef void result_type;

	configure_entity(
		scene &scene_,
		entity_id const id_,
		Message const &message_
	)
	:
		scene_(scene_),
		id_(id_),
		message_(message_)
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
		scene_(
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
	scene &scene_;
	entity_id const id_;
	Message const &message_;
};

}
}

#endif