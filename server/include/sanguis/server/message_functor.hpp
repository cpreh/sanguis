#ifndef SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED

#include <sanguis/messages/call/result.hpp>
#include <sanguis/server/player_id.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{

template<
	typename State
>
class message_functor
{
	FCPPT_NONASSIGNABLE(
		message_functor
	);
public:
	typedef
	sanguis::messages::call::result
	result_type;

	message_functor(
		State &_state,
		sanguis::server::player_id const _id
	)
	:
		state_(
			_state
		),
		id_(
			_id
		)
	{
	}

	template<
		typename Message
	>
	result_type
	operator()(
		Message const &_message
	) const
	{
		return
			state_(
				id_,
				_message
			);
	}
private:
	State &state_;

	sanguis::server::player_id const id_;
};

}
}

#endif