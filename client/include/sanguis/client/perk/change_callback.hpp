#ifndef SANGUIS_CLIENT_PERK_CHANGE_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CHANGE_CALLBACK_HPP_INCLUDED

#include <sanguis/client/perk/change_function.hpp>
#include <fcppt/function_impl.hpp>

namespace sanguis::client::perk
{

using change_callback = fcppt::function<sanguis::client::perk::change_function>;

}

#endif
