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

typedef
fcppt::unique_ptr<
	sanguis::server::auras::aura
>
unique_ptr;

}
}
}

#endif
