#include "../libs.h"

struct fy_node *encodeYamlBool(struct fy_document *node, Data data);
struct fy_node *encodeYamlNull(struct fy_document *node, Data data);
struct fy_node *encodeYamlString(struct fy_document *node, Data data);
struct fy_node *encodeYamlInt(struct fy_document *node, Data data);
struct fy_node *encodeYamlUint(struct fy_document *node, Data data);
struct fy_node *encodeYamlFloat(struct fy_document *node, Data data);
struct fy_node *encodeYamlArray(struct fy_document *node, Data data);
struct fy_node *encodeYamlObject(struct fy_document *node, Data data);
