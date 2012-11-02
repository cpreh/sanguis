#ifndef SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace server
{

template<
	typename Functor,
	typename Result
>
class message_functor
{
	FCPPT_NONASSIGNABLE(
		message_functor
	);
public:
	typedef Result result_type;

	message_functor(
		Functor &_functor,
		sanguis::server::player_id const _id
	)
	:
		functor_(
			_functor
		),
		id_(
			_id
		)
	{
	}

	template<
		typename Message
	>
	Result
	operator()(
		Message const &_message
	) const
	{
		return
			functor_(
				id_,
				_message
			);
	}
private:
	Functor &functor_;

	sanguis::server::player_id const id_;
};

}
}

#endif
