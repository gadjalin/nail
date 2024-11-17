template<typename InputIt>
inline auto nail::join_all(InputIt first, InputIt last, std::string const& delimiter)
    -> std::enable_if_t<std::is_same_v<typename std::iterator_traits<InputIt>::value_type, std::string>, std::string>
{
    NAIL_DEBUG_ASSERT(first != last, "Cannot join an empty list of strings!");
    return std::accumulate(std::next(first), last, *first,
        [&delimiter](std::string const& lhs, std::string const& rhs) -> std::string
        {
            return join(lhs, rhs, delimiter);
        });
}

