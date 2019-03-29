#ifndef SANGUIS_SERVER_MESSAGE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_FUNCTION_HPP_INCLUDED

#include <sanguis/messages/call/result.hpp>
#include <sanguis/server/player_id.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{

template<
	typename State
>
class message_function
{
public:
	typedef
	sanguis::messages::call::result
	result_type;

	message_function(
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
			state_.get()(
				id_,
				_message
			);
	}
private:
	fcppt::reference<
		State
	> state_;

	sanguis::server::player_id id_;
};

}
}

#endif
