#pragma once

#include <string>

/*
	class ConfigReader

	Utility-class that enable us to store information/settings in a text-file
	according to the INI-fileformat specification.

	Each setting is stored as a key-value-pair seperated by an equals-sign
		KEY = VALUE

	Settings can be bound to a specific section.
	Sections are declared between to square brackets.
	A section will stay active until the file ends or a new section-declaration
	begins.
		[SECTION_NAME]
*/

class ConfigContainer;
class ConfigReader
{
public:
	ConfigReader();
	~ConfigReader();

	// Different methods to add data too the internal list of elements
	void add(const std::string& section, const std::string& key, std::string value);
	void add(const std::string& section, const std::string& key, const char* value);
	void add(const std::string& section, const std::string& key, int value);
	void add(const std::string& section, const std::string& key, bool value);
	void add(const std::string& section, const std::string& key, float value);
	
	// Different methods to retrieve data from the internal list of elements
	std::string get(const std::string& section, const std::string& key, std::string def) const;
	int get(const std::string& section, const std::string& key, int def) const;
	bool get(const std::string& section, const std::string& key, bool def) const;
	float get(const std::string& section, const std::string& key, float def) const;

	// Saves the current internal list of elements to the specified file
	void save(const std::string& filename);

	// Loads the data from the specified file, returns false if something whent wrong
	bool load(const std::string& filename);

	// Clears the entire internal list of elements
	void clear();

	// Returns the number of errors that were caught when loading the config-file
	unsigned int num_parse_errors() const;

	// Returns a specific error that was caught when loading the config-file
	std::string get_parse_error(unsigned int index) const;

private:
	ConfigContainer* _container;
};