#ifndef SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

class buff
{
	FCPPT_NONMOVABLE(
		buff
	);
public:
	[[nodiscard]]
	virtual
	sanguis::buff_type
	type() const = 0;

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

	[[nodiscard]]
	// Only compares other buffs with the same typeid
	virtual
	bool
	greater(
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
