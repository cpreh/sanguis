#ifndef SANGUIS_SERVER_GLOBAL_NEXT_ID_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_NEXT_ID_CALLBACK_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

typedef
std::function<
	sanguis::entity_id ()
>
next_id_callback;

}
}
}

#endif
