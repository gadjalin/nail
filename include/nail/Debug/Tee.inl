template<typename PrintFn>
Tee<PrintFn, if_is_invocable<PrintFn> >::Tee(PrintFn fn) noexcept
   : m_print(fn) {}

template<typename PrintFn>
template<typename V>
decltype(auto) Tee<PrintFn, if_is_invocable<PrintFn> >::operator()(V&& value)
{
   m_print(value);
   return std::forward<V>(value);
}

inline Tee<std::filesystem::path>::Tee(std::filesystem::path const& filePath, std::ios_base::openmode mode) noexcept
   : m_file(filePath), m_mode(mode) {}

template<typename V>
decltype(auto) Tee<std::filesystem::path>::operator()(V&& value)
{
   std::ofstream file(m_file, m_mode);

   if (file)
      file << value << std::endl;
   else
      std::cerr << "unable to open file " << m_file << std::endl;

   return std::forward<V>(value);
}

template<typename Stream>
Tee<Stream, if_is_stream<Stream> >::Tee(Stream& output) noexcept
   : m_output(output) {}

template<typename Stream>
template<typename V>
decltype(auto) Tee<Stream, if_is_stream<Stream> >::operator()(V&& value)
{
   m_output << value << std::endl;
   return std::forward<V>(value);
}

template<typename PrintFunc, if_is_invocable<PrintFunc, int>>
Tee<PrintFunc> make_tee(PrintFunc func) noexcept
{
   return Tee<PrintFunc>(func);
}

template<typename Stream, if_is_stream<Stream, int>>
Tee<Stream> make_tee(Stream& stream) noexcept
{
   return Tee<Stream>(stream);
}

template<typename V, typename TeeType>
decltype(auto) operator|(V&& value, Tee<TeeType> tee_t)
{
   tee_t(value);
   return std::forward<V>(value);
}

template<typename V, typename CharType>
decltype(auto) stee(V&& value, std::basic_ostream<CharType>& output)
{
   output << value << std::endl;
   return std::forward<V>(value);
}

template<typename V>
decltype(auto) ftee(V&& value, std::filesystem::path const& outputFile, std::ios_base::openmode mode)
{
   std::ofstream file(outputFile, mode);

   if (file)
      file << value << std::endl;
   else
      std::cerr << "unable to open file " << outputFile << std::endl;

   return std::forward<V>(value);
}

