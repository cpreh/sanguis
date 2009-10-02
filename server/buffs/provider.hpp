#ifndef SANGUIS_SERVER_BUFFS_PROVIDER_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_PROVIDER_HPP_INCLUDED

#include "provider_fwd.hpp"
#include "map.hpp"
#include "auto_ptr.hpp"
#include "../entities/with_buffs_fwd.hpp"
#include "../../entity_id.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

class provider {
	SGE_NONCOPYABLE(provider)
public:
	provider();

	~provider();

	void
	add(
		entities::with_buffs &,
		auto_ptr
	);

	void
	remove(
		entities::with_buffs &
	);
private:
	map buffs_;
};

}
}
}

#endif
