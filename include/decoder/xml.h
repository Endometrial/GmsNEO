#ifndef BAPHOMET_XML_H
#define BAPHOMET_XML_H

#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>

typedef xmlNode XmlNode;	  // Syntax preference

typedef struct {
	xmlDoc*			document;
	xmlNode*		root;
} XmlDecoder;

XmlDecoder* xml_decoder_open(char* filepath);
int xml_decoder_is_xml(char* filepath);
XmlNode* xml_decoder_get_root_node(XmlDecoder* decoder);
void xml_decoder_close(XmlDecoder* decoder);

XmlNode* xml_node_get_children(XmlNode* node);
int xml_node_get_num_children(XmlNode* node);
char* xml_node_get_content(XmlNode* node);
char* xml_node_get_name(XmlNode* node);
int xml_node_is_element_node(XmlNode* node);
int xml_node_get_num_attributes(XmlNode* nodes);
char* xml_node_get_attribute_name(XmlNode* node, int index);
char* xml_node_get_attribute(XmlNode* node, char* attribute_name);

#endif