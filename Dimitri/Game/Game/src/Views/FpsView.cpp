#include "FpsView.h"

namespace Game {
	Views::FpsView::FpsView(const std::shared_ptr<Graphics::Controllers::GraphicsController>& graphics_controller) : View(graphics_controller) {}

	void Views::FpsView::draw()
	{
		std::string fps = std::to_string(_graphics_controller.get()->get_fps());
		std::tuple<int, int> camera_pos = _graphics_controller.get()->get_camera_pos();
		std::tuple<int, int> level_size = _graphics_controller.get()->get_level_size();
		int window_width = _graphics_controller.get()->get_window().get()->get_width() + std::get<0>(camera_pos);
		int window_height =  std::get<1>(level_size) - std::get<1>(camera_pos);
		int width = fps.size() * 15;
		int height = 50;
		_textures.clear();
		std::string path = Utility::Helpers::get_base_path() + std::string{ "/assets/fonts/font1.ttf" };
		Color color = { 255, 255, 255 };
		_textures.push_back(std::make_shared<Graphics::Models::Text>(fps, color, window_width - width - 5, window_height - height, 100, height, width, 0, path));
		_textures[0].get()->set_visible(true);
		for (auto& t : _textures) {
			_graphics_controller.get()->add_texture(t);
		}
	}
}