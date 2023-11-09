#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>

bool startswith(const std::string &str, const std::string &start_prefix) {
	return !str.compare(0, start_prefix.size(), start_prefix);
}

bool endswith(const std::string &str, const std::string &end_suffix) {
	return !str.compare(str.size() - end_suffix.size(), end_suffix.size(), end_suffix);
}

inline std::string getCIDPrefix(const std::string &cid) {
	return cid.substr(0, cid.find('_'));
}

inline std::string getCIDSuffix(const std::string &cid) {
	int pos = cid.find('_');
	return cid.substr(pos, cid.size() - pos);
}

struct Match {
    uint64_t start;
    uint64_t end;
    float val;
    Match(const uint64_t &start, const uint64_t &end, const float &val) : start(start), end(end), val(val) {}
    bool operator<(const Match &o) const {
        return val < o.val;
    }
};



int main () {
	try {
		std::map<int, std::string> test;
		for (int i = 10; i < 15; ++i) test[i] = std::to_string(i);
		auto t1 = test.lower_bound(8); 
		
		if (t1 != test.end()) {
			std::cout << t1->first << std::endl;
			t1--;
			for (auto &t : test) if (t == *t1) std::cout << "foud t1 in test" << std::endl;
			std::cout << t1->first << std::endl;
		} else {
			std::cout << "t1 is end " << std::endl;
		} 
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;

	
	std::vector<Match> matches;
	matches.push_back({0, 0, 0.1});
	matches.push_back({0, 0, 0.2});
	std::sort(matches.begin(), matches.end());
	for (auto &m : matches) {
		std::cout << m.start << "-" << m.end << "=" << m.val << std::endl;
	}


	// std::string test = "chaserfer4tq4tqf324543test\n";
	// std::cout << startswith(test, "ch");
	// std::cout <<endswith(test, "\n") << std::endl;

	// std::string cid = "che70c9c68-ce3e-4ec3-9e49-b97a7faa8f0a_1676130000000_2367";

	// std::cout << getCIDPrefix(cid) << std::endl;
	
	// std::cout << getCIDSuffix(cid) << std::endl;

	// long t = time(0);
	// std::cout << t * 1000 << std::endl;
	// std::cout << INT64_MAX << std::endl;

	// std::map<int, int> test_map;
	// for (int i = 0; i < 10; ++i) {
	// 	test_map[i * 10] = i * 10;
	// }
	// auto it1 = test_map.lower_bound(15);
	// auto it2 = test_map.upper_bound(110);
	// it2++;
	// std::map<int, int> new_map = {it1, it2};
	// std::cout << new_map.size() << std::endl;
	// std::cout << it->first << ", " << it->second << std::endl;
	return 0;
}