#ifndef SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>


#define SANGUIS_SERVER_BUFFS_DEFINE_SPECIAL(\
	derived,\
	base\
)\
class derived \
: \
	public sanguis::server::buffs::base \
{ \
	FCPPT_NONCOPYABLE(\
		derived\
	);\
public:\
	using sanguis::server::buffs::base::base;\
\
	~derived()\
	{\
	}\
}

#endif
