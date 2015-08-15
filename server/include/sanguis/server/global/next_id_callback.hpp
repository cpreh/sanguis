#ifndef SANGUIS_SERVER_GLOBAL_NEXT_ID_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_NEXT_ID_CALLBACK_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

typedef
fcppt::function<
	sanguis::entity_id ()
>
next_id_callback;

}
}
}

#endif
