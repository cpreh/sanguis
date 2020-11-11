#ifndef SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>


#define SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL(\
	derived,\
	base\
)\
class derived \
: \
	public sanguis::server::buffs::base \
{ \
	FCPPT_NONMOVABLE(\
		derived\
	);\
public:\
	using sanguis::server::buffs::base::base;\
\
	~derived() override\
	= default; \
}

#endif
