#ifndef SANGUIS_SERVER_AURAS_BUFF_CREATE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_BUFF_CREATE_CALLBACK_HPP_INCLUDED

#include <sanguis/server/buffs/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

typedef
std::function<
	sanguis::server::buffs::unique_ptr ()
>
buff_create_callback;

}
}
}

#endif
