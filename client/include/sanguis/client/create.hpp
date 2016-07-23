#ifndef SANGUIS_CLIENT_CREATE_HPP_INCLUDED
#define SANGUIS_CLIENT_CREATE_HPP_INCLUDED

#include <sanguis/client/object_base_unique_ptr.hpp>
#include <sanguis/client/symbol.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

SANGUIS_CLIENT_SYMBOL
sanguis::client::object_base_unique_ptr
create(
	fcppt::log::context &,
	boost::program_options::variables_map const &
);

}
}

#endif
