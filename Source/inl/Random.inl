template <typename T>
T Random::choice(const std::vector<T>& choices)
{
	return choices[Random::genInt(0, choices.size() - 1)];
}