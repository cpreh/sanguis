#ifndef SANGUIS_MESSAGES_CALL_RESULT_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_RESULT_HPP_INCLUDED

#include <sanguis/common/symbol.hpp>
#include <sanguis/messages/call/forward_to_default_fwd.hpp>
#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/call/result_variant.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis::messages::call
{

class result
{
public:
	SANGUIS_COMMON_SYMBOL
	explicit
	result(
		boost::statechart::result
	);

	SANGUIS_COMMON_SYMBOL
	explicit
	result(
		sanguis::messages::call::forward_to_default
	);

	SANGUIS_COMMON_SYMBOL
	sanguis::messages::call::result_variant const &
	get() const;
private:
	sanguis::messages::call::result_variant variant_;
};

}

#endif
