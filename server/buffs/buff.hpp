#ifndef SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED

#include "../entities/entity_fwd.hpp"
#include "../../time_type.hpp"
#include "../../entity_id.hpp"
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

class buff {
	SGE_NONCOPYABLE(buff)
public:
	virtual void update(
		entities::entity &,
		time_type) = 0;

	virtual bool
	stacks(
		buff const &) const;

	bool expired() const;

	entity_id source() const;

	virtual ~buff();
protected:
	explicit buff(
		entity_id source);

	void expire();
private:
	entity_id const source_;
	bool expired_;
};

}
}
}

#endif
