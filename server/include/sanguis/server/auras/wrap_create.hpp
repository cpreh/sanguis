#ifndef SANGUIS_SERVER_AURAS_WRAP_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_WRAP_CREATE_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/auras/create_callback.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

template<
	typename Result,
	typename... Args
>
sanguis::server::auras::create_callback
wrap_create(
	Args && ..._args
)
{
	return
		sanguis::server::auras::create_callback(
			[
				&_args...
			](
				sanguis::diff_clock const &
			)
			{
				return
					fcppt::make_unique_ptr<
						Result
					>(
						std::forward<
							Args
						>(
							_args
						)...
					);
			}
		);
}

}
}
}

#endif
