#ifndef SANGUIS_CLIENT_ARGS_OPTIONAL_SCREEN_UNIT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_OPTIONAL_SCREEN_UNIT_FWD_HPP_INCLUDED

#include <sge/renderer/screen_unit.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace args
{

typedef
fcppt::optional::object<
	sge::renderer::screen_unit
>
optional_screen_unit;

}
}
}

#endif
