#include "IRapidXml/rapidxml.hpp"
#include "IRapidXml/rapidxml_print.hpp"
#include "IRapidXml/rapidxml_utils.hpp"

#include <iostream>
//using namespace std;
using namespace rapidxml;

int XMLRead(){
	//rapidxml::file<>fdoc("../xmlout.xml");
	//std::cout<<fdoc.data();
}

int main(){
	xml_document <> dos;
	
	xml_node<>*rot=dos.allocate_node(rapidxml::node_pi,dos.allocate_string("xml version='1.0' encoding='utf8'"));
	dos.append_node(rot);
	xml_node<>* node=dos.allocate_node(node_element,"config","information");
	
	xml_node<>*color=dos.allocate_node(node_element,"color",NULL);
	
	dos.append_node(node);
	node->append_node(color);
	xml_node<>*blue=dos.allocate_node(node_element,"blue",NULL);
	//dos.append_node(node);
	
	color->append_node(blue);
	
	//xml_node<>*
	
	std::string text;
	
	rapidxml::print(std::back_inserter(text),dos,0);
	
	std::cout<<text<<std::endl;
	std::ofstream out("xmlout.xml");
	out<<text;
	XMLRead();
	return 0;
}