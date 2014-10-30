#include <rapidxml.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <iostream>

using namespace rapidxml;

int main (void)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> *node = doc.allocate_node(rapidxml::node_element, "a", "Google");
	doc.append_node(node);
	rapidxml::xml_attribute<> *attr = doc.allocate_attribute("href", "google.com");
	node->append_attribute(attr);

	std::cout << "HI" << std::endl;
	print(std::cout, doc, 0);   // 0 means default printing flags

	// Print to stream using operator <<
/*
	std::cout << doc;   

	// Print to stream using print function, specifying printing flags
	print(std::cout, doc, 0);   // 0 means default printing flags

	// Print to string using output iterator
	std::string s;
	print(std::back_inserter(s), doc, 0);

	// Print to memory buffer using output iterator
	char buffer[4096];                      // You are responsible for making the buffer large enough!
	char *end = print(buffer, doc, 0);      // end contains pointer to character after last printed character
	*end = 0;                               // Add string terminator after XML
*/
}
