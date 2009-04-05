#ifndef SANGUIS_MESSAGES_UNWRAP_HPP_INCLUDED
#define SANGUIS_MESSAGES_UNWRAP_HPP_INCLUDED

#include "base.hpp"
#include "concrete.hpp"
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <typeinfo>

namespace sanguis
{
namespace messages
{
namespace detail
{

template<
	typename Result,
	bool done = true
>
struct unwrap_impl {
	template<
		typename Iterator,
		typename LastIterator,
		typename Fun,
		typename Handler
	>
	static Result
	execute(
		Iterator *,
		LastIterator *,
		Fun &,
		base const &msg,
		Handler const &def_handler)
	{
		return def_handler(msg);
	}
};

template<
	typename Result
>
struct unwrap_impl<
	Result,
	false
> {
	template<
		typename Iterator,
		typename LastIterator,
		typename Fun,
		typename Handler
	>
	static Result
	execute(
		Iterator *,
		LastIterator *,
		Fun &f,
		base const &msg,
		Handler const &def_handler)
	{
		typedef typename boost::mpl::deref<Iterator>::type item;
		typedef typename boost::mpl::next<Iterator>::type iter;

		typedef concrete<item> concrete_msg;

		return typeid(msg) == typeid(concrete_msg)
			? f(
				static_cast<
					concrete_msg const &
				>(msg).value())
			: unwrap_impl<
				Result,
				boost::is_same<
					iter,
					LastIterator
				>::value
			>::execute(
				static_cast<iter *>(0),
				static_cast<LastIterator *>(0),
				f,
				msg,
				def_handler
			);
	}
};

}

template<
	typename Sequence,
	typename Result,
	typename Fun,
	typename Handler
>
Result
unwrap(
	Fun &f,
	base const &msg,
	Handler const &def_handler)
{
	typedef typename boost::mpl::begin<Sequence>::type first;
	typedef typename boost::mpl::end<Sequence>::type last;

	return detail::unwrap_impl<
		Result,
		boost::is_same<first, last>::value
	>::execute(
		static_cast<first *>(0),
		static_cast<last *>(0),
		f,
		msg,
		def_handler
	);
}

}
}

#endif
