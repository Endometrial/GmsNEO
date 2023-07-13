#ifndef BAPHOMET_XML_H
#define BAPHOMET_XML_H

#include <stdlib.h>
#include <libxml/parser.h>

typedef struct {
	xmlDoc*			document;
	xmlNode*		root;
} XmlDecoder;

XmlDecoder* xml_decoder_open(char* filepath);
int xml_decoder_is_xml(char* filepath);
xmlNode* xml_decoder_get_root_node(XmlDecoder* decoder);
void xml_decoder_close(XmlDecoder* decoder);

xmlNode* xml_node_get_children(xmlNode* node);
int xml_node_get_num_nodes(xmlNode* nodes);
char* xml_node_get_content(xmlNode* node);
char* xml_node_get_name(xmlNode* node);
int xml_node_is_element_node(xmlNode* node);

#endif