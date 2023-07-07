#include <iostream>
#include <algorithm>
#include <string>

void test() {
    std::string track_id = "asdfasdfsfd";
    std::cout << track_id.rfind('_') << std::endl;
    std::cout << track_id.substr(track_id.rfind('_') + 1, track_id.size()) << std::endl;
}


std::string filterSuffix(const std::string& org_track_id) {
    std::string res_track_id = org_track_id;
    auto checkAndRemoveNumberSuffix = [](std::string &track_id) {
        std::size_t su_idx = track_id.rfind('_');
        if (su_idx == std::string::npos) return;
        std::string suffix = track_id.substr(track_id.rfind('_') + 1, track_id.size());
        if (!suffix.empty() && std::all_of(suffix.begin(), suffix.end(), ::isdigit)) {
            track_id = track_id.substr(0, track_id.rfind('_'));
        }
    };
    checkAndRemoveNumberSuffix(res_track_id); // 第一个数字后缀 _1 buc批次
    checkAndRemoveNumberSuffix(res_track_id); // 第二个数字后缀 _1680484361 cluster时间
    return res_track_id;
}

int main () {
    std::cout << filterSuffix("wanda_beijing_tzwd-ch03016-fid-track-4052-7c8ff271-a820-4b23-9790-1a1680484361") << std::endl;
    return 0;
}