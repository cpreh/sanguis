#ifndef SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED

#include <sanguis/server/player_id_from_net.hpp>
#include <alda/net/id.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{

template<
	typename T,
	typename R
>
class message_functor
{
	FCPPT_NONASSIGNABLE(
		message_functor
	);
public:
	typedef R result_type;

	message_functor(
		T &_value,
		alda::net::id const _id
	)
	:
		value_(
			_value
		),
		id_(
			_id
		)
	{
	}

	template<
		typename U
	>
	R
	operator()(
		U const &_message
	) const
	{
		return
			value_(
				sanguis::server::player_id_from_net(
					id_
				),
				_message
			);
	}

private:
	T &value_;

	alda::net::id const id_;
};

}
}

#endif
