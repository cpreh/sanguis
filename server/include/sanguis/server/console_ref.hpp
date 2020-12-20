#ifndef SANGUIS_SERVER_CONSOLE_REF_HPP_INCLUDED
#define SANGUIS_SERVER_CONSOLE_REF_HPP_INCLUDED

#include <sanguis/server/console_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{

using
console_ref
=
fcppt::reference<
	sanguis::server::console
>;

}
}

#endif
