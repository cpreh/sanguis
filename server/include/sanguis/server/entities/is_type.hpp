#ifndef SANGUIS_SERVER_ENTITIES_IS_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IS_TYPE_HPP_INCLUDED


namespace sanguis::server::entities
{

template<
	typename Derived,
	typename Base
>
inline
bool
is_type(
	Base const &_entity
)
{
	return
		dynamic_cast<
			Derived const *
		>(
			&_entity
		)
		!=
		nullptr
		;
}

}

#endif
