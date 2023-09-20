#ifndef TEXTURE_BAKER_H
#define TEXTURE_BAKER_H

#include "core/math/transform.h"
#include "core/os/dir_access.h"
#include "core/os/file_access.h"
#include "scene/animation/animation_player.h"
#include "scene/3d/skeleton.h"
#include "scene/resources/packed_scene.h"


class TextureBaker : public Node {
	GDCLASS(TextureBaker, Node);

	private:
	Ref<Image> maskImage;
	Ref<Image> baseImage;
	Ref<Image> colorTintImage;

	public:

		void set_mask_texture(Ref<Texture> mask);
		void bake_texture(Ref<Texture> image, Color tint = Color(0, 0, 0, 0));
		Ref<Image> get_final_image();
		Ref<ImageTexture> get_final_texture();

		TextureBaker();
		~TextureBaker();

	protected:
		static void _bind_methods();


};

//VARIANT_ENUM_CAST(SkeletonAnimator::AnimationState);

#endif // TEXTURE_BAKER_H
