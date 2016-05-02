#pragma once
template <class T = float>
class TMemory
{
public:
	TMemory();
	~TMemory();
	string getState();
	T getNumber();
	void store(const T);
	T restore();
	void add(const T);
	void clear();

private:
	void init();	
	enum class States { _On, _Off };

	class StatesHelper {
	public:
		static const string &to_string(States value)
		{
			static const map<States, string> enumStringsMap = {
				{ States::_On, "_On" },
				{ States::_Off, "_Off" }
			};

			auto it = enumStringsMap.find(value);
			static string emptyString;
			if (it == enumStringsMap.end()) {
				return emptyString;
			}

			return it->second;
		}
	};

	T fNumber;
	States fState;
};