#ifndef SANGUIS_SERVER_ADD_TARGET_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ADD_TARGET_CALLBACK_HPP_INCLUDED

#include <sanguis/server/update_target_callback.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::update_target_callback,
	add_target_callback
);

}
}

#endif
