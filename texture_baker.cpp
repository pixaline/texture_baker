#include "texture_baker.h"
//#include "core/method_bind_ext.gen.inc"

void TextureBaker::set_mask_texture(Ref<Texture> mask) {
	maskImage = mask->get_data()->duplicate(true);
	maskImage->convert(Image::FORMAT_RGBA8);
}

void TextureBaker::bake_texture(Ref<Texture> texture, Color tint) {

	Ref<Image> img = texture->get_data()->duplicate(true);
	img->convert(Image::FORMAT_RGBA8);

	if (baseImage.is_valid()) {
		if (img->get_size() != baseImage->get_size()) {
			return;
		}
		if (baseImage->get_format() != img->get_format()) {
			return;
		}

		if (tint.a != 0.0) {
			colorTintImage->fill(tint);
			img->blit_rect_mask(colorTintImage, img, Rect2(Vector2(0, 0), colorTintImage->get_size()), Vector2(0, 0));
		}

		if (maskImage.is_valid()) {
			baseImage->blend_rect_mask(img, maskImage, Rect2(Vector2(0, 0), img->get_size()), Vector2(0, 0));

		} else {
			baseImage->blit_rect_mask(img, img, Rect2(Vector2(0, 0), baseImage->get_size()), Vector2(0, 0));
		}
	} else {
		// Create initial texture

		if (maskImage.is_valid()) {
			// Mask it with the mask texture
			Rect2 rect = Rect2(Vector2(0, 0), img->get_size());
			img->fill(Color(1.0, 1.0, 1.0, 1.0));
			baseImage = Ref<Image>(new Image(img->get_width(), img->get_height(), false, img->get_format()));
			baseImage->fill(Color(1.0, 1.0, 1.0, 1.0));
			baseImage->blend_rect_mask(img, maskImage, rect, Vector2(0, 0));
		} else {
			// Just copy it
			baseImage = img;

		}

		Image * colimg = new Image(baseImage->get_width(), baseImage->get_height(), false, baseImage->get_format());
		colorTintImage = Ref<Image>(colimg);
	}
}
Ref<Image> TextureBaker::get_final_image() {
	return baseImage;
}
Ref<ImageTexture> TextureBaker::get_final_texture() {
	Ref<ImageTexture> tex;
	tex.instance();
	tex->create_from_image(baseImage, 0);
	return tex;
}

void TextureBaker::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_mask_texture"), &TextureBaker::set_mask_texture);
	ClassDB::bind_method(D_METHOD("bake_texture"), &TextureBaker::bake_texture);
	ClassDB::bind_method(D_METHOD("get_final_image"), &TextureBaker::get_final_image);
	ClassDB::bind_method(D_METHOD("get_final_texture"), &TextureBaker::get_final_texture);
}


TextureBaker::TextureBaker() {

}

TextureBaker::~TextureBaker() {
}


