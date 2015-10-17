#ifndef SANGUIS_MESSAGES_CALL_RESULT_VARIANT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_RESULT_VARIANT_FWD_HPP_INCLUDED

#include <sanguis/messages/call/forward_to_default_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace call
{

typedef
fcppt::variant::variadic<
	boost::statechart::result,
	sanguis::messages::call::forward_to_default
>
result_variant;

}
}
}

#endif
