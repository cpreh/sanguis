#ifndef SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>


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
	add();

	virtual
	void
	remove();

	virtual
	void
	update();

	virtual
	~buff() = 0;

	// Only compares other buffs with the same typeid
	virtual
	bool
	less(
		sanguis::server::buffs::buff const &
	) const = 0;
protected:
	buff();

	FCPPT_MAKE_STRONG_TYPEDEF(
		bool,
		added
	);
private:
	virtual
	void
	apply(
		sanguis::server::buffs::buff::added
	);
};

}
}
}

#endif
