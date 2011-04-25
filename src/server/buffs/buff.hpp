#ifndef SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED

#include "base_hook.hpp"
#include "../entities/base_fwd.hpp"
#include "../../time_delta_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

class buff
:
	public base_hook
{
	FCPPT_NONCOPYABLE(
		buff
	);
public:
	virtual void
	update(
		entities::base &,
		sanguis::time_delta const &
	) = 0;

	bool
	expired() const;

	virtual ~buff();
protected:
	buff();

	void
	expire();
private:
	bool expired_;
};

}
}
}

#endif
