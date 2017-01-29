#ifndef SANGUIS_CLIENT_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_CREATE_HPP_INCLUDED

#include <sanguis/client/object_base_unique_ptr.hpp>
#include <sanguis/client/symbol.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace sanguis
{
namespace client
{

SANGUIS_CLIENT_SYMBOL
sanguis::client::object_base_unique_ptr
create(
	fcppt::log::context &,
	sanguis::client::args::result const &
);

}
}

#endif
