#ifndef SANGUIS_SERVER_REMOVE_SIGHT_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_REMOVE_SIGHT_CALLBACK_HPP_INCLUDED

#include <sanguis/entity_id_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

typedef
std::function<
	void (
		sanguis::entity_id
	)
>
remove_sight_callback;

}
}

#endif
