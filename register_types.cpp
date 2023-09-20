/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "texture_baker.h"

void register_texture_baker_types() {
	ClassDB::register_class<TextureBaker>();
}

void unregister_texture_baker_types() {
   // 
}
