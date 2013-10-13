#ifndef SANGUIS_SERVER_DAMAGE_ICE_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_ICE_HPP_INCLUDED

#include <sanguis/server/damage/wrapper.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sanguis
{
namespace server
{
namespace damage
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wshadow)

extern sanguis::server::damage::wrapper const ice;

FCPPT_PP_POP_WARNING

}
}
}

#endif
