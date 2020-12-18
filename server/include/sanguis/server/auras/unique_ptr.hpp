#ifndef SANGUIS_SERVER_AURAS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/auras/aura_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

using
unique_ptr
=
fcppt::unique_ptr<
	sanguis::server::auras::aura
>;

}
}
}

#endif
