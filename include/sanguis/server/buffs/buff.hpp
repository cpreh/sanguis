#ifndef SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED

#include <sanguis/server/entities/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

class buff
{
	FCPPT_NONCOPYABLE(
		buff
	);
public:
	virtual
	void
	add(
		sanguis::server::entities::base &
	);

	virtual
	void
	owner_lost();

	virtual
	void
	remove(
		sanguis::server::entities::base &
	);

	virtual
	void
	update(
		sanguis::server::entities::base &
	);

	bool
	expired() const;

	virtual
	~buff() = 0;
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
