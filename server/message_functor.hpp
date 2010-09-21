#ifndef SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_FUNCTOR_HPP_INCLUDED

#include "../net/id_type.hpp"
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
	)
public:
	typedef R result_type;

	message_functor(
		T &t,
		sanguis::net::id_type const id
	)
	:
		t(t),
		id(id)
	{}

	template<
		typename U
	>
	R
	operator()(
		U const &m
	) const
	{
		return t(
			id,
			m
		);
	}

private:
	T &t;
	sanguis::net::id_type const id;
};

}
}

#endif
