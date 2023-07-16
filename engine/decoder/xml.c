#include <decoder/xml.h>

XmlDecoder* xml_decoder_open(char* filepath) {
	XmlDecoder* decoder;

	// Allocate space for the decoder
	decoder = malloc(sizeof(XmlDecoder));

	// Parse the file
	decoder->document = xmlParseFile(filepath);
	if (decoder->document == NULL) {
		fprintf(stderr, "xml_decoder_open(): Could not parse %s\n", filepath);
		xml_decoder_close(decoder);
		exit(-1);
	}

	// Get the root element/node
	decoder->root = xmlDocGetRootElement(decoder->document);
	if (decoder->document == NULL) {
		fprintf(stderr, "xml_decoder_open(): %s is empty!\n", filepath);
		xml_decoder_close(decoder);
		exit(-1);
	}

	return decoder;
}

void xml_decoder_close(XmlDecoder* decoder) {
	xmlFreeDoc(decoder->document);
	free(decoder);
}

int xml_decoder_is_xml(char* filepath) {
	return (int)(xmlParseFile(filepath) != NULL);
}

xmlNode* xml_decoder_get_root_node(XmlDecoder* decoder) {
	return decoder->root;
}

xmlNode* xml_node_get_children(xmlNode* node) {
	return node->xmlChildrenNode;
}

int xml_node_get_num_children(xmlNode* node) {
	int sum=0;
	XmlNode* current_node = xml_node_get_children(node);
	for (1; current_node!=NULL; current_node = current_node->next) {
		sum++;}
	return sum;
}

char* xml_node_get_content(xmlNode* node) {
	return xmlNodeGetContent(node);
}

char* xml_node_get_name(xmlNode* node) {
	return node->name;
}

int xml_node_is_element_node(xmlNode* node) {
	return (node->type == XML_ELEMENT_NODE);
}

int xml_node_get_num_attributes(XmlNode* node) {
	int sum=0;
	xmlAttr* current_attr = node->properties;
	for (1; current_attr!=NULL; current_attr = current_attr->next) {
		sum++;}
	return sum;
}

char* xml_node_get_attribute_name(XmlNode* node, int index) {
	xmlAttr* current_attribute = node->properties;
	for (int i=0; i<xml_node_get_num_attributes(node); i++) {
		if (i == index) {
			return current_attribute->name;}
		current_attribute = current_attribute->next;
	}
	return (char*)NULL;
}

char* xml_node_get_attribute(XmlNode* node, char* attribute_name) {
	return xmlGetProp(node, attribute_name);
}