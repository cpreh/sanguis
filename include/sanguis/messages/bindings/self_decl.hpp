#ifndef SANGUIS_MESSAGES_BINDINGS_SELF_DECL_HPP_INCLUDED
#define SANGUIS_MESSAGES_BINDINGS_SELF_DECL_HPP_INCLUDED

#include <sanguis/messages/bindings/self_fwd.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sanguis
{
namespace messages
{
namespace bindings
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct self
:
alda::bindings::dynamic_len<
	Type,
	Type
>
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
