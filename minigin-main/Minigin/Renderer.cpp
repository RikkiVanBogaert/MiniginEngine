#include <stdexcept>
#include "Renderer.h"

#include <chrono>

#include "SceneManager.h"
#include "Texture2D.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_plot.h"

struct Transform
{
	float matrix[16] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
	Transform transform{};
	int ID{};
};

class GameObject3DAlt
{
public:
	~GameObject3DAlt()
	{
		delete transform;
	}
	Transform* transform;
	int ID;
};

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void RenderStats(float min, float max, const float** data, int values, ImU32* colors, int count = 1)
{
	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.ys_list = data;
	conf.values.ys_count = count;
	conf.values.count = values;
	conf.line_thickness = 2.f;
	conf.values.colors = colors;
	conf.scale.min = min;
	conf.scale.max = max;
	conf.tooltip.show = true;
	conf.frame_size = ImVec2(250, 100.f);
	conf.line_thickness = 2.f;

	ImGui::Plot("plot", conf);
}
void RenderStats(std::vector<float> data, int values, ImU32& color)
{
	auto minIt = std::min_element(data.begin(), data.end());
	auto maxIt = std::max_element(data.begin(), data.end());
	float min = *minIt;
	float max = *maxIt;

	const float* dataFl[]{ {&data[0]} };
	ImU32 colors[1]{ {color} };

	RenderStats(min, max, dataFl, values, colors);
}

void DataTrashTheCash(int& size, int steps, std::vector<float>& timesFl)
{
	
	const int length = 10'000'000;
	int* array = new int[length] {};

	for (int stepsize = 1; stepsize <= 1024 * steps; stepsize *= 2)
	{
		float minTime{ INFINITY };
		float maxTime{};
		std::vector<float> times{};

		for (int sample{}; sample < 10; ++sample)
		{

			const auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < length; i += stepsize)
			{
				array[i] *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			const float elapsedTime = float(duration_cast<std::chrono::microseconds>(end - start).count());

			if (elapsedTime > maxTime)
				maxTime = elapsedTime;

			else if (elapsedTime < minTime)
				minTime = elapsedTime;

			times.push_back(elapsedTime);
		}

		times.erase(std::remove(times.begin(), times.end(), minTime), times.end());

		times.erase(std::remove(times.begin(), times.end(), maxTime), times.end());

		float avgTime{};
		for (auto t : times)
		{
			avgTime += t;
		}
		avgTime /= times.size();

		timesFl.push_back(avgTime);
	}

	size = int(timesFl.size());

}

void DataTrashTheCashGameObject3D(int& size, int, std::vector<float>& timesFl)
{
	const int length = 10'000'000;
	GameObject3D* array = new GameObject3D[length] {};

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		float minTime{ INFINITY };
		float maxTime{};
		std::vector<float> times{};

		for (int sample{}; sample < 10; ++sample)
		{

			const auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < length; i += stepsize)
			{
				array[i].ID *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			const float elapsedTime = float(duration_cast<std::chrono::microseconds>(end - start).count());

			if (elapsedTime > maxTime)
				maxTime = elapsedTime;

			else if (elapsedTime < minTime)
				minTime = elapsedTime;

			times.push_back(elapsedTime);
		}

		times.erase(std::remove(times.begin(), times.end(), minTime), times.end());

		times.erase(std::remove(times.begin(), times.end(), maxTime), times.end());

		float avgTime{};
		for (auto t : times)
		{
			avgTime += t;
		}
		avgTime /= times.size();

		timesFl.push_back(avgTime);
	}

	size = int(timesFl.size());
}
void DataTrashTheCacheGameObject3DAlt(int& size, int, std::vector<float>& timesFl)
{
	const int length = 10'000'000;
	GameObject3DAlt* array = new GameObject3DAlt[length]{};

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		float minTime{ INFINITY };
		float maxTime{};
		std::vector<float> times{};

		for (int sample{}; sample < 10; ++sample)
		{

			const auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < length; i += stepsize)
			{
				array[i].ID *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			const float elapsedTime = float(duration_cast<std::chrono::microseconds>(end - start).count());

			if (elapsedTime > maxTime)
				maxTime = elapsedTime;

			else if (elapsedTime < minTime)
				minTime = elapsedTime;

			times.push_back(elapsedTime);
		}

		times.erase(std::remove(times.begin(), times.end(), minTime), times.end());

		times.erase(std::remove(times.begin(), times.end(), maxTime), times.end());

		float avgTime{};
		for (auto t : times)
		{
			avgTime += t;
		}
		avgTime /= times.size();

		timesFl.push_back(avgTime);
	}

	size = int(timesFl.size());
}

