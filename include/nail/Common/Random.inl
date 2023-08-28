template<typename Generator>
std::random_device nail::RandomGenerator<Generator>::s_rd;

template<typename Generator>
inline nail::RandomGenerator<Generator>::RandomGenerator()
    : m_rng(s_rd()) {}

template<typename Generator>
inline nail::RandomGenerator<Generator>::RandomGenerator(SeedType const seed)
    : m_rng(seed) {}

template<typename Generator>
inline void nail::RandomGenerator<Generator>::setSeed(SeedType const seed)
{
    m_rng.seed(seed);
}

template<typename Generator>
template<typename IntType>
inline auto nail::RandomGenerator<Generator>::next(IntType const min, IntType const max)
    -> std::enable_if_t<std::is_integral_v<IntType>, IntType>
{
    return std::uniform_int_distribution<IntType>(min, max)(m_rng);
}

template<typename Generator>
template<typename RealType>
inline auto nail::RandomGenerator<Generator>::next(RealType const min, RealType const max)
    -> std::enable_if_t<std::is_floating_point_v<RealType>, RealType>
{
    return std::uniform_real_distribution<RealType>(min, max)(m_rng);
}

template<typename T>
inline T nail::GenerateRandom(T const min, T const max)
{
    return GetDefaultRandomGenerator().next<T>(min, max);
}

