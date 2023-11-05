module;
export import <string>;
export module user;

namespace gartic {
	export class User
	{
	public:
		User();
		User(const std::string& name, uint16_t score);
		User(const User& user);
		std::string GetName();
		void SetName(const std::string& name);
		uint16_t GetScore();
		void SetScore(uint16_t score);
		void AddPoints(uint16_t points);

	private:
		std::string m_name;
		uint16_t m_score;
	};
}
