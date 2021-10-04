#ifndef SANGUIS_CLIENT_PERK_SEND_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_SEND_CALLBACK_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::client::perk
{

using
send_callback
=
fcppt::function<
	void (
		sanguis::perk_type
	)
>;

}

#endif
