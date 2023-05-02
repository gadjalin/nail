template<typename Type, typename Parameter, template<typename> class... Capabilities>
nail::NamedType<Type, Parameter, Capabilities...>::NamedType(Type const& value)
   : m_value(value) {}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
template<typename Type_>
nail::NamedType<Type, Parameter, Capabilities...>::NamedType(Type&& value, std::enable_if_t<!std::is_reference_v<Type_>, std::nullptr_t>)
   : m_value(std::move(value)) {}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline Type& nail::NamedType<Type, Parameter, Capabilities...>::get() noexcept
{
   return m_value;
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline Type const& nail::NamedType<Type, Parameter, Capabilities...>::get() const noexcept
{
   return m_value;
}

template<typename Type, template<typename> class crtpType>
inline Type& nail::crtp<Type, crtpType>::underlying() noexcept
{
   return static_cast<Type&>(*this);
}

template<typename Type, template<typename> class crtpType>
inline Type const& nail::crtp<Type, crtpType>::underlying() const noexcept
{
   return static_cast<Type const&>(*this);
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline Type* nail::Dereferenceable<nail::NamedType<Type, Parameter, Capabilities...> >::operator->() noexcept
{
   return std::addressof(this->underlying().get());
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline Type const* nail::Dereferenceable<nail::NamedType<Type, Parameter, Capabilities...> >::operator->() const noexcept
{
   return std::addressof(this->underlying().get());
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline Type& nail::Dereferenceable<nail::NamedType<Type, Parameter, Capabilities...> >::operator*() noexcept
{
   return this->underlying().get();
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline Type const& nail::Dereferenceable<nail::NamedType<Type, Parameter, Capabilities...> >::operator*() const noexcept
{
   return this->underlying().get();
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline nail::ImplicitlyConvertible<nail::NamedType<Type, Parameter, Capabilities...> >::operator Type&() noexcept
{
   return this->underlying().get();
}

template<typename Type, typename Parameter, template<typename> class... Capabilities>
inline nail::ImplicitlyConvertible<nail::NamedType<Type, Parameter, Capabilities...> >::operator Type const&() const noexcept
{
   return this->underlying().get();
}

