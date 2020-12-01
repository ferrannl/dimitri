#pragma once
#include "../Facades/WindowFacade.h"
#include "Text.h"
#include <tuple>

#ifdef _WIN64
#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport)
#else 
#define GRAPHICS_API __declspec(dllimport)
#endif
#else
#define GRAPHICS_API
#endif

/**
* \namespace Graphics
* \brief Namespace for the graphics engine
*/
namespace Graphics {
	/**
	* \namespace Graphics::Models
	* \brief Namespace for the models in the graphics engine
	*/
	namespace Models {
		/**
		* \class Window
		* \brief Class contains the data to render the window
		*/
		class GRAPHICS_API Window {
		private:
			/**
			* \brief The height of the Window
			*/
			int _height;

			/**
			* \brief The width of the Window
			*/
			int _width;

			/**
			* \brief The title of the Window that is displayed in the frame
			*/
			const std::string _title;

			/**
			* \brief Instance of the WindowFacade
			*/
			std::shared_ptr<Facades::WindowFacade> _facade;

			/**
			* \brief A list of the Textures displayed in the Window
			*/
			std::vector<std::shared_ptr<Texture>> _textures;

			/**
			* \brief Returns a Texture if a matching Texture already exists
			*/
			std::shared_ptr<Models::Texture> get_matching_texture(const std::shared_ptr<Models::Texture>& texture) const;
		public:
			Window(const std::string& title, int height, int width);

			/**
			* \brief Calls methods on the WindowFacade to create the everything needed to render a window
			* \return 0 or greater if initialization succeeded, otherwise initialization failed
			*/
			int create();

			/**
			* \brief Updates the Window
			*/
			void update();

			/**
			* \brief Destroys the window
			*/
			void destroy();

			/**
			* \brief Adds the Texture to _textures
			*/
			void add_texture(const std::shared_ptr<Texture>& texture);

			/**
			* \brief Removes the Texture from _textures
			*/
			void remove_texture(const std::shared_ptr<Texture>& texture);

			/**
			* \brief Clears all Textures from _textures
			*/
			void clear_textures();

			/**
			* \brief Returns the Textures
			*/
			std::vector<std::shared_ptr<Texture>> get_textures() const;

			/**
			* \brief Returns the height of the Window
			*/
			int get_height() const;

			/**
			* \brief Returns the width of the Window
			*/
			int get_width() const;

			/**
			* \brief Returns the title of the window
			*/
			const std::string get_title() const;

			/**
			* \brief Returns the WindowFacade
			*/
			std::shared_ptr<Facades::WindowFacade> get_facade() const;

			/**
			* \brief Updates camera position
			*/
			void set_camera_pos(int x, int y);

			/**
			* \brief Returns camera position
			*/
			std::tuple<int, int> get_camera_pos() const;

			/**
			* \brief Sets scene size
			*/
			void set_scene_size(int height, int width);

			/**
			* \brief Returns scene size
			*/
			std::tuple<int, int> get_scene_size() const;
		};
	}
}