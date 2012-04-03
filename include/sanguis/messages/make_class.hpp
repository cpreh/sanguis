#ifndef SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_CLASS_HPP_INCLUDED

#include <alda/message/make_class.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sanguis
{
namespace messages
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename T
>
struct make_class
:
alda::message::make_class<
	T
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
