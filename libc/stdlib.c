#include <stdlib.h>
#include <ctype.h>

#define ato_T(T, str) \
	while (isspace(*str)) ++str; \
	bool negative = false; \
	if (*str == '+') \
		++str; \
	else if (*str == '-') \
	{ \
		++str; \
		negative = true; \
	} \
	T result = 0; \
	for (; isdigit(*str); ++str) \
	{ \
		int digit = *str - '0'; \
		result *= 10; \
		result -= digit; \
	} \
	return negative ? result : -result;

int atoi(const char *str)
{
	ato_T(int, str);
}

long atol(const char *str)
{
	ato_T(long, str);
}

long long atoll(const char *str)
{
	ato_T(long long, str);
}
