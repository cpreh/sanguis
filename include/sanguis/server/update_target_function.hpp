#ifndef SANGUIS_SERVER_UPDATE_TARGET_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_UPDATE_TARGET_FUNCTION_HPP_INCLUDED

#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

typedef std::function<
	void (
		sanguis::server::entities::with_body &
	)
> update_target_function;

}
}

#endif
