#pragma once

#include <memory>
#include <string>
#include "Scene.h"
#include "Background.h"
#include "Font.h"
#include "Labels.h"
#include "Renderer.h"
#include "Texture.h"
#include <vector>

namespace BINI {

	class SongSelect : public Scene {
	public:
		explicit SongSelect(BINI::Renderer* renderer);
		~SongSelect() override = default;

		void display(BINI::Renderer* renderer) override;
		bool isDone() override;
		bool handleEvents(BINI::Events* events) override;

	private:
		//BACKGROUND ASPECT
		void switchToNextSlide();
		void initializeBackgrounds(BINI::Renderer* renderer);
		size_t currentIndex{ 0 };
		Uint32 lastSwitchTime{ 0 };
		static constexpr int SLIDE_DURATION{ 5000 };

		std::vector<Background*> backgrounds;
		Texture* shade;

		bool done;
	};

}