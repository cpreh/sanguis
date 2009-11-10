#ifndef SANGUIS_MESSAGES_IS_CALLABLE_HPP_INCLUDED
#define SANGUIS_MESSAGES_IS_CALLABLE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

// TODO: create a more generic version of this and put it in sge

namespace sanguis
{
namespace messages
{

template<
	typename T,
	typename Result,
	typename Param
>
struct callable {
	typedef char no;
	struct yes { char c[2]; };

	template<
		typename S,
		Result (S:: *)(
			Param
		)
	>
	struct dummy
	{};

	template<
		typename S
	>
	static yes
	check(
		dummy<
			S,
			&S::operator()
		> *
	);

	template<
		typename S
	>
	static no
	check(...);

	typedef boost::mpl::bool_<
		sizeof(check<T>(0))
		== sizeof(yes)
	> type;
};

}
}

#endif
