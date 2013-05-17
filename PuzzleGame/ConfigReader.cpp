#include "ConfigReader.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

typedef std::map<std::string, std::string>	Elements;
typedef std::map<std::string, Elements>		SectionElements;

class ConfigContainer
{
public:
	void add_error(const std::string& str)
	{
		parse_errors.push_back(str);
	}

	SectionElements				data;
	std::vector<std::string>	parse_errors;
};

ConfigReader::ConfigReader():
_container(new ConfigContainer)
{
}

ConfigReader::~ConfigReader()
{
	delete _container;
}

void ConfigReader::add(const std::string& section, const std::string& key, std::string value)
{
	if ( _container->data.find(section) == _container->data.end() )
	{
		_container->data.insert(std::make_pair(section, Elements()));
		_container->data[section].insert(std::make_pair(key, value));
	}
	else
	{
		if ( _container->data[section].find(key) == _container->data[section].end() )
		{
			_container->data[section].insert(std::make_pair(key, value));
		}
		else
		{
			_container->data[section][key] = value;
		}
	}
}

void ConfigReader::add(const std::string& section, const std::string& key, const char* value)
{
	add(section, key, std::string(value));
}

void ConfigReader::add(const std::string& section, const std::string& key, int value)
{
	std::stringstream strm;
	strm << value;

	add(section, key, strm.str());
}

void ConfigReader::add(const std::string& section, const std::string& key, bool value)
{
	if ( value )
		add(section, key, std::string("true"));
	else
		add(section, key, std::string("false"));
}

void ConfigReader::add(const std::string& section, const std::string& key, float value)
{
	std::stringstream strm;
	strm << value;

	add(section, key, strm.str());
}

std::string ConfigReader::get(const std::string& section, const std::string& key, std::string def) const
{
	if ( _container->data.find(section) == _container->data.end() )
	{
		return def;
	}
	else
	{
		if ( _container->data[section].find(key) == _container->data[section].end() )
		{
			return def;
		}
		else
		{
			return _container->data[section][key];
		}
	}
}

int ConfigReader::get(const std::string& section, const std::string& key, int def) const
{
	if ( _container->data.find(section) == _container->data.end() )
	{
		return def;
	}
	else
	{
		if ( _container->data[section].find(key) == _container->data[section].end() )
		{
			return def;
		}
		else
		{
			std::string str = _container->data[section][key];
			std::stringstream strm(str);
			int ret = 0;
			strm >> ret;
			return ret;
		}
	}
}

bool ConfigReader::get(const std::string& section, const std::string& key, bool def) const
{
	if ( _container->data.find(section) == _container->data.end() )
	{
		return def;
	}
	else
	{
		if ( _container->data[section].find(key) == _container->data[section].end() )
		{
			return def;
		}
		else
		{
			std::string str = _container->data[section][key];
			
			if ( str == "True" || str == "TRUE" || str == "true" )
				return true;

			return false;
		}
	}
}

float ConfigReader::get(const std::string& section, const std::string& key, float def) const
{
	if ( _container->data.find(section) == _container->data.end() )
	{
		return def;
	}
	else
	{
		if ( _container->data[section].find(key) == _container->data[section].end() )
		{
			return def;
		}
		else
		{
			std::string str = _container->data[section][key];
			std::stringstream strm(str);
			float ret = 0.0f;
			strm >> ret;
			return ret;
		}
	}
}

void ConfigReader::save(const std::string& filename)
{
	std::ofstream out(filename);

	if ( out.is_open() )
	{

		SectionElements::iterator it_spec = _container->data.find("");
		if ( it_spec != _container->data.end() )
		{
			Elements::iterator it2 = (*it_spec).second.begin();

			while ( it2 != (*it_spec).second.end() )
			{
				out << "\t" << (*it2).first << " = " << (*it2).second << "\n";

				++it2;
			}
		}

		SectionElements::iterator it = _container->data.begin();

		while ( it != _container->data.end() )
		{
			if ( it_spec != _container->data.end() && it_spec == it )
			{
				++it;
				continue;
			}

			out << "[" << (*it).first << "]\n";

			Elements::iterator it2 = (*it).second.begin();

			while ( it2 != (*it).second.end() )
			{
				out << "\t" << (*it2).first << " = " << (*it2).second << "\n";

				++it2;
			}

			++it;
		}

		out.close();
	}
}

bool ConfigReader::load(const std::string& filename)
{
	std::ifstream in(filename);
	
	if ( in.is_open() )
	{
		std::string current_line;
		std::string current_section = "";
		unsigned int line_number = 1;

		while ( !in.eof() )
		{
			std::stringstream error_text;

			std::getline(in, current_line);

			// Remove all whitespaces from the start and end
			current_line.erase(0, current_line.find_first_not_of(" \t\r"));
			current_line.erase(current_line.find_last_not_of(" \t\r") + 1);

			unsigned int comment_pos = current_line.find(';');
			// Remove comments denoted by a ';'-sign
			if ( comment_pos != std::string::npos )
			{
				current_line.erase(comment_pos);
			}

			if ( current_line.size() > 0 )
			{
				// We found a new section
				if ( current_line[0] == '[' )
				{
					current_section = current_line.substr(1, current_line.find_last_of(']') - 1);

					// Trim away whitespaces, just in case
					current_section.erase(0, current_section.find_first_not_of(" \t\r"));
					current_section.erase(current_section.find_last_not_of(" \t\r") + 1);
				}
				else
				{
					// Look for the equals-sign
					int eq_pos = current_line.find('=');

					// We found some syntax-error in the config-file
					if ((unsigned int) eq_pos == std::string::npos )
					{
						error_text << "(" << line_number << "): Failed to find the equals-sign in the KeyValue-pair";
						_container->add_error(error_text.str());
					}
					else
					{
						if ( eq_pos == 0 )
						{
							error_text << "(" << line_number << "): Missing key-identifier";
							_container->add_error(error_text.str());
						}
						else
						{
							std::string key = current_line.substr(0, eq_pos -1);
							std::string value = current_line.substr(eq_pos +1);

							// Trim trim
							key.erase(0, key.find_first_not_of(" \t\r"));
							key.erase(key.find_last_not_of(" \t\r") +1);

							value.erase(0, value.find_first_not_of(" \t\r"));
							value.erase(value.find_last_not_of(" \t\r") +1);

							if ( value.size() == 0 )
							{
								error_text << "(" << line_number << "): Missing value-identifier";
								_container->add_error(error_text.str());
							}

							add(current_section, key, value);
						}
					}
				}
			}

			line_number++;
		}

		in.close();
		return true;
	}

	_container->add_error("Failed to open the file: " + filename);

	return false;
}

void ConfigReader::clear()
{
	SectionElements::iterator it = _container->data.begin();

	while ( it != _container->data.end() )
	{
		(*it).second.clear();
		++it;
	}

	_container->data.clear();
}

unsigned int ConfigReader::num_parse_errors() const
{
	return _container->parse_errors.size();
}

std::string ConfigReader::get_parse_error(unsigned int index) const
{
	return _container->parse_errors.at(index);
}