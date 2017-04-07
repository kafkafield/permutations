#ifdef __linux__
#include <sys/time.h>

inline double get_time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + (tv.tv_usec / 1e6);
}
#elif _WIN32
#include <time.h>

inline double get_time() {
	return (double)clock() / CLOCKS_PER_SEC;
}
#endif