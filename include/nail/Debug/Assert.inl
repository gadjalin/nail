template<typename Handler, typename Evaluator, typename... Args>
inline auto nail::try_assert(
    Evaluator const& evaluator,
    SourceLocation const& location,
    char const* expression,
    Args&&... args) noexcept -> std::enable_if_t<Handler::enabled>
{
    if (!evaluator())
    {
        Handler::Handle(location, expression, std::forward<Args>(args)...);
        // In case Handler::Handle() doesn't crash the program
        std::abort();
    }
}

template<typename Handler, typename Evaluator, typename... Args>
inline auto nail::try_assert(Evaluator const&, SourceLocation const&, char const*, Args&&...) noexcept -> std::enable_if_t<not Handler::enabled>
{}

