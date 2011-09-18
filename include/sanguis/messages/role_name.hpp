#ifndef SANGUIS_MESSAGES_ROLE_NAME_HPP_INCLUDED
#define SANGUIS_MESSAGES_ROLE_NAME_HPP_INCLUDED

namespace sanguis
{
namespace messages
{

template<
	typename Role
>
struct role_name
{
	typedef typename Role::alias type;
};

}
}

#endif
