#ifndef SANGUIS_SERVER_AURAS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/auras/aura_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

typedef std::unique_ptr<
	sanguis::server::auras::aura
> unique_ptr;

}
}
}

#endif
