#
#   Makes the object scripts actually bearable
#

# DATA { to struct NAME_data {

# Replace LOCALVARIABLE with ((struct NAME_data*)(((Object*)data)->data))->LOCALVARIABLE

# Replace CREATE (void* data) { with NAME_create(void* data) { etc for every function

# Replace self. with ((Object*)data)->

# append Object NAME = {0, NULL, &NAME_create, &NAME_step, &NAME_draw, &NAME_clean, &NAME_destroy, NULL};
