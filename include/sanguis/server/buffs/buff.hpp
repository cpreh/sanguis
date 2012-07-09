#ifndef SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BUFF_HPP_INCLUDED

#include <sanguis/server/buffs/base_hook.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class buff
:
	public sanguis::server::buffs::base_hook
{
	FCPPT_NONCOPYABLE(
		buff
	);
public:
	virtual void
	update(
		entities::base &
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

FCPPT_PP_POP_WARNING

}
}
}

#endif
