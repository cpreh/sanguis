#ifndef SANGUIS_SERVER_ENTITIES_WITH_ID_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_ID_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/entities/with_id_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

typedef std::unique_ptr<
	sanguis::server::entities::with_id
> with_id_unique_ptr;

}
}
}

#endif
