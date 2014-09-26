#ifndef SANGUIS_SERVER_ENVIRONMENT_INSERT_NO_RESULT_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_INSERT_NO_RESULT_HPP_INCLUDED

#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/environment/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace environment
{

void
insert_no_result(
	sanguis::server::environment::object &,
	sanguis::server::entities::unique_ptr &&,
	sanguis::server::entities::insert_parameters const &
);

}
}
}

#endif
