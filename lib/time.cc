#include "time.hpp"

namespace hkl {
	std::string time::GetCurrentString() {
		char buffer[80];

		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now + std::chrono::hours(9));

		struct tm *timeinfo = localtime(&now_c);
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %I:%M:%S", timeinfo);
		std::string str(buffer);
		return str;
	}

	struct tm* time::GetCurrentTM() {
		char buffer[80];

		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now + std::chrono::hours(9));

		struct tm *timeinfo = localtime(&now_c);
		return timeinfo;
		
	}

/* 아래 함수들은 public 함수  */
    void timer::Start() {
        start = std::chrono::system_clock::now();
    }

    double timer::End() {
        std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
        return sec.count();
    }

	std::chrono::system_clock::time_point timer::start = std::chrono::system_clock::now();
}
