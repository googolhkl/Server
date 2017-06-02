#ifndef SERVER_LIB_TIME_HPP
#define SERVER_LIB_TIME_HPP
#include <ctime>
#include <chrono>
#include <array>

// 시간 포맷은 아래 링크
// http://www.cplusplus.com/reference/ctime/strftime/
#define DATETIME_FORMAT     L"%Y-%m-%d %A %r"
#define TIME_FORMAT         L"%H:%M:%S"
#define DATE_FORMAT         L"%Y-%m-%d %A"
#define DB_FORMAT           L"%Y-%m-%d %H:%M:%S"

#define WBUFFER_SIZE              120

#define YESTERDAY -1
#define TODAY      0
#define TOMORROW   1

namespace hkl {
class time {
	public:
		static std::string GetCurrentString();
		static struct tm* GetCurrentTM();

};

class timer {
    public:
        static void Start();
        static double End();
    private:
        static std::chrono::system_clock::time_point start;
};
}


#endif
