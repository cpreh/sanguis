#ifndef SANGUIS_CLIENT_DISPATCH_DEFAULT_FUNCTION_HPP_INCLUDED
#define SANGUIS_CLIENT_DISPATCH_DEFAULT_FUNCTION_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

typedef
fcppt::function<
	boost::statechart::result (
		sanguis::messages::server::base const &
	)
>
dispatch_default_function;

}
}

#endif
