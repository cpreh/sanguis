#ifndef SANGUIS_SERVER_AURAS_CREATE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_CREATE_CALLBACK_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

typedef
std::function<
	sanguis::server::auras::unique_ptr (
		sanguis::diff_clock const &
	)
>
create_callback;

}
}
}

#endif
