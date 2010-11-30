#ifndef SANGUIS_CYCLIC_ITERATOR_IMPL_HPP_INCLUDED
#define SANGUIS_CYCLIC_ITERATOR_IMPL_HPP_INCLUDED

#include "cyclic_iterator.hpp"

template<
	typename ContainerIterator
>
sanguis::cyclic_iterator<ContainerIterator>::cyclic_iterator()
{}


template<
	typename ContainerIterator
>
template<
	typename OtherIterator
>
sanguis::cyclic_iterator<ContainerIterator>::cyclic_iterator(
	cyclic_iterator<OtherIterator> const &_other
)
:
	it_(_other.it_),
	begin_(_other.begin_),
	end_(_other.end_)
{}

template<
	typename ContainerIterator
>
sanguis::cyclic_iterator<ContainerIterator>::cyclic_iterator(
	container_iterator_type const &_it,
	container_iterator_type const &_begin,
	container_iterator_type const &_end
)
:
	it_(_it),
	begin_(_begin),
	end_(_end)
{}

template<
	typename ContainerIterator
>
template<
	typename OtherIterator
>
sanguis::cyclic_iterator<ContainerIterator> &
sanguis::cyclic_iterator<ContainerIterator>::operator=(
	cyclic_iterator<OtherIterator> const &_other
)
{
	it_ = _other.it_;
	begin_ = _other.begin_;
	end_ = _other.end_;
	return *this;
}

template<
	typename ContainerIterator
>
void
sanguis::cyclic_iterator<ContainerIterator>::begin(
	container_iterator_type const &_begin
)
{
	begin_ = _begin;
}

template<
	typename ContainerIterator
>
void
sanguis::cyclic_iterator<ContainerIterator>::end(
	container_iterator_type const &_end
)
{
	end_ = _end;
}

template<
	typename ContainerIterator
>
typename sanguis::cyclic_iterator<ContainerIterator>::container_iterator_type
sanguis::cyclic_iterator<ContainerIterator>::begin() const
{
	return begin_;
}

template<
	typename ContainerIterator
>
typename sanguis::cyclic_iterator<ContainerIterator>::container_iterator_type
sanguis::cyclic_iterator<ContainerIterator>::end() const
{
	return end_;
}

template<
	typename ContainerIterator
>
typename sanguis::cyclic_iterator<ContainerIterator>::container_iterator_type
sanguis::cyclic_iterator<ContainerIterator>::get() const
{
	return it_;
}

template<
	typename ContainerIterator
>
void
sanguis::cyclic_iterator<ContainerIterator>::increment()
{
	if (begin_ != end_ && ++it_ == end_)
		it_ = begin_;
}

template<
	typename ContainerIterator
>
void
sanguis::cyclic_iterator<ContainerIterator>::decrement()
{
	if (begin_ != end_ && it_ == begin_)
		it_ = boost::prior(end_);
}

template<
	typename ContainerIterator
>
template<
	typename OtherIterator
>
bool
sanguis::cyclic_iterator<ContainerIterator>::equal(
	cyclic_iterator<OtherIterator> const &_other
) const
{
	return it_ == _other.it;
}

template<
	typename ContainerIterator
>
typename sanguis::cyclic_iterator<ContainerIterator>::reference
sanguis::cyclic_iterator<ContainerIterator>::dereference() const
{
	return *it_;
}

template<
	typename ContainerIterator
>
template<
	typename OtherIterator
>
typename sanguis::cyclic_iterator<ContainerIterator>::difference_type
sanguis::cyclic_iterator<ContainerIterator>::distance_to(
	cyclic_iterator<OtherIterator> const &_other
) const
{
	return _other.it_ - it_;
}

#endif
