#ifndef SANGUIS_CLIENT_PERK_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace perk
{

typedef std::function<
	void (
		sanguis::perk_type
	)
> send_callback;

}
}
}

#endif
