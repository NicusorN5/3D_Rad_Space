#pragma once
#include "EditableField.hpp"

class EditableFieldCollection
{
	EditableField* _fields;
	size_t _size;
public:
	EditableFieldCollection(std::vector<EditableField> &fields);

	std::string ObjectName;

	size_t Size();
	size_t CountCreatedElements();

	size_t CountHWNDs();

	EditableField& operator[](size_t i);

	std::vector<__stdstring> GetTitles();
	std::vector<__stdstring> GetDefaultValues();

	~EditableFieldCollection();
};