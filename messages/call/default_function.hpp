#ifndef SANGUIS_MESSAGES_CALL_DEFAULT_FUNCTION_HPP_INCLUDED
#define SANGUIS_MESSAGES_CALL_DEFAULT_FUNCTION_HPP_INCLUDED

#include "../base_fwd.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace messages
{
namespace call
{

template<
	typename Result
>
struct default_function {
	typedef sge::function::object<
		Result (
			base const &
		)
	> type;
};

}
}
}

#endif