void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	
	//Draw Plots
	//DrawPlotTrashCache();
	//DrawPlotGameObject3D();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);


}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}


void dae::Renderer::DrawPlotTrashCache()
{
	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_None);
	static char   u8_v = 100;
	static char   u8_one = 1;
	static ImU8   u8_min = 0;
	static ImU8   u8_max = 255;
	ImGui::InputScalar("samples", ImGuiDataType_U8, &u8_v, &u8_one, NULL, "%u");
	m_TrashTheCacheSteps = static_cast<int>(u8_v);
	const char* buttonText = "Trash the cache";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data ...");
		m_TrashTheCacheDataSize = 0;
		DataTrashTheCash(m_TrashTheCacheDataSize, m_TrashTheCacheSteps, m_TrashTheCacheData);
	}

	if (m_TrashTheCacheDataSize > 0)
	{
		ImU32 orange = { ImColor{195,165,0} };
		RenderStats(m_TrashTheCacheData, m_TrashTheCacheDataSize, orange);
	}
	ImGui::End();
}

void dae::Renderer::DrawPlotGameObject3D()
{
	static char   u8_v = 100;
	static char   u8_one = 1;
	static ImU8   u8_min = 0;
	static ImU8   u8_max = 255;
	ImU32 green = { ImColor{0,255,0} };
	ImU32 blue = { ImColor{94,97,100} };
	const bool vec3DValid = m_Object3DSizeVec > 0;
	const bool vec3DAltValid = m_Object3DAltSizeVec > 0;


	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_None);
	ImGui::InputScalar("samples", ImGuiDataType_U8, &u8_v, &u8_one, NULL, "%u");
	m_StepsObject3D = static_cast<int>(u8_v);
	const char* buttonText = "Trash the cache - GameObject3D";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data");
		m_Object3DSizeVec = 0;
		DataTrashTheCashGameObject3D(m_Object3DSizeVec, m_StepsObject3D, m_Object3DVec);
	}

	if (vec3DValid)
	{
		RenderStats(m_Object3DVec, m_Object3DSizeVec, green);
	}

	buttonText = "Trash the cache - GameObject3DAlt";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data");
		m_Object3DAltSizeVec = 0;
		DataTrashTheCacheGameObject3DAlt(m_Object3DAltSizeVec, m_StepsObject3D, m_Object3DAltVec);
	}

	if (vec3DAltValid)
	{
		RenderStats(m_Object3DAltVec, m_Object3DAltSizeVec, blue);
	}

	if (vec3DValid && vec3DAltValid)
	{
		float min3D = *std::min_element(m_Object3DVec.begin(), m_Object3DVec.end());
		float max3D = *std::max_element(m_Object3DVec.begin(), m_Object3DVec.end());
		float min3DAlt = *std::min_element(m_Object3DAltVec.begin(), m_Object3DAltVec.end());
		float max3DAlt = *std::max_element(m_Object3DAltVec.begin(), m_Object3DAltVec.end());

		float min = min3D < min3DAlt ? min3D : min3DAlt;
		float max = max3D > max3DAlt ? max3D : max3DAlt;
		const int totalAllowdArrayValues{ 2 };
		const float* dataFl[totalAllowdArrayValues]{ &m_Object3DVec[0],&m_Object3DAltVec[0] };
		ImU32 colors[totalAllowdArrayValues]{ green, blue };

		RenderStats(min, max, dataFl, 10, colors, 2);
	}
	ImGui::End();
}