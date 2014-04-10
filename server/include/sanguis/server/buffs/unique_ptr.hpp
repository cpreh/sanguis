#ifndef SANGUIS_SERVER_BUFFS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

typedef std::unique_ptr<
	sanguis::server::buffs::buff
> unique_ptr;

}
}
}

#endif
